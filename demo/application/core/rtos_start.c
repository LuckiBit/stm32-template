#include "rtos_start.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "led.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"

#include <stdbool.h>

static TaskHandle_t s_task_0_handle;
static TaskHandle_t s_task_1_handle;
static TaskHandle_t s_task_2_handle;
static TaskHandle_t s_task_3_handle;
static TaskHandle_t s_task_4_handle;

static SemaphoreHandle_t s_semaphore_0;
static SemaphoreHandle_t s_semaphore_1;
static SemaphoreHandle_t s_semaphore_2;
static SemaphoreHandle_t s_semaphore_3;
static SemaphoreHandle_t s_semaphore_4;

static SemaphoreHandle_t s_mutex_0;
static SemaphoreHandle_t s_mutex_1;
static SemaphoreHandle_t s_mutex_2;
static SemaphoreHandle_t s_mutex_3;
static SemaphoreHandle_t s_mutex_4;

static QueueHandle_t s_queue_0;
static QueueHandle_t s_queue_1;
static QueueHandle_t s_queue_2;
static QueueHandle_t s_queue_3;
static QueueHandle_t s_queue_4;

static EventGroupHandle_t s_event_group_0;
static EventGroupHandle_t s_event_group_1;

static TimerHandle_t s_timer_0;
static TimerHandle_t s_timer_1;

static void task_0(void *argument);
static void task_1(void *argument);
static void task_2(void *argument);
static void task_3(void *argument);
static void task_4(void *argument);
static void timer_0_callback(TimerHandle_t timer);
static void timer_1_callback(TimerHandle_t timer);

static BaseType_t rtos_objects_create(void);
static BaseType_t rtos_tasks_create(void);
static BaseType_t rtos_timers_start(void);
static void       rtos_fatal_error(void);

void rtos_start(void)
{
    bool       create_failed;
    BaseType_t create_result = rtos_objects_create();

    create_failed = create_result != pdPASS;

    if(create_failed)
    {
        rtos_fatal_error();
    }

    create_result = rtos_tasks_create();
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        rtos_fatal_error();
    }

    create_result = rtos_timers_start();
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        rtos_fatal_error();
    }

    vTaskStartScheduler();
    rtos_fatal_error();
}

static BaseType_t rtos_objects_create(void)
{
    bool object_missing;

    s_semaphore_0 = xSemaphoreCreateBinary();
    s_semaphore_1 = xSemaphoreCreateBinary();
    s_semaphore_2 = xSemaphoreCreateBinary();
    s_semaphore_3 = xSemaphoreCreateBinary();
    s_semaphore_4 = xSemaphoreCreateBinary();

    s_mutex_0 = xSemaphoreCreateMutex();
    s_mutex_1 = xSemaphoreCreateMutex();
    s_mutex_2 = xSemaphoreCreateMutex();
    s_mutex_3 = xSemaphoreCreateMutex();
    s_mutex_4 = xSemaphoreCreateMutex();

    s_queue_0 = xQueueCreate(RTOS_QUEUE_0_LENGTH, sizeof(RTOS_QUEUE_0_ITEM_TYPE));
    s_queue_1 = xQueueCreate(RTOS_QUEUE_1_LENGTH, sizeof(RTOS_QUEUE_1_ITEM_TYPE));
    s_queue_2 = xQueueCreate(RTOS_QUEUE_2_LENGTH, sizeof(RTOS_QUEUE_2_ITEM_TYPE));
    s_queue_3 = xQueueCreate(RTOS_QUEUE_3_LENGTH, sizeof(RTOS_QUEUE_3_ITEM_TYPE));
    s_queue_4 = xQueueCreate(RTOS_QUEUE_4_LENGTH, sizeof(RTOS_QUEUE_4_ITEM_TYPE));

    s_event_group_0 = xEventGroupCreate();
    s_event_group_1 = xEventGroupCreate();

    s_timer_0 = xTimerCreate(RTOS_TIMER_0_NAME,
                             pdMS_TO_TICKS(RTOS_TIMER_0_PERIOD_MS),
                             pdTRUE,
                             NULL,
                             timer_0_callback);
    s_timer_1 = xTimerCreate(RTOS_TIMER_1_NAME,
                             pdMS_TO_TICKS(RTOS_TIMER_1_PERIOD_MS),
                             pdTRUE,
                             NULL,
                             timer_1_callback);

    object_missing = (s_semaphore_0 == NULL) || (s_semaphore_1 == NULL) ||
                     (s_semaphore_2 == NULL) || (s_semaphore_3 == NULL) ||
                     (s_semaphore_4 == NULL) || (s_mutex_0 == NULL) || (s_mutex_1 == NULL) ||
                     (s_mutex_2 == NULL) || (s_mutex_3 == NULL) || (s_mutex_4 == NULL) ||
                     (s_queue_0 == NULL) || (s_queue_1 == NULL) || (s_queue_2 == NULL) ||
                     (s_queue_3 == NULL) || (s_queue_4 == NULL) || (s_event_group_0 == NULL) ||
                     (s_event_group_1 == NULL) || (s_timer_0 == NULL) || (s_timer_1 == NULL);
    if(object_missing)
    {
        return pdFAIL;
    }

    return pdPASS;
}

static BaseType_t rtos_timers_start(void)
{
    bool       start_failed;
    BaseType_t start_result;

    start_result = xTimerStart(s_timer_0, 0U);
    start_failed = start_result != pdPASS;
    if(start_failed)
    {
        return pdFAIL;
    }

    start_result = xTimerStart(s_timer_1, 0U);
    start_failed = start_result != pdPASS;
    if(start_failed)
    {
        return pdFAIL;
    }

    return pdPASS;
}

static BaseType_t rtos_tasks_create(void)
{
    bool       create_failed;
    BaseType_t create_result;

    create_result = xTaskCreate(task_0,
                                RTOS_TASK_0_NAME,
                                RTOS_TASK_0_STACK_DEPTH,
                                NULL,
                                RTOS_TASK_0_PRIORITY,
                                &s_task_0_handle);
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        return pdFAIL;
    }

    create_result = xTaskCreate(task_1,
                                RTOS_TASK_1_NAME,
                                RTOS_TASK_1_STACK_DEPTH,
                                NULL,
                                RTOS_TASK_1_PRIORITY,
                                &s_task_1_handle);
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        return pdFAIL;
    }

    create_result = xTaskCreate(task_2,
                                RTOS_TASK_2_NAME,
                                RTOS_TASK_2_STACK_DEPTH,
                                NULL,
                                RTOS_TASK_2_PRIORITY,
                                &s_task_2_handle);
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        return pdFAIL;
    }

    create_result = xTaskCreate(task_3,
                                RTOS_TASK_3_NAME,
                                RTOS_TASK_3_STACK_DEPTH,
                                NULL,
                                RTOS_TASK_3_PRIORITY,
                                &s_task_3_handle);
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        return pdFAIL;
    }

    create_result = xTaskCreate(task_4,
                                RTOS_TASK_4_NAME,
                                RTOS_TASK_4_STACK_DEPTH,
                                NULL,
                                RTOS_TASK_4_PRIORITY,
                                &s_task_4_handle);
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        return pdFAIL;
    }

    return pdPASS;
}

static void task_0(void *argument)
{
    (void)argument;

    for(;;)
    {
        (void)xEventGroupWaitBits(s_event_group_0,
                                  RTOS_EVENT_GROUP_0_TIMER_BIT,
                                  pdTRUE,
                                  pdTRUE,
                                  portMAX_DELAY);
    }
}

static void task_1(void *argument)
{
    (void)argument;

    for(;;)
    {
        (void)xEventGroupWaitBits(s_event_group_1,
                                  RTOS_EVENT_GROUP_1_TIMER_BIT,
                                  pdTRUE,
                                  pdTRUE,
                                  portMAX_DELAY);
    }
}

static void task_2(void *argument)
{
    (void)argument;

    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(RTOS_TASK_2_PERIOD_MS));
    }
}

static void task_3(void *argument)
{
    (void)argument;

    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(RTOS_TASK_3_PERIOD_MS));
    }
}

static void task_4(void *argument)
{
    (void)argument;
    led_run();
}

static void timer_0_callback(TimerHandle_t timer)
{
    (void)timer;
    (void)xEventGroupSetBits(s_event_group_0, RTOS_EVENT_GROUP_0_TIMER_BIT);
}

static void timer_1_callback(TimerHandle_t timer)
{
    (void)timer;
    (void)xEventGroupSetBits(s_event_group_1, RTOS_EVENT_GROUP_1_TIMER_BIT);
}

static void rtos_fatal_error(void)
{
    taskDISABLE_INTERRUPTS();

    for(;;)
    {
    }
}

void vApplicationMallocFailedHook(void)
{
    rtos_fatal_error();
}

void vApplicationStackOverflowHook(TaskHandle_t task, char *task_name)
{
    (void)task;
    (void)task_name;
    rtos_fatal_error();
}
