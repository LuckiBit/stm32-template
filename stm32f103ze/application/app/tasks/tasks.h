/**
 * @file tasks.h
 * @brief Configures numbered tasks/resources and declares their lifecycle interfaces.
 */

#ifndef TASKS_H
#define TASKS_H

#include <stdbool.h>

/** This header remains independent of FreeRTOS headers so FreeRTOSConfig.h can
 * read its timer switches without a circular include. Interfaces use C bool.
 */

/** Task switches: 1 enables creation; 0 excludes the task and its static RTOS storage. */
#ifndef TASK_0_ENABLE
#define TASK_0_ENABLE 0
#endif
#ifndef TASK_1_ENABLE
#define TASK_1_ENABLE 0
#endif
#ifndef TASK_2_ENABLE
#define TASK_2_ENABLE 0
#endif
#ifndef TASK_3_ENABLE
#define TASK_3_ENABLE 0
#endif
#ifndef TASK_4_ENABLE
#define TASK_4_ENABLE 1
#endif
#ifndef TASK_5_ENABLE
#define TASK_5_ENABLE 0
#endif
#ifndef TASK_6_ENABLE
#define TASK_6_ENABLE 0
#endif
#ifndef TASK_7_ENABLE
#define TASK_7_ENABLE 0
#endif
#ifndef TASK_8_ENABLE
#define TASK_8_ENABLE 0
#endif
#ifndef TASK_9_ENABLE
#define TASK_9_ENABLE 0
#endif
#ifndef TASK_10_ENABLE
#define TASK_10_ENABLE 0
#endif
#ifndef TASK_11_ENABLE
#define TASK_11_ENABLE 0
#endif
#ifndef TASK_12_ENABLE
#define TASK_12_ENABLE 0
#endif
#ifndef TASK_13_ENABLE
#define TASK_13_ENABLE 0
#endif
#ifndef TASK_14_ENABLE
#define TASK_14_ENABLE 0
#endif
#ifndef TASK_15_ENABLE
#define TASK_15_ENABLE 0
#endif

/** Resource switches: 1 enables creation; 0 excludes the resource and its static storage. */
#ifndef QUEUE_0_ENABLE
#define QUEUE_0_ENABLE 0
#endif
#ifndef QUEUE_1_ENABLE
#define QUEUE_1_ENABLE 0
#endif
#ifndef QUEUE_2_ENABLE
#define QUEUE_2_ENABLE 0
#endif
#ifndef QUEUE_3_ENABLE
#define QUEUE_3_ENABLE 0
#endif
#ifndef QUEUE_4_ENABLE
#define QUEUE_4_ENABLE 0
#endif
#ifndef QUEUE_5_ENABLE
#define QUEUE_5_ENABLE 0
#endif
#ifndef QUEUE_6_ENABLE
#define QUEUE_6_ENABLE 0
#endif
#ifndef QUEUE_7_ENABLE
#define QUEUE_7_ENABLE 0
#endif
#ifndef SEMAPHORE_0_ENABLE
#define SEMAPHORE_0_ENABLE 0
#endif
#ifndef SEMAPHORE_1_ENABLE
#define SEMAPHORE_1_ENABLE 0
#endif
#ifndef SEMAPHORE_2_ENABLE
#define SEMAPHORE_2_ENABLE 0
#endif
#ifndef SEMAPHORE_3_ENABLE
#define SEMAPHORE_3_ENABLE 0
#endif
#ifndef SEMAPHORE_4_ENABLE
#define SEMAPHORE_4_ENABLE 0
#endif
#ifndef SEMAPHORE_5_ENABLE
#define SEMAPHORE_5_ENABLE 0
#endif
#ifndef SEMAPHORE_6_ENABLE
#define SEMAPHORE_6_ENABLE 0
#endif
#ifndef SEMAPHORE_7_ENABLE
#define SEMAPHORE_7_ENABLE 0
#endif
#ifndef MUTEX_0_ENABLE
#define MUTEX_0_ENABLE 0
#endif
#ifndef MUTEX_1_ENABLE
#define MUTEX_1_ENABLE 0
#endif
#ifndef MUTEX_2_ENABLE
#define MUTEX_2_ENABLE 0
#endif
#ifndef MUTEX_3_ENABLE
#define MUTEX_3_ENABLE 0
#endif
#ifndef MUTEX_4_ENABLE
#define MUTEX_4_ENABLE 0
#endif
#ifndef MUTEX_5_ENABLE
#define MUTEX_5_ENABLE 0
#endif
#ifndef MUTEX_6_ENABLE
#define MUTEX_6_ENABLE 0
#endif
#ifndef MUTEX_7_ENABLE
#define MUTEX_7_ENABLE 0
#endif

/** Timer and event-group switches may follow the enable state of their dependencies. */
#ifndef TIMER_0_ENABLE
#define TIMER_0_ENABLE TASK_0_ENABLE
#endif
#ifndef TIMER_1_ENABLE
#define TIMER_1_ENABLE TASK_1_ENABLE
#endif
#ifndef TIMER_2_ENABLE
#define TIMER_2_ENABLE 0
#endif
#ifndef TIMER_3_ENABLE
#define TIMER_3_ENABLE 0
#endif
#ifndef EVENT_GROUP_0_ENABLE
#define EVENT_GROUP_0_ENABLE (TASK_0_ENABLE || TIMER_0_ENABLE)
#endif
#ifndef EVENT_GROUP_1_ENABLE
#define EVENT_GROUP_1_ENABLE (TASK_1_ENABLE || TIMER_1_ENABLE)
#endif
#ifndef EVENT_GROUP_2_ENABLE
#define EVENT_GROUP_2_ENABLE 0
#endif
#ifndef EVENT_GROUP_3_ENABLE
#define EVENT_GROUP_3_ENABLE 0
#endif

#define TASK_ENABLED_COUNT                                                                         \
    (TASK_0_ENABLE + TASK_1_ENABLE + TASK_2_ENABLE + TASK_3_ENABLE + TASK_4_ENABLE +               \
     TASK_5_ENABLE + TASK_6_ENABLE + TASK_7_ENABLE + TASK_8_ENABLE + TASK_9_ENABLE +               \
     TASK_10_ENABLE + TASK_11_ENABLE + TASK_12_ENABLE + TASK_13_ENABLE + TASK_14_ENABLE +          \
     TASK_15_ENABLE)
#define TASK_SOFTWARE_TIMERS_ENABLED                                                               \
    (TIMER_0_ENABLE || TIMER_1_ENABLE || TIMER_2_ENABLE || TIMER_3_ENABLE)

#if(TASK_0_ENABLE != 0) && (TASK_0_ENABLE != 1)
#error "TASK_0_ENABLE must be 0 or 1"
#endif
#if(TASK_1_ENABLE != 0) && (TASK_1_ENABLE != 1)
#error "TASK_1_ENABLE must be 0 or 1"
#endif
#if(TASK_2_ENABLE != 0) && (TASK_2_ENABLE != 1)
#error "TASK_2_ENABLE must be 0 or 1"
#endif
#if(TASK_3_ENABLE != 0) && (TASK_3_ENABLE != 1)
#error "TASK_3_ENABLE must be 0 or 1"
#endif
#if(TASK_4_ENABLE != 0) && (TASK_4_ENABLE != 1)
#error "TASK_4_ENABLE must be 0 or 1"
#endif
#if(TASK_5_ENABLE != 0) && (TASK_5_ENABLE != 1)
#error "TASK_5_ENABLE must be 0 or 1"
#endif
#if(TASK_6_ENABLE != 0) && (TASK_6_ENABLE != 1)
#error "TASK_6_ENABLE must be 0 or 1"
#endif
#if(TASK_7_ENABLE != 0) && (TASK_7_ENABLE != 1)
#error "TASK_7_ENABLE must be 0 or 1"
#endif
#if(TASK_8_ENABLE != 0) && (TASK_8_ENABLE != 1)
#error "TASK_8_ENABLE must be 0 or 1"
#endif
#if(TASK_9_ENABLE != 0) && (TASK_9_ENABLE != 1)
#error "TASK_9_ENABLE must be 0 or 1"
#endif
#if(TASK_10_ENABLE != 0) && (TASK_10_ENABLE != 1)
#error "TASK_10_ENABLE must be 0 or 1"
#endif
#if(TASK_11_ENABLE != 0) && (TASK_11_ENABLE != 1)
#error "TASK_11_ENABLE must be 0 or 1"
#endif
#if(TASK_12_ENABLE != 0) && (TASK_12_ENABLE != 1)
#error "TASK_12_ENABLE must be 0 or 1"
#endif
#if(TASK_13_ENABLE != 0) && (TASK_13_ENABLE != 1)
#error "TASK_13_ENABLE must be 0 or 1"
#endif
#if(TASK_14_ENABLE != 0) && (TASK_14_ENABLE != 1)
#error "TASK_14_ENABLE must be 0 or 1"
#endif
#if(TASK_15_ENABLE != 0) && (TASK_15_ENABLE != 1)
#error "TASK_15_ENABLE must be 0 or 1"
#endif
#if(QUEUE_0_ENABLE != 0) && (QUEUE_0_ENABLE != 1)
#error "QUEUE_0_ENABLE must be 0 or 1"
#endif
#if(QUEUE_1_ENABLE != 0) && (QUEUE_1_ENABLE != 1)
#error "QUEUE_1_ENABLE must be 0 or 1"
#endif
#if(QUEUE_2_ENABLE != 0) && (QUEUE_2_ENABLE != 1)
#error "QUEUE_2_ENABLE must be 0 or 1"
#endif
#if(QUEUE_3_ENABLE != 0) && (QUEUE_3_ENABLE != 1)
#error "QUEUE_3_ENABLE must be 0 or 1"
#endif
#if(QUEUE_4_ENABLE != 0) && (QUEUE_4_ENABLE != 1)
#error "QUEUE_4_ENABLE must be 0 or 1"
#endif
#if(QUEUE_5_ENABLE != 0) && (QUEUE_5_ENABLE != 1)
#error "QUEUE_5_ENABLE must be 0 or 1"
#endif
#if(QUEUE_6_ENABLE != 0) && (QUEUE_6_ENABLE != 1)
#error "QUEUE_6_ENABLE must be 0 or 1"
#endif
#if(QUEUE_7_ENABLE != 0) && (QUEUE_7_ENABLE != 1)
#error "QUEUE_7_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_0_ENABLE != 0) && (SEMAPHORE_0_ENABLE != 1)
#error "SEMAPHORE_0_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_1_ENABLE != 0) && (SEMAPHORE_1_ENABLE != 1)
#error "SEMAPHORE_1_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_2_ENABLE != 0) && (SEMAPHORE_2_ENABLE != 1)
#error "SEMAPHORE_2_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_3_ENABLE != 0) && (SEMAPHORE_3_ENABLE != 1)
#error "SEMAPHORE_3_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_4_ENABLE != 0) && (SEMAPHORE_4_ENABLE != 1)
#error "SEMAPHORE_4_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_5_ENABLE != 0) && (SEMAPHORE_5_ENABLE != 1)
#error "SEMAPHORE_5_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_6_ENABLE != 0) && (SEMAPHORE_6_ENABLE != 1)
#error "SEMAPHORE_6_ENABLE must be 0 or 1"
#endif
#if(SEMAPHORE_7_ENABLE != 0) && (SEMAPHORE_7_ENABLE != 1)
#error "SEMAPHORE_7_ENABLE must be 0 or 1"
#endif
#if(MUTEX_0_ENABLE != 0) && (MUTEX_0_ENABLE != 1)
#error "MUTEX_0_ENABLE must be 0 or 1"
#endif
#if(MUTEX_1_ENABLE != 0) && (MUTEX_1_ENABLE != 1)
#error "MUTEX_1_ENABLE must be 0 or 1"
#endif
#if(MUTEX_2_ENABLE != 0) && (MUTEX_2_ENABLE != 1)
#error "MUTEX_2_ENABLE must be 0 or 1"
#endif
#if(MUTEX_3_ENABLE != 0) && (MUTEX_3_ENABLE != 1)
#error "MUTEX_3_ENABLE must be 0 or 1"
#endif
#if(MUTEX_4_ENABLE != 0) && (MUTEX_4_ENABLE != 1)
#error "MUTEX_4_ENABLE must be 0 or 1"
#endif
#if(MUTEX_5_ENABLE != 0) && (MUTEX_5_ENABLE != 1)
#error "MUTEX_5_ENABLE must be 0 or 1"
#endif
#if(MUTEX_6_ENABLE != 0) && (MUTEX_6_ENABLE != 1)
#error "MUTEX_6_ENABLE must be 0 or 1"
#endif
#if(MUTEX_7_ENABLE != 0) && (MUTEX_7_ENABLE != 1)
#error "MUTEX_7_ENABLE must be 0 or 1"
#endif
#if(TIMER_0_ENABLE != 0) && (TIMER_0_ENABLE != 1)
#error "TIMER_0_ENABLE must be 0 or 1"
#endif
#if(TIMER_1_ENABLE != 0) && (TIMER_1_ENABLE != 1)
#error "TIMER_1_ENABLE must be 0 or 1"
#endif
#if(TIMER_2_ENABLE != 0) && (TIMER_2_ENABLE != 1)
#error "TIMER_2_ENABLE must be 0 or 1"
#endif
#if(TIMER_3_ENABLE != 0) && (TIMER_3_ENABLE != 1)
#error "TIMER_3_ENABLE must be 0 or 1"
#endif
#if(EVENT_GROUP_0_ENABLE != 0) && (EVENT_GROUP_0_ENABLE != 1)
#error "EVENT_GROUP_0_ENABLE must be 0 or 1"
#endif
#if(EVENT_GROUP_1_ENABLE != 0) && (EVENT_GROUP_1_ENABLE != 1)
#error "EVENT_GROUP_1_ENABLE must be 0 or 1"
#endif
#if(EVENT_GROUP_2_ENABLE != 0) && (EVENT_GROUP_2_ENABLE != 1)
#error "EVENT_GROUP_2_ENABLE must be 0 or 1"
#endif
#if(EVENT_GROUP_3_ENABLE != 0) && (EVENT_GROUP_3_ENABLE != 1)
#error "EVENT_GROUP_3_ENABLE must be 0 or 1"
#endif

#if TASK_0_ENABLE && !TIMER_0_ENABLE
#error "Task 0 requires timer 0 in the current event example"
#endif
#if(TASK_0_ENABLE || TIMER_0_ENABLE) && !EVENT_GROUP_0_ENABLE
#error "Task/timer 0 requires event group 0"
#endif

#if TASK_1_ENABLE && !TIMER_1_ENABLE
#error "Task 1 requires timer 1 in the current event example"
#endif
#if(TASK_1_ENABLE || TIMER_1_ENABLE) && !EVENT_GROUP_1_ENABLE
#error "Task/timer 1 requires event group 1"
#endif

#define TASK_0_READY_BIT  (1UL << 0)
#define TASK_1_READY_BIT  (1UL << 1)
#define TASK_2_READY_BIT  (1UL << 2)
#define TASK_3_READY_BIT  (1UL << 3)
#define TASK_4_READY_BIT  (1UL << 4)
#define TASK_5_READY_BIT  (1UL << 5)
#define TASK_6_READY_BIT  (1UL << 6)
#define TASK_7_READY_BIT  (1UL << 7)
#define TASK_8_READY_BIT  (1UL << 8)
#define TASK_9_READY_BIT  (1UL << 9)
#define TASK_10_READY_BIT (1UL << 10)
#define TASK_11_READY_BIT (1UL << 11)
#define TASK_12_READY_BIT (1UL << 12)
#define TASK_13_READY_BIT (1UL << 13)
#define TASK_14_READY_BIT (1UL << 14)
#define TASK_15_READY_BIT (1UL << 15)
#define REQUIRED_TASKS                                                                             \
    ((TASK_0_ENABLE * TASK_0_READY_BIT) | (TASK_1_ENABLE * TASK_1_READY_BIT) |                     \
     (TASK_2_ENABLE * TASK_2_READY_BIT) | (TASK_3_ENABLE * TASK_3_READY_BIT) |                     \
     (TASK_4_ENABLE * TASK_4_READY_BIT) | (TASK_5_ENABLE * TASK_5_READY_BIT) |                     \
     (TASK_6_ENABLE * TASK_6_READY_BIT) | (TASK_7_ENABLE * TASK_7_READY_BIT) |                     \
     (TASK_8_ENABLE * TASK_8_READY_BIT) | (TASK_9_ENABLE * TASK_9_READY_BIT) |                     \
     (TASK_10_ENABLE * TASK_10_READY_BIT) | (TASK_11_ENABLE * TASK_11_READY_BIT) |                 \
     (TASK_12_ENABLE * TASK_12_READY_BIT) | (TASK_13_ENABLE * TASK_13_READY_BIT) |                 \
     (TASK_14_ENABLE * TASK_14_READY_BIT) | (TASK_15_ENABLE * TASK_15_READY_BIT))

/**
 * @brief Creates module-owned static resources and enabled numbered tasks.
 * @pre Call once, after manager creation and before scheduler start; not reentrant.
 * @return true on success, false on failure. Failure requires fail-stop;
 * partially created static objects must not be reused or created again.
 */
bool tasks_create(void);

/**
 * @brief Starts enabled software timers; disabled timers have no storage.
 * @pre Call once from the manager after all enabled tasks report ready.
 * @return true when all enabled timer commands are queued; false requires fail-stop.
 * @note On partial failure previously submitted commands may take effect; no rollback is attempted.
 */
bool tasks_start(void);

#endif /** TASKS_H */
