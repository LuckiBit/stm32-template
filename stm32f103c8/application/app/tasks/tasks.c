/**
 * @file tasks.c
 * @brief Owns numbered RTOS template resources, including unused expansion slots.
 */

#include "tasks.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "led.h"
#include "queue.h"
#include "semphr.h"
#include "system_manager.h"
#include "task.h"
#include "timers.h"

#include <stdbool.h>
#include <stdint.h>

/** Numbered names are intentional template slots requested for product expansion.
 * Stack depths use StackType_t units. Task count does not determine priority count.
 */
#define TASK_NAME_0        "task_0"
#define TASK_STACK_DEPTH_0 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_0    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_1        "task_1"
#define TASK_STACK_DEPTH_1 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_1    (tskIDLE_PRIORITY + 2U)

#define TASK_NAME_2        "task_2"
#define TASK_STACK_DEPTH_2 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_2    (tskIDLE_PRIORITY + 3U)

#define TASK_NAME_3        "task_3"
#define TASK_STACK_DEPTH_3 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_3    (tskIDLE_PRIORITY + 4U)

#define TASK_NAME_4        "task_4"
#define TASK_STACK_DEPTH_4 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_4    (tskIDLE_PRIORITY + 5U)

#define TASK_NAME_5        "task_5"
#define TASK_STACK_DEPTH_5 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_5    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_6        "task_6"
#define TASK_STACK_DEPTH_6 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_6    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_7        "task_7"
#define TASK_STACK_DEPTH_7 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_7    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_8        "task_8"
#define TASK_STACK_DEPTH_8 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_8    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_9        "task_9"
#define TASK_STACK_DEPTH_9 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_9    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_10        "task_10"
#define TASK_STACK_DEPTH_10 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_10    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_11        "task_11"
#define TASK_STACK_DEPTH_11 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_11    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_12        "task_12"
#define TASK_STACK_DEPTH_12 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_12    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_13        "task_13"
#define TASK_STACK_DEPTH_13 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_13    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_14        "task_14"
#define TASK_STACK_DEPTH_14 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_14    (tskIDLE_PRIORITY + 1U)

#define TASK_NAME_15        "task_15"
#define TASK_STACK_DEPTH_15 configMINIMAL_STACK_SIZE
#define TASK_PRIORITY_15    (tskIDLE_PRIORITY + 1U)

#define QUEUE_LENGTH_0    5U
#define QUEUE_ITEM_TYPE_0 uint32_t
#define QUEUE_LENGTH_1    5U
#define QUEUE_ITEM_TYPE_1 uint32_t
#define QUEUE_LENGTH_2    5U
#define QUEUE_ITEM_TYPE_2 uint32_t
#define QUEUE_LENGTH_3    5U
#define QUEUE_ITEM_TYPE_3 uint32_t
#define QUEUE_LENGTH_4    5U
#define QUEUE_ITEM_TYPE_4 uint32_t
#define QUEUE_LENGTH_5    5U
#define QUEUE_ITEM_TYPE_5 uint32_t
#define QUEUE_LENGTH_6    5U
#define QUEUE_ITEM_TYPE_6 uint32_t
#define QUEUE_LENGTH_7    5U
#define QUEUE_ITEM_TYPE_7 uint32_t

#define TIMER_NAME_0      "timer_0"
#define TIMER_PERIOD_MS_0 500U
#define TIMER_NAME_1      "timer_1"
#define TIMER_PERIOD_MS_1 1000U
#define TIMER_NAME_2      "timer_2"
#define TIMER_PERIOD_MS_2 1000U
#define TIMER_NAME_3      "timer_3"
#define TIMER_PERIOD_MS_3 1000U

#define EVENT_TIMER_BIT_0 ((EventBits_t)(1U << 0))
#define EVENT_TIMER_BIT_1 ((EventBits_t)(1U << 0))

#if QUEUE_ENABLE_0
static uint8_t s_queue_storage_0[QUEUE_LENGTH_0 * sizeof(QUEUE_ITEM_TYPE_0)];
#endif
#if QUEUE_ENABLE_1
static uint8_t s_queue_storage_1[QUEUE_LENGTH_1 * sizeof(QUEUE_ITEM_TYPE_1)];
#endif
#if QUEUE_ENABLE_2
static uint8_t s_queue_storage_2[QUEUE_LENGTH_2 * sizeof(QUEUE_ITEM_TYPE_2)];
#endif
#if QUEUE_ENABLE_3
static uint8_t s_queue_storage_3[QUEUE_LENGTH_3 * sizeof(QUEUE_ITEM_TYPE_3)];
#endif
#if QUEUE_ENABLE_4
static uint8_t s_queue_storage_4[QUEUE_LENGTH_4 * sizeof(QUEUE_ITEM_TYPE_4)];
#endif
#if QUEUE_ENABLE_5
static uint8_t s_queue_storage_5[QUEUE_LENGTH_5 * sizeof(QUEUE_ITEM_TYPE_5)];
#endif
#if QUEUE_ENABLE_6
static uint8_t s_queue_storage_6[QUEUE_LENGTH_6 * sizeof(QUEUE_ITEM_TYPE_6)];
#endif
#if QUEUE_ENABLE_7
static uint8_t s_queue_storage_7[QUEUE_LENGTH_7 * sizeof(QUEUE_ITEM_TYPE_7)];
#endif
#if TASK_ENABLE_0
static StackType_t s_task_stack_0[TASK_STACK_DEPTH_0];
#endif
#if TASK_ENABLE_1
static StackType_t s_task_stack_1[TASK_STACK_DEPTH_1];
#endif
#if TASK_ENABLE_2
static StackType_t s_task_stack_2[TASK_STACK_DEPTH_2];
#endif
#if TASK_ENABLE_3
static StackType_t s_task_stack_3[TASK_STACK_DEPTH_3];
#endif
#if TASK_ENABLE_4
static StackType_t s_task_stack_4[TASK_STACK_DEPTH_4];
#endif
#if TASK_ENABLE_5
static StackType_t s_task_stack_5[TASK_STACK_DEPTH_5];
#endif
#if TASK_ENABLE_6
static StackType_t s_task_stack_6[TASK_STACK_DEPTH_6];
#endif
#if TASK_ENABLE_7
static StackType_t s_task_stack_7[TASK_STACK_DEPTH_7];
#endif
#if TASK_ENABLE_8
static StackType_t s_task_stack_8[TASK_STACK_DEPTH_8];
#endif
#if TASK_ENABLE_9
static StackType_t s_task_stack_9[TASK_STACK_DEPTH_9];
#endif
#if TASK_ENABLE_10
static StackType_t s_task_stack_10[TASK_STACK_DEPTH_10];
#endif
#if TASK_ENABLE_11
static StackType_t s_task_stack_11[TASK_STACK_DEPTH_11];
#endif
#if TASK_ENABLE_12
static StackType_t s_task_stack_12[TASK_STACK_DEPTH_12];
#endif
#if TASK_ENABLE_13
static StackType_t s_task_stack_13[TASK_STACK_DEPTH_13];
#endif
#if TASK_ENABLE_14
static StackType_t s_task_stack_14[TASK_STACK_DEPTH_14];
#endif
#if TASK_ENABLE_15
static StackType_t s_task_stack_15[TASK_STACK_DEPTH_15];
#endif

#if TASK_ENABLE_0
static StaticTask_t s_task_buffer_0;
#endif
#if TASK_ENABLE_1
static StaticTask_t s_task_buffer_1;
#endif
#if TASK_ENABLE_2
static StaticTask_t s_task_buffer_2;
#endif
#if TASK_ENABLE_3
static StaticTask_t s_task_buffer_3;
#endif
#if TASK_ENABLE_4
static StaticTask_t s_task_buffer_4;
#endif
#if TASK_ENABLE_5
static StaticTask_t s_task_buffer_5;
#endif
#if TASK_ENABLE_6
static StaticTask_t s_task_buffer_6;
#endif
#if TASK_ENABLE_7
static StaticTask_t s_task_buffer_7;
#endif
#if TASK_ENABLE_8
static StaticTask_t s_task_buffer_8;
#endif
#if TASK_ENABLE_9
static StaticTask_t s_task_buffer_9;
#endif
#if TASK_ENABLE_10
static StaticTask_t s_task_buffer_10;
#endif
#if TASK_ENABLE_11
static StaticTask_t s_task_buffer_11;
#endif
#if TASK_ENABLE_12
static StaticTask_t s_task_buffer_12;
#endif
#if TASK_ENABLE_13
static StaticTask_t s_task_buffer_13;
#endif
#if TASK_ENABLE_14
static StaticTask_t s_task_buffer_14;
#endif
#if TASK_ENABLE_15
static StaticTask_t s_task_buffer_15;
#endif

#if SEMAPHORE_ENABLE_0
static StaticSemaphore_t s_semaphore_buffer_0;
#endif
#if SEMAPHORE_ENABLE_1
static StaticSemaphore_t s_semaphore_buffer_1;
#endif
#if SEMAPHORE_ENABLE_2
static StaticSemaphore_t s_semaphore_buffer_2;
#endif
#if SEMAPHORE_ENABLE_3
static StaticSemaphore_t s_semaphore_buffer_3;
#endif
#if SEMAPHORE_ENABLE_4
static StaticSemaphore_t s_semaphore_buffer_4;
#endif
#if SEMAPHORE_ENABLE_5
static StaticSemaphore_t s_semaphore_buffer_5;
#endif
#if SEMAPHORE_ENABLE_6
static StaticSemaphore_t s_semaphore_buffer_6;
#endif
#if SEMAPHORE_ENABLE_7
static StaticSemaphore_t s_semaphore_buffer_7;
#endif

#if MUTEX_ENABLE_0
static StaticSemaphore_t s_mutex_buffer_0;
#endif
#if MUTEX_ENABLE_1
static StaticSemaphore_t s_mutex_buffer_1;
#endif
#if MUTEX_ENABLE_2
static StaticSemaphore_t s_mutex_buffer_2;
#endif
#if MUTEX_ENABLE_3
static StaticSemaphore_t s_mutex_buffer_3;
#endif
#if MUTEX_ENABLE_4
static StaticSemaphore_t s_mutex_buffer_4;
#endif
#if MUTEX_ENABLE_5
static StaticSemaphore_t s_mutex_buffer_5;
#endif
#if MUTEX_ENABLE_6
static StaticSemaphore_t s_mutex_buffer_6;
#endif
#if MUTEX_ENABLE_7
static StaticSemaphore_t s_mutex_buffer_7;
#endif

#if QUEUE_ENABLE_0
static StaticQueue_t s_queue_buffer_0;
#endif
#if QUEUE_ENABLE_1
static StaticQueue_t s_queue_buffer_1;
#endif
#if QUEUE_ENABLE_2
static StaticQueue_t s_queue_buffer_2;
#endif
#if QUEUE_ENABLE_3
static StaticQueue_t s_queue_buffer_3;
#endif
#if QUEUE_ENABLE_4
static StaticQueue_t s_queue_buffer_4;
#endif
#if QUEUE_ENABLE_5
static StaticQueue_t s_queue_buffer_5;
#endif
#if QUEUE_ENABLE_6
static StaticQueue_t s_queue_buffer_6;
#endif
#if QUEUE_ENABLE_7
static StaticQueue_t s_queue_buffer_7;
#endif

#if EVENT_GROUP_ENABLE_0
static StaticEventGroup_t s_event_group_buffer_0;
#endif
#if EVENT_GROUP_ENABLE_1
static StaticEventGroup_t s_event_group_buffer_1;
#endif
#if EVENT_GROUP_ENABLE_2
static StaticEventGroup_t s_event_group_buffer_2;
#endif
#if EVENT_GROUP_ENABLE_3
static StaticEventGroup_t s_event_group_buffer_3;
#endif

#if TIMER_ENABLE_0
static StaticTimer_t s_timer_buffer_0;
#endif
#if TIMER_ENABLE_1
static StaticTimer_t s_timer_buffer_1;
#endif
#if TIMER_ENABLE_2
static StaticTimer_t s_timer_buffer_2;
#endif
#if TIMER_ENABLE_3
static StaticTimer_t s_timer_buffer_3;
#endif

#if TASK_ENABLE_0
static TaskHandle_t s_task_handle_0 = NULL;
#endif
#if TASK_ENABLE_1
static TaskHandle_t s_task_handle_1 = NULL;
#endif
#if TASK_ENABLE_2
static TaskHandle_t s_task_handle_2 = NULL;
#endif
#if TASK_ENABLE_3
static TaskHandle_t s_task_handle_3 = NULL;
#endif
#if TASK_ENABLE_4
static TaskHandle_t s_task_handle_4 = NULL;
#endif
#if TASK_ENABLE_5
static TaskHandle_t s_task_handle_5 = NULL;
#endif
#if TASK_ENABLE_6
static TaskHandle_t s_task_handle_6 = NULL;
#endif
#if TASK_ENABLE_7
static TaskHandle_t s_task_handle_7 = NULL;
#endif
#if TASK_ENABLE_8
static TaskHandle_t s_task_handle_8 = NULL;
#endif
#if TASK_ENABLE_9
static TaskHandle_t s_task_handle_9 = NULL;
#endif
#if TASK_ENABLE_10
static TaskHandle_t s_task_handle_10 = NULL;
#endif
#if TASK_ENABLE_11
static TaskHandle_t s_task_handle_11 = NULL;
#endif
#if TASK_ENABLE_12
static TaskHandle_t s_task_handle_12 = NULL;
#endif
#if TASK_ENABLE_13
static TaskHandle_t s_task_handle_13 = NULL;
#endif
#if TASK_ENABLE_14
static TaskHandle_t s_task_handle_14 = NULL;
#endif
#if TASK_ENABLE_15
static TaskHandle_t s_task_handle_15 = NULL;
#endif

#if SEMAPHORE_ENABLE_0
static SemaphoreHandle_t s_semaphore_handle_0 = NULL;
#endif
#if SEMAPHORE_ENABLE_1
static SemaphoreHandle_t s_semaphore_handle_1 = NULL;
#endif
#if SEMAPHORE_ENABLE_2
static SemaphoreHandle_t s_semaphore_handle_2 = NULL;
#endif
#if SEMAPHORE_ENABLE_3
static SemaphoreHandle_t s_semaphore_handle_3 = NULL;
#endif
#if SEMAPHORE_ENABLE_4
static SemaphoreHandle_t s_semaphore_handle_4 = NULL;
#endif
#if SEMAPHORE_ENABLE_5
static SemaphoreHandle_t s_semaphore_handle_5 = NULL;
#endif
#if SEMAPHORE_ENABLE_6
static SemaphoreHandle_t s_semaphore_handle_6 = NULL;
#endif
#if SEMAPHORE_ENABLE_7
static SemaphoreHandle_t s_semaphore_handle_7 = NULL;
#endif

#if MUTEX_ENABLE_0
static SemaphoreHandle_t s_mutex_handle_0 = NULL;
#endif
#if MUTEX_ENABLE_1
static SemaphoreHandle_t s_mutex_handle_1 = NULL;
#endif
#if MUTEX_ENABLE_2
static SemaphoreHandle_t s_mutex_handle_2 = NULL;
#endif
#if MUTEX_ENABLE_3
static SemaphoreHandle_t s_mutex_handle_3 = NULL;
#endif
#if MUTEX_ENABLE_4
static SemaphoreHandle_t s_mutex_handle_4 = NULL;
#endif
#if MUTEX_ENABLE_5
static SemaphoreHandle_t s_mutex_handle_5 = NULL;
#endif
#if MUTEX_ENABLE_6
static SemaphoreHandle_t s_mutex_handle_6 = NULL;
#endif
#if MUTEX_ENABLE_7
static SemaphoreHandle_t s_mutex_handle_7 = NULL;
#endif

#if QUEUE_ENABLE_0
static QueueHandle_t s_queue_handle_0 = NULL;
#endif
#if QUEUE_ENABLE_1
static QueueHandle_t s_queue_handle_1 = NULL;
#endif
#if QUEUE_ENABLE_2
static QueueHandle_t s_queue_handle_2 = NULL;
#endif
#if QUEUE_ENABLE_3
static QueueHandle_t s_queue_handle_3 = NULL;
#endif
#if QUEUE_ENABLE_4
static QueueHandle_t s_queue_handle_4 = NULL;
#endif
#if QUEUE_ENABLE_5
static QueueHandle_t s_queue_handle_5 = NULL;
#endif
#if QUEUE_ENABLE_6
static QueueHandle_t s_queue_handle_6 = NULL;
#endif
#if QUEUE_ENABLE_7
static QueueHandle_t s_queue_handle_7 = NULL;
#endif

#if EVENT_GROUP_ENABLE_0
static EventGroupHandle_t s_event_group_handle_0 = NULL;
#endif
#if EVENT_GROUP_ENABLE_1
static EventGroupHandle_t s_event_group_handle_1 = NULL;
#endif
#if EVENT_GROUP_ENABLE_2
static EventGroupHandle_t s_event_group_handle_2 = NULL;
#endif
#if EVENT_GROUP_ENABLE_3
static EventGroupHandle_t s_event_group_handle_3 = NULL;
#endif

#if TIMER_ENABLE_0
static TimerHandle_t s_timer_handle_0 = NULL;
#endif
#if TIMER_ENABLE_1
static TimerHandle_t s_timer_handle_1 = NULL;
#endif
#if TIMER_ENABLE_2
static TimerHandle_t s_timer_handle_2 = NULL;
#endif
#if TIMER_ENABLE_3
static TimerHandle_t s_timer_handle_3 = NULL;
#endif

#if TASK_ENABLE_0
static void task_0(void *argument);
#endif
#if TASK_ENABLE_1
static void task_1(void *argument);
#endif
#if TASK_ENABLE_2
static void task_2(void *argument);
#endif
#if TASK_ENABLE_3
static void task_3(void *argument);
#endif
#if TASK_ENABLE_4
static void task_4(void *argument);
#endif
#if TASK_ENABLE_5
static void task_5(void *argument);
#endif
#if TASK_ENABLE_6
static void task_6(void *argument);
#endif
#if TASK_ENABLE_7
static void task_7(void *argument);
#endif
#if TASK_ENABLE_8
static void task_8(void *argument);
#endif
#if TASK_ENABLE_9
static void task_9(void *argument);
#endif
#if TASK_ENABLE_10
static void task_10(void *argument);
#endif
#if TASK_ENABLE_11
static void task_11(void *argument);
#endif
#if TASK_ENABLE_12
static void task_12(void *argument);
#endif
#if TASK_ENABLE_13
static void task_13(void *argument);
#endif
#if TASK_ENABLE_14
static void task_14(void *argument);
#endif
#if TASK_ENABLE_15
static void task_15(void *argument);
#endif
#if TIMER_ENABLE_0
static void timer_callback_0(TimerHandle_t timer);
#endif
#if TIMER_ENABLE_1
static void timer_callback_1(TimerHandle_t timer);
#endif
#if TIMER_ENABLE_2
static void timer_callback_2(TimerHandle_t timer);
#endif
#if TIMER_ENABLE_3
static void timer_callback_3(TimerHandle_t timer);
#endif

static BaseType_t create_objects(void);
static BaseType_t create_tasks(void);
static BaseType_t start_timers(void);

bool tasks_create(void)
{
    bool       create_failed    = false;
    bool       create_succeeded = false;
    BaseType_t create_result    = create_objects();

    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        return false;
    }
    create_result    = create_tasks();
    create_succeeded = create_result == pdPASS;
    return create_succeeded;
}

bool tasks_start(void)
{
    bool       start_succeeded = false;
    BaseType_t start_result    = start_timers();

    start_succeeded = start_result == pdPASS;
    return start_succeeded;
}

static BaseType_t create_objects(void)
{
#if SEMAPHORE_ENABLE_0
    {
        bool object_missing = false;

        s_semaphore_handle_0 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_0);
        object_missing       = s_semaphore_handle_0 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if SEMAPHORE_ENABLE_1
    {
        bool object_missing = false;

        s_semaphore_handle_1 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_1);
        object_missing       = s_semaphore_handle_1 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if SEMAPHORE_ENABLE_2
    {
        bool object_missing = false;

        s_semaphore_handle_2 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_2);
        object_missing       = s_semaphore_handle_2 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if SEMAPHORE_ENABLE_3
    {
        bool object_missing = false;

        s_semaphore_handle_3 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_3);
        object_missing       = s_semaphore_handle_3 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if SEMAPHORE_ENABLE_4
    {
        bool object_missing = false;

        s_semaphore_handle_4 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_4);
        object_missing       = s_semaphore_handle_4 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if SEMAPHORE_ENABLE_5
    {
        bool object_missing = false;

        s_semaphore_handle_5 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_5);
        object_missing       = s_semaphore_handle_5 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if SEMAPHORE_ENABLE_6
    {
        bool object_missing = false;

        s_semaphore_handle_6 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_6);
        object_missing       = s_semaphore_handle_6 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if SEMAPHORE_ENABLE_7
    {
        bool object_missing = false;

        s_semaphore_handle_7 = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer_7);
        object_missing       = s_semaphore_handle_7 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_0
    {
        bool object_missing = false;

        s_mutex_handle_0 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_0);
        object_missing   = s_mutex_handle_0 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_1
    {
        bool object_missing = false;

        s_mutex_handle_1 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_1);
        object_missing   = s_mutex_handle_1 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_2
    {
        bool object_missing = false;

        s_mutex_handle_2 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_2);
        object_missing   = s_mutex_handle_2 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_3
    {
        bool object_missing = false;

        s_mutex_handle_3 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_3);
        object_missing   = s_mutex_handle_3 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_4
    {
        bool object_missing = false;

        s_mutex_handle_4 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_4);
        object_missing   = s_mutex_handle_4 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_5
    {
        bool object_missing = false;

        s_mutex_handle_5 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_5);
        object_missing   = s_mutex_handle_5 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_6
    {
        bool object_missing = false;

        s_mutex_handle_6 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_6);
        object_missing   = s_mutex_handle_6 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if MUTEX_ENABLE_7
    {
        bool object_missing = false;

        s_mutex_handle_7 = xSemaphoreCreateMutexStatic(&s_mutex_buffer_7);
        object_missing   = s_mutex_handle_7 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_0
    {
        bool object_missing = false;

        s_queue_handle_0 = xQueueCreateStatic(QUEUE_LENGTH_0,
                                              sizeof(QUEUE_ITEM_TYPE_0),
                                              s_queue_storage_0,
                                              &s_queue_buffer_0);
        object_missing   = s_queue_handle_0 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_1
    {
        bool object_missing = false;

        s_queue_handle_1 = xQueueCreateStatic(QUEUE_LENGTH_1,
                                              sizeof(QUEUE_ITEM_TYPE_1),
                                              s_queue_storage_1,
                                              &s_queue_buffer_1);
        object_missing   = s_queue_handle_1 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_2
    {
        bool object_missing = false;

        s_queue_handle_2 = xQueueCreateStatic(QUEUE_LENGTH_2,
                                              sizeof(QUEUE_ITEM_TYPE_2),
                                              s_queue_storage_2,
                                              &s_queue_buffer_2);
        object_missing   = s_queue_handle_2 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_3
    {
        bool object_missing = false;

        s_queue_handle_3 = xQueueCreateStatic(QUEUE_LENGTH_3,
                                              sizeof(QUEUE_ITEM_TYPE_3),
                                              s_queue_storage_3,
                                              &s_queue_buffer_3);
        object_missing   = s_queue_handle_3 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_4
    {
        bool object_missing = false;

        s_queue_handle_4 = xQueueCreateStatic(QUEUE_LENGTH_4,
                                              sizeof(QUEUE_ITEM_TYPE_4),
                                              s_queue_storage_4,
                                              &s_queue_buffer_4);
        object_missing   = s_queue_handle_4 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_5
    {
        bool object_missing = false;

        s_queue_handle_5 = xQueueCreateStatic(QUEUE_LENGTH_5,
                                              sizeof(QUEUE_ITEM_TYPE_5),
                                              s_queue_storage_5,
                                              &s_queue_buffer_5);
        object_missing   = s_queue_handle_5 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_6
    {
        bool object_missing = false;

        s_queue_handle_6 = xQueueCreateStatic(QUEUE_LENGTH_6,
                                              sizeof(QUEUE_ITEM_TYPE_6),
                                              s_queue_storage_6,
                                              &s_queue_buffer_6);
        object_missing   = s_queue_handle_6 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if QUEUE_ENABLE_7
    {
        bool object_missing = false;

        s_queue_handle_7 = xQueueCreateStatic(QUEUE_LENGTH_7,
                                              sizeof(QUEUE_ITEM_TYPE_7),
                                              s_queue_storage_7,
                                              &s_queue_buffer_7);
        object_missing   = s_queue_handle_7 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if EVENT_GROUP_ENABLE_0
    {
        bool object_missing = false;

        s_event_group_handle_0 = xEventGroupCreateStatic(&s_event_group_buffer_0);
        object_missing         = s_event_group_handle_0 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if EVENT_GROUP_ENABLE_1
    {
        bool object_missing = false;

        s_event_group_handle_1 = xEventGroupCreateStatic(&s_event_group_buffer_1);
        object_missing         = s_event_group_handle_1 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if EVENT_GROUP_ENABLE_2
    {
        bool object_missing = false;

        s_event_group_handle_2 = xEventGroupCreateStatic(&s_event_group_buffer_2);
        object_missing         = s_event_group_handle_2 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if EVENT_GROUP_ENABLE_3
    {
        bool object_missing = false;

        s_event_group_handle_3 = xEventGroupCreateStatic(&s_event_group_buffer_3);
        object_missing         = s_event_group_handle_3 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if TIMER_ENABLE_0
    {
        bool object_missing = false;

        s_timer_handle_0 = xTimerCreateStatic(TIMER_NAME_0,
                                              pdMS_TO_TICKS(TIMER_PERIOD_MS_0),
                                              pdTRUE,
                                              NULL,
                                              timer_callback_0,
                                              &s_timer_buffer_0);
        object_missing   = s_timer_handle_0 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if TIMER_ENABLE_1
    {
        bool object_missing = false;

        s_timer_handle_1 = xTimerCreateStatic(TIMER_NAME_1,
                                              pdMS_TO_TICKS(TIMER_PERIOD_MS_1),
                                              pdTRUE,
                                              NULL,
                                              timer_callback_1,
                                              &s_timer_buffer_1);
        object_missing   = s_timer_handle_1 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if TIMER_ENABLE_2
    {
        bool object_missing = false;

        s_timer_handle_2 = xTimerCreateStatic(TIMER_NAME_2,
                                              pdMS_TO_TICKS(TIMER_PERIOD_MS_2),
                                              pdTRUE,
                                              NULL,
                                              timer_callback_2,
                                              &s_timer_buffer_2);
        object_missing   = s_timer_handle_2 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
#if TIMER_ENABLE_3
    {
        bool object_missing = false;

        s_timer_handle_3 = xTimerCreateStatic(TIMER_NAME_3,
                                              pdMS_TO_TICKS(TIMER_PERIOD_MS_3),
                                              pdTRUE,
                                              NULL,
                                              timer_callback_3,
                                              &s_timer_buffer_3);
        object_missing   = s_timer_handle_3 == NULL;
        if(object_missing)
        {
            return pdFAIL;
        }
    }
#endif
    return pdPASS;
}

static BaseType_t create_tasks(void)
{
#if TASK_ENABLED_COUNT > 0
    bool task_missing = false;
#endif

#if TASK_ENABLE_0
    s_task_handle_0 = xTaskCreateStatic(task_0,
                                        TASK_NAME_0,
                                        TASK_STACK_DEPTH_0,
                                        NULL,
                                        TASK_PRIORITY_0,
                                        s_task_stack_0,
                                        &s_task_buffer_0);
    task_missing    = s_task_handle_0 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_1
    s_task_handle_1 = xTaskCreateStatic(task_1,
                                        TASK_NAME_1,
                                        TASK_STACK_DEPTH_1,
                                        NULL,
                                        TASK_PRIORITY_1,
                                        s_task_stack_1,
                                        &s_task_buffer_1);
    task_missing    = s_task_handle_1 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_2
    s_task_handle_2 = xTaskCreateStatic(task_2,
                                        TASK_NAME_2,
                                        TASK_STACK_DEPTH_2,
                                        NULL,
                                        TASK_PRIORITY_2,
                                        s_task_stack_2,
                                        &s_task_buffer_2);
    task_missing    = s_task_handle_2 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_3
    s_task_handle_3 = xTaskCreateStatic(task_3,
                                        TASK_NAME_3,
                                        TASK_STACK_DEPTH_3,
                                        NULL,
                                        TASK_PRIORITY_3,
                                        s_task_stack_3,
                                        &s_task_buffer_3);
    task_missing    = s_task_handle_3 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_4
    s_task_handle_4 = xTaskCreateStatic(task_4,
                                        TASK_NAME_4,
                                        TASK_STACK_DEPTH_4,
                                        NULL,
                                        TASK_PRIORITY_4,
                                        s_task_stack_4,
                                        &s_task_buffer_4);
    task_missing    = s_task_handle_4 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_5
    s_task_handle_5 = xTaskCreateStatic(task_5,
                                        TASK_NAME_5,
                                        TASK_STACK_DEPTH_5,
                                        NULL,
                                        TASK_PRIORITY_5,
                                        s_task_stack_5,
                                        &s_task_buffer_5);
    task_missing    = s_task_handle_5 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_6
    s_task_handle_6 = xTaskCreateStatic(task_6,
                                        TASK_NAME_6,
                                        TASK_STACK_DEPTH_6,
                                        NULL,
                                        TASK_PRIORITY_6,
                                        s_task_stack_6,
                                        &s_task_buffer_6);
    task_missing    = s_task_handle_6 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_7
    s_task_handle_7 = xTaskCreateStatic(task_7,
                                        TASK_NAME_7,
                                        TASK_STACK_DEPTH_7,
                                        NULL,
                                        TASK_PRIORITY_7,
                                        s_task_stack_7,
                                        &s_task_buffer_7);
    task_missing    = s_task_handle_7 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_8
    s_task_handle_8 = xTaskCreateStatic(task_8,
                                        TASK_NAME_8,
                                        TASK_STACK_DEPTH_8,
                                        NULL,
                                        TASK_PRIORITY_8,
                                        s_task_stack_8,
                                        &s_task_buffer_8);
    task_missing    = s_task_handle_8 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_9
    s_task_handle_9 = xTaskCreateStatic(task_9,
                                        TASK_NAME_9,
                                        TASK_STACK_DEPTH_9,
                                        NULL,
                                        TASK_PRIORITY_9,
                                        s_task_stack_9,
                                        &s_task_buffer_9);
    task_missing    = s_task_handle_9 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_10
    s_task_handle_10 = xTaskCreateStatic(task_10,
                                         TASK_NAME_10,
                                         TASK_STACK_DEPTH_10,
                                         NULL,
                                         TASK_PRIORITY_10,
                                         s_task_stack_10,
                                         &s_task_buffer_10);
    task_missing     = s_task_handle_10 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_11
    s_task_handle_11 = xTaskCreateStatic(task_11,
                                         TASK_NAME_11,
                                         TASK_STACK_DEPTH_11,
                                         NULL,
                                         TASK_PRIORITY_11,
                                         s_task_stack_11,
                                         &s_task_buffer_11);
    task_missing     = s_task_handle_11 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_12
    s_task_handle_12 = xTaskCreateStatic(task_12,
                                         TASK_NAME_12,
                                         TASK_STACK_DEPTH_12,
                                         NULL,
                                         TASK_PRIORITY_12,
                                         s_task_stack_12,
                                         &s_task_buffer_12);
    task_missing     = s_task_handle_12 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_13
    s_task_handle_13 = xTaskCreateStatic(task_13,
                                         TASK_NAME_13,
                                         TASK_STACK_DEPTH_13,
                                         NULL,
                                         TASK_PRIORITY_13,
                                         s_task_stack_13,
                                         &s_task_buffer_13);
    task_missing     = s_task_handle_13 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_14
    s_task_handle_14 = xTaskCreateStatic(task_14,
                                         TASK_NAME_14,
                                         TASK_STACK_DEPTH_14,
                                         NULL,
                                         TASK_PRIORITY_14,
                                         s_task_stack_14,
                                         &s_task_buffer_14);
    task_missing     = s_task_handle_14 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

#if TASK_ENABLE_15
    s_task_handle_15 = xTaskCreateStatic(task_15,
                                         TASK_NAME_15,
                                         TASK_STACK_DEPTH_15,
                                         NULL,
                                         TASK_PRIORITY_15,
                                         s_task_stack_15,
                                         &s_task_buffer_15);
    task_missing     = s_task_handle_15 == NULL;
    if(task_missing)
    {
        return pdFAIL;
    }
#endif

    return pdPASS;
}

static BaseType_t start_timers(void)
{
#if TASK_SOFTWARE_TIMERS_ENABLED
    bool       start_failed = false;
    BaseType_t start_result = pdFAIL;
#endif
#if TIMER_ENABLE_0
    start_result = xTimerStart(s_timer_handle_0, 0U);
    start_failed = start_result != pdPASS;
    if(start_failed)
    {
        return pdFAIL;
    }
#endif
#if TIMER_ENABLE_1
    start_result = xTimerStart(s_timer_handle_1, 0U);
    start_failed = start_result != pdPASS;
    if(start_failed)
    {
        return pdFAIL;
    }
#endif
#if TIMER_ENABLE_2
    start_result = xTimerStart(s_timer_handle_2, 0U);
    start_failed = start_result != pdPASS;
    if(start_failed)
    {
        return pdFAIL;
    }
#endif
#if TIMER_ENABLE_3
    start_result = xTimerStart(s_timer_handle_3, 0U);
    start_failed = start_result != pdPASS;
    if(start_failed)
    {
        return pdFAIL;
    }
#endif
    return pdPASS;
}

#if TASK_ENABLE_0
static void task_0(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_0);
    system_manager_wait_running();

    for(;;)
    {
        (void)xEventGroupWaitBits(s_event_group_handle_0,
                                  EVENT_TIMER_BIT_0,
                                  pdTRUE,
                                  pdTRUE,
                                  portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_1
static void task_1(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_1);
    system_manager_wait_running();

    for(;;)
    {
        (void)xEventGroupWaitBits(s_event_group_handle_1,
                                  EVENT_TIMER_BIT_1,
                                  pdTRUE,
                                  pdTRUE,
                                  portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_2
static void task_2(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_2);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_3
static void task_3(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_3);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_4
static void task_4(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_4);
    system_manager_wait_running();

    led_run();
}
#endif

#if TASK_ENABLE_5
static void task_5(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_5);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_6
static void task_6(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_6);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_7
static void task_7(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_7);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_8
static void task_8(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_8);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_9
static void task_9(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_9);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_10
static void task_10(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_10);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_11
static void task_11(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_11);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_12
static void task_12(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_12);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_13
static void task_13(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_13);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_14
static void task_14(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_14);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TASK_ENABLE_15
static void task_15(void *argument)
{
    (void)argument;

    /** Complete local initialization before reporting this slot ready. */
    system_manager_report_ready(TASK_READY_BIT_15);
    system_manager_wait_running();

    /** Reserved business slot: block without polling until future work is assigned.
     * Notifications carry no payload here; define a protocol when implementing this task.
     */
    for(;;)
    {
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
}
#endif

#if TIMER_ENABLE_0
static void timer_callback_0(TimerHandle_t timer)
{
    (void)timer;
    (void)xEventGroupSetBits(s_event_group_handle_0, EVENT_TIMER_BIT_0);
}
#endif

#if TIMER_ENABLE_1
static void timer_callback_1(TimerHandle_t timer)
{
    (void)timer;
    (void)xEventGroupSetBits(s_event_group_handle_1, EVENT_TIMER_BIT_1);
}
#endif

#if TIMER_ENABLE_2
static void timer_callback_2(TimerHandle_t timer)
{
    (void)timer;
    /** Reserved callback. Any future timer work must remain non-blocking. */
}
#endif

#if TIMER_ENABLE_3
static void timer_callback_3(TimerHandle_t timer)
{
    (void)timer;
    /** Reserved callback. Any future timer work must remain non-blocking. */
}
#endif
