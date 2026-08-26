/**
 * @file rtos_start.h
 * @brief Defines RTOS startup objects and declares the scheduler startup interface.
 */

#ifndef RTOS_START_H
#define RTOS_START_H

#include "FreeRTOS.h"

#include <stdint.h>

/** Stack depth is measured in StackType_t units. */
#define RTOS_TASK_0_NAME        "task_0"
#define RTOS_TASK_0_STACK_DEPTH configMINIMAL_STACK_SIZE
#define RTOS_TASK_0_PRIORITY    (tskIDLE_PRIORITY + 1U)
#define RTOS_TASK_0_PERIOD_MS   1000U

#define RTOS_TASK_1_NAME        "task_1"
#define RTOS_TASK_1_STACK_DEPTH configMINIMAL_STACK_SIZE
#define RTOS_TASK_1_PRIORITY    (tskIDLE_PRIORITY + 2U)
#define RTOS_TASK_1_PERIOD_MS   1000U

#define RTOS_TASK_2_NAME        "task_2"
#define RTOS_TASK_2_STACK_DEPTH configMINIMAL_STACK_SIZE
#define RTOS_TASK_2_PRIORITY    (tskIDLE_PRIORITY + 3U)
#define RTOS_TASK_2_PERIOD_MS   1000U

#define RTOS_TASK_3_NAME        "task_3"
#define RTOS_TASK_3_STACK_DEPTH configMINIMAL_STACK_SIZE
#define RTOS_TASK_3_PRIORITY    (tskIDLE_PRIORITY + 4U)
#define RTOS_TASK_3_PERIOD_MS   1000U

#define RTOS_TASK_4_NAME        "task_4"
#define RTOS_TASK_4_STACK_DEPTH configMINIMAL_STACK_SIZE
#define RTOS_TASK_4_PRIORITY    (tskIDLE_PRIORITY + 5U)

#define RTOS_QUEUE_0_LENGTH    5U
#define RTOS_QUEUE_0_ITEM_TYPE uint32_t
#define RTOS_QUEUE_1_LENGTH    5U
#define RTOS_QUEUE_1_ITEM_TYPE uint32_t
#define RTOS_QUEUE_2_LENGTH    5U
#define RTOS_QUEUE_2_ITEM_TYPE uint32_t
#define RTOS_QUEUE_3_LENGTH    5U
#define RTOS_QUEUE_3_ITEM_TYPE uint32_t
#define RTOS_QUEUE_4_LENGTH    5U
#define RTOS_QUEUE_4_ITEM_TYPE uint32_t

#define RTOS_TIMER_0_NAME      "timer_0"
#define RTOS_TIMER_0_PERIOD_MS 500U
#define RTOS_TIMER_1_NAME      "timer_1"
#define RTOS_TIMER_1_PERIOD_MS 1000U

#define RTOS_EVENT_GROUP_0_TIMER_BIT (1U << 0)
#define RTOS_EVENT_GROUP_1_TIMER_BIT (1U << 0)

void rtos_start(void);

#endif /* RTOS_START_H */
