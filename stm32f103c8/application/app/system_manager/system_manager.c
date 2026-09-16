/**
 * @file system_manager.c
 * @brief Coordinates startup deadlines, the business gate and runtime fault handling.
 */

#include "system_manager.h"
#include "rtos_fault.h"
#include "task.h"

#include <stdbool.h>

#define SYSTEM_TASK_NAME        "system"
#define SYSTEM_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE * 2U)
#define SYSTEM_TASK_PRIORITY    (tskIDLE_PRIORITY + 5U)
#define SYSTEM_RUNNING_BIT      ((EventBits_t)(1U << 16))
#define SYSTEM_FAULT_BIT        ((EventBits_t)(1U << 17))

/** Participant bits must never overlap business release or fault control bits. */
_Static_assert((SYSTEM_READY_BITS_MASK & (SYSTEM_RUNNING_BIT | SYSTEM_FAULT_BIT)) == 0U,
               "Startup participant bits overlap manager control bits");

static volatile system_state_t s_system_state   = SYSTEM_STATE_BOOT;
static EventBits_t             s_required_tasks = 0U;
static StackType_t             s_manager_stack[SYSTEM_TASK_STACK_DEPTH];
static StaticEventGroup_t      s_events_buffer;
static StaticTask_t            s_manager_buffer;
static EventGroupHandle_t      s_events         = NULL;
static TaskHandle_t            s_manager_task   = NULL;
static system_start_callback_t s_start_callback = NULL;

static void system_manager_run(void *argument);
static void system_manager_wait_ready(void);
static void system_manager_check_fault(void);

BaseType_t system_manager_create(system_start_callback_t start_callback, EventBits_t required_tasks)
{
    bool        callback_missing  = start_callback == NULL;
    bool        has_invalid_bits  = false;
    bool        arguments_invalid = false;
    bool        resource_missing  = false;
    EventBits_t invalid_bits      = required_tasks & ~SYSTEM_READY_BITS_MASK;

    has_invalid_bits  = invalid_bits != 0U;
    arguments_invalid = callback_missing || has_invalid_bits;
    if(arguments_invalid)
    {
        return pdFAIL;
    }

    s_required_tasks = required_tasks;
    s_start_callback = start_callback;
    s_events         = xEventGroupCreateStatic(&s_events_buffer);
    resource_missing = s_events == NULL;
    if(resource_missing)
    {
        return pdFAIL;
    }

    s_manager_task   = xTaskCreateStatic(system_manager_run,
                                       SYSTEM_TASK_NAME,
                                       SYSTEM_TASK_STACK_DEPTH,
                                       NULL,
                                       SYSTEM_TASK_PRIORITY,
                                       s_manager_stack,
                                       &s_manager_buffer);
    resource_missing = s_manager_task == NULL;
    if(resource_missing)
    {
        return pdFAIL;
    }
    return pdPASS;
}

void system_manager_report_ready(EventBits_t task_bit)
{
    bool        is_nonzero      = task_bit != 0U;
    bool        is_single_bit   = false;
    bool        is_required_bit = false;
    EventBits_t preceding_bits  = task_bit - 1U;
    EventBits_t duplicate_bits  = task_bit & preceding_bits;
    EventBits_t unexpected_bits = task_bit & ~s_required_tasks;

    is_single_bit   = duplicate_bits == 0U;
    is_required_bit = unexpected_bits == 0U;
    configASSERT(is_nonzero);
    configASSERT(is_single_bit);
    configASSERT(is_required_bit);

    /** These non-blocking APIs cannot fail for valid, module-owned handles. */
    (void)xEventGroupSetBits(s_events, task_bit);
    (void)xTaskNotifyGive(s_manager_task);
}

void system_manager_wait_running(void)
{
    /** Keep the permission latched so late-arriving tasks can pass the same gate. */
    (void)xEventGroupWaitBits(s_events, SYSTEM_RUNNING_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
}

void system_manager_report_fault(void)
{
    /** The event latches the fault; notification also interrupts the startup wait. */
    (void)xEventGroupSetBits(s_events, SYSTEM_FAULT_BIT);
    (void)xTaskNotifyGive(s_manager_task);
}

system_state_t system_manager_get_state(void)
{
    bool has_fault = g_rtos_fault != RTOS_FAULT_NONE;

    if(has_fault)
    {
        return SYSTEM_STATE_FAULT;
    }
    return s_system_state;
}

static void system_manager_run(void *argument)
{
    bool start_failed    = false;
    bool start_succeeded = false;
    (void)argument;

    s_system_state = SYSTEM_STATE_INITIALIZING;
    system_manager_wait_ready();

    /** The application owns the bounded service startup callback and its dependencies. */
    start_succeeded = s_start_callback();
    start_failed    = !start_succeeded;
    if(start_failed)
    {
        rtos_fault_stop(RTOS_FAULT_SERVICE_START);
    }

    /** Publish state and permission atomically relative to task-context fault reports.
     * Nested event-group scheduler suspension is supported; this region never blocks.
     */
    vTaskSuspendAll();
    system_manager_check_fault();
    s_system_state = SYSTEM_STATE_RUNNING;
    (void)xEventGroupSetBits(s_events, SYSTEM_RUNNING_BIT);
    /** Resume's result only says whether a yield occurred; both results are valid. */
    (void)xTaskResumeAll();

    /** A startup handshake does not establish runtime health. Product-specific health
     * monitoring belongs here; the current manager blocks until a reported fault.
     */
    (void)xEventGroupWaitBits(s_events, SYSTEM_FAULT_BIT, pdFALSE, pdTRUE, portMAX_DELAY);
    rtos_fault_stop(RTOS_FAULT_RUNTIME);
}

static void system_manager_wait_ready(void)
{
    bool             all_ready       = false;
    bool             has_timed_out   = false;
    EventBits_t      events          = 0U;
    EventBits_t      ready_tasks     = 0U;
    TickType_t       start_tick      = xTaskGetTickCount();
    TickType_t       elapsed_ticks   = 0U;
    TickType_t       remaining_ticks = 0U;
    const TickType_t timeout_ticks   = pdMS_TO_TICKS(SYSTEM_STARTUP_TIMEOUT_MS);

    for(;;)
    {
        system_manager_check_fault();
        events      = xEventGroupGetBits(s_events);
        ready_tasks = events & s_required_tasks;
        all_ready   = ready_tasks == s_required_tasks;
        if(all_ready)
        {
            return;
        }

        /** Unsigned subtraction tolerates tick wrap; timeout is shorter than one wrap. */
        elapsed_ticks = xTaskGetTickCount() - start_tick;
        has_timed_out = elapsed_ticks >= timeout_ticks;
        if(has_timed_out)
        {
            rtos_fault_stop(RTOS_FAULT_STARTUP_TIMEOUT);
        }
        remaining_ticks = timeout_ticks - elapsed_ticks;
        /** A notification is only a wakeup hint; persistent event bits are authoritative. */
        (void)ulTaskNotifyTake(pdTRUE, remaining_ticks);
    }
}

static void system_manager_check_fault(void)
{
    bool        has_fault  = false;
    EventBits_t events     = xEventGroupGetBits(s_events);
    EventBits_t fault_bits = events & SYSTEM_FAULT_BIT;

    has_fault = fault_bits != 0U;
    if(has_fault)
    {
        rtos_fault_stop(RTOS_FAULT_RUNTIME);
    }
}
