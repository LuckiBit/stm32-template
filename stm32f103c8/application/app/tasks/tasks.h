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
#ifndef TASK_ENABLE_0
#define TASK_ENABLE_0 0
#endif
#ifndef TASK_ENABLE_1
#define TASK_ENABLE_1 0
#endif
#ifndef TASK_ENABLE_2
#define TASK_ENABLE_2 0
#endif
#ifndef TASK_ENABLE_3
#define TASK_ENABLE_3 0
#endif
#ifndef TASK_ENABLE_4
#define TASK_ENABLE_4 1
#endif
#ifndef TASK_ENABLE_5
#define TASK_ENABLE_5 0
#endif
#ifndef TASK_ENABLE_6
#define TASK_ENABLE_6 0
#endif
#ifndef TASK_ENABLE_7
#define TASK_ENABLE_7 0
#endif
#ifndef TASK_ENABLE_8
#define TASK_ENABLE_8 0
#endif
#ifndef TASK_ENABLE_9
#define TASK_ENABLE_9 0
#endif
#ifndef TASK_ENABLE_10
#define TASK_ENABLE_10 0
#endif
#ifndef TASK_ENABLE_11
#define TASK_ENABLE_11 0
#endif
#ifndef TASK_ENABLE_12
#define TASK_ENABLE_12 0
#endif
#ifndef TASK_ENABLE_13
#define TASK_ENABLE_13 0
#endif
#ifndef TASK_ENABLE_14
#define TASK_ENABLE_14 0
#endif
#ifndef TASK_ENABLE_15
#define TASK_ENABLE_15 0
#endif

/** Resource switches: 1 enables creation; 0 excludes the resource and its static storage. */
#ifndef QUEUE_ENABLE_0
#define QUEUE_ENABLE_0 0
#endif
#ifndef QUEUE_ENABLE_1
#define QUEUE_ENABLE_1 0
#endif
#ifndef QUEUE_ENABLE_2
#define QUEUE_ENABLE_2 0
#endif
#ifndef QUEUE_ENABLE_3
#define QUEUE_ENABLE_3 0
#endif
#ifndef QUEUE_ENABLE_4
#define QUEUE_ENABLE_4 0
#endif
#ifndef QUEUE_ENABLE_5
#define QUEUE_ENABLE_5 0
#endif
#ifndef QUEUE_ENABLE_6
#define QUEUE_ENABLE_6 0
#endif
#ifndef QUEUE_ENABLE_7
#define QUEUE_ENABLE_7 0
#endif
#ifndef SEMAPHORE_ENABLE_0
#define SEMAPHORE_ENABLE_0 0
#endif
#ifndef SEMAPHORE_ENABLE_1
#define SEMAPHORE_ENABLE_1 0
#endif
#ifndef SEMAPHORE_ENABLE_2
#define SEMAPHORE_ENABLE_2 0
#endif
#ifndef SEMAPHORE_ENABLE_3
#define SEMAPHORE_ENABLE_3 0
#endif
#ifndef SEMAPHORE_ENABLE_4
#define SEMAPHORE_ENABLE_4 0
#endif
#ifndef SEMAPHORE_ENABLE_5
#define SEMAPHORE_ENABLE_5 0
#endif
#ifndef SEMAPHORE_ENABLE_6
#define SEMAPHORE_ENABLE_6 0
#endif
#ifndef SEMAPHORE_ENABLE_7
#define SEMAPHORE_ENABLE_7 0
#endif
#ifndef MUTEX_ENABLE_0
#define MUTEX_ENABLE_0 0
#endif
#ifndef MUTEX_ENABLE_1
#define MUTEX_ENABLE_1 0
#endif
#ifndef MUTEX_ENABLE_2
#define MUTEX_ENABLE_2 0
#endif
#ifndef MUTEX_ENABLE_3
#define MUTEX_ENABLE_3 0
#endif
#ifndef MUTEX_ENABLE_4
#define MUTEX_ENABLE_4 0
#endif
#ifndef MUTEX_ENABLE_5
#define MUTEX_ENABLE_5 0
#endif
#ifndef MUTEX_ENABLE_6
#define MUTEX_ENABLE_6 0
#endif
#ifndef MUTEX_ENABLE_7
#define MUTEX_ENABLE_7 0
#endif

/** Timer and event-group switches may follow the enable state of their dependencies. */
#ifndef TIMER_ENABLE_0
#define TIMER_ENABLE_0 TASK_ENABLE_0
#endif
#ifndef TIMER_ENABLE_1
#define TIMER_ENABLE_1 TASK_ENABLE_1
#endif
#ifndef TIMER_ENABLE_2
#define TIMER_ENABLE_2 0
#endif
#ifndef TIMER_ENABLE_3
#define TIMER_ENABLE_3 0
#endif
#ifndef EVENT_GROUP_ENABLE_0
#define EVENT_GROUP_ENABLE_0 (TASK_ENABLE_0 || TIMER_ENABLE_0)
#endif
#ifndef EVENT_GROUP_ENABLE_1
#define EVENT_GROUP_ENABLE_1 (TASK_ENABLE_1 || TIMER_ENABLE_1)
#endif
#ifndef EVENT_GROUP_ENABLE_2
#define EVENT_GROUP_ENABLE_2 0
#endif
#ifndef EVENT_GROUP_ENABLE_3
#define EVENT_GROUP_ENABLE_3 0
#endif

#define TASK_ENABLED_COUNT                                                                         \
    (TASK_ENABLE_0 + TASK_ENABLE_1 + TASK_ENABLE_2 + TASK_ENABLE_3 + TASK_ENABLE_4 +               \
     TASK_ENABLE_5 + TASK_ENABLE_6 + TASK_ENABLE_7 + TASK_ENABLE_8 + TASK_ENABLE_9 +               \
     TASK_ENABLE_10 + TASK_ENABLE_11 + TASK_ENABLE_12 + TASK_ENABLE_13 + TASK_ENABLE_14 +          \
     TASK_ENABLE_15)
#define TASK_SOFTWARE_TIMERS_ENABLED                                                               \
    (TIMER_ENABLE_0 || TIMER_ENABLE_1 || TIMER_ENABLE_2 || TIMER_ENABLE_3)

#if(TASK_ENABLE_0 != 0) && (TASK_ENABLE_0 != 1)
#error "TASK_ENABLE_0 must be 0 or 1"
#endif
#if(TASK_ENABLE_1 != 0) && (TASK_ENABLE_1 != 1)
#error "TASK_ENABLE_1 must be 0 or 1"
#endif
#if(TASK_ENABLE_2 != 0) && (TASK_ENABLE_2 != 1)
#error "TASK_ENABLE_2 must be 0 or 1"
#endif
#if(TASK_ENABLE_3 != 0) && (TASK_ENABLE_3 != 1)
#error "TASK_ENABLE_3 must be 0 or 1"
#endif
#if(TASK_ENABLE_4 != 0) && (TASK_ENABLE_4 != 1)
#error "TASK_ENABLE_4 must be 0 or 1"
#endif
#if(TASK_ENABLE_5 != 0) && (TASK_ENABLE_5 != 1)
#error "TASK_ENABLE_5 must be 0 or 1"
#endif
#if(TASK_ENABLE_6 != 0) && (TASK_ENABLE_6 != 1)
#error "TASK_ENABLE_6 must be 0 or 1"
#endif
#if(TASK_ENABLE_7 != 0) && (TASK_ENABLE_7 != 1)
#error "TASK_ENABLE_7 must be 0 or 1"
#endif
#if(TASK_ENABLE_8 != 0) && (TASK_ENABLE_8 != 1)
#error "TASK_ENABLE_8 must be 0 or 1"
#endif
#if(TASK_ENABLE_9 != 0) && (TASK_ENABLE_9 != 1)
#error "TASK_ENABLE_9 must be 0 or 1"
#endif
#if(TASK_ENABLE_10 != 0) && (TASK_ENABLE_10 != 1)
#error "TASK_ENABLE_10 must be 0 or 1"
#endif
#if(TASK_ENABLE_11 != 0) && (TASK_ENABLE_11 != 1)
#error "TASK_ENABLE_11 must be 0 or 1"
#endif
#if(TASK_ENABLE_12 != 0) && (TASK_ENABLE_12 != 1)
#error "TASK_ENABLE_12 must be 0 or 1"
#endif
#if(TASK_ENABLE_13 != 0) && (TASK_ENABLE_13 != 1)
#error "TASK_ENABLE_13 must be 0 or 1"
#endif
#if(TASK_ENABLE_14 != 0) && (TASK_ENABLE_14 != 1)
#error "TASK_ENABLE_14 must be 0 or 1"
#endif
#if(TASK_ENABLE_15 != 0) && (TASK_ENABLE_15 != 1)
#error "TASK_ENABLE_15 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_0 != 0) && (QUEUE_ENABLE_0 != 1)
#error "QUEUE_ENABLE_0 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_1 != 0) && (QUEUE_ENABLE_1 != 1)
#error "QUEUE_ENABLE_1 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_2 != 0) && (QUEUE_ENABLE_2 != 1)
#error "QUEUE_ENABLE_2 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_3 != 0) && (QUEUE_ENABLE_3 != 1)
#error "QUEUE_ENABLE_3 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_4 != 0) && (QUEUE_ENABLE_4 != 1)
#error "QUEUE_ENABLE_4 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_5 != 0) && (QUEUE_ENABLE_5 != 1)
#error "QUEUE_ENABLE_5 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_6 != 0) && (QUEUE_ENABLE_6 != 1)
#error "QUEUE_ENABLE_6 must be 0 or 1"
#endif
#if(QUEUE_ENABLE_7 != 0) && (QUEUE_ENABLE_7 != 1)
#error "QUEUE_ENABLE_7 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_0 != 0) && (SEMAPHORE_ENABLE_0 != 1)
#error "SEMAPHORE_ENABLE_0 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_1 != 0) && (SEMAPHORE_ENABLE_1 != 1)
#error "SEMAPHORE_ENABLE_1 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_2 != 0) && (SEMAPHORE_ENABLE_2 != 1)
#error "SEMAPHORE_ENABLE_2 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_3 != 0) && (SEMAPHORE_ENABLE_3 != 1)
#error "SEMAPHORE_ENABLE_3 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_4 != 0) && (SEMAPHORE_ENABLE_4 != 1)
#error "SEMAPHORE_ENABLE_4 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_5 != 0) && (SEMAPHORE_ENABLE_5 != 1)
#error "SEMAPHORE_ENABLE_5 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_6 != 0) && (SEMAPHORE_ENABLE_6 != 1)
#error "SEMAPHORE_ENABLE_6 must be 0 or 1"
#endif
#if(SEMAPHORE_ENABLE_7 != 0) && (SEMAPHORE_ENABLE_7 != 1)
#error "SEMAPHORE_ENABLE_7 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_0 != 0) && (MUTEX_ENABLE_0 != 1)
#error "MUTEX_ENABLE_0 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_1 != 0) && (MUTEX_ENABLE_1 != 1)
#error "MUTEX_ENABLE_1 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_2 != 0) && (MUTEX_ENABLE_2 != 1)
#error "MUTEX_ENABLE_2 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_3 != 0) && (MUTEX_ENABLE_3 != 1)
#error "MUTEX_ENABLE_3 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_4 != 0) && (MUTEX_ENABLE_4 != 1)
#error "MUTEX_ENABLE_4 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_5 != 0) && (MUTEX_ENABLE_5 != 1)
#error "MUTEX_ENABLE_5 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_6 != 0) && (MUTEX_ENABLE_6 != 1)
#error "MUTEX_ENABLE_6 must be 0 or 1"
#endif
#if(MUTEX_ENABLE_7 != 0) && (MUTEX_ENABLE_7 != 1)
#error "MUTEX_ENABLE_7 must be 0 or 1"
#endif
#if(TIMER_ENABLE_0 != 0) && (TIMER_ENABLE_0 != 1)
#error "TIMER_ENABLE_0 must be 0 or 1"
#endif
#if(TIMER_ENABLE_1 != 0) && (TIMER_ENABLE_1 != 1)
#error "TIMER_ENABLE_1 must be 0 or 1"
#endif
#if(TIMER_ENABLE_2 != 0) && (TIMER_ENABLE_2 != 1)
#error "TIMER_ENABLE_2 must be 0 or 1"
#endif
#if(TIMER_ENABLE_3 != 0) && (TIMER_ENABLE_3 != 1)
#error "TIMER_ENABLE_3 must be 0 or 1"
#endif
#if(EVENT_GROUP_ENABLE_0 != 0) && (EVENT_GROUP_ENABLE_0 != 1)
#error "EVENT_GROUP_ENABLE_0 must be 0 or 1"
#endif
#if(EVENT_GROUP_ENABLE_1 != 0) && (EVENT_GROUP_ENABLE_1 != 1)
#error "EVENT_GROUP_ENABLE_1 must be 0 or 1"
#endif
#if(EVENT_GROUP_ENABLE_2 != 0) && (EVENT_GROUP_ENABLE_2 != 1)
#error "EVENT_GROUP_ENABLE_2 must be 0 or 1"
#endif
#if(EVENT_GROUP_ENABLE_3 != 0) && (EVENT_GROUP_ENABLE_3 != 1)
#error "EVENT_GROUP_ENABLE_3 must be 0 or 1"
#endif

#if TASK_ENABLE_0 && !TIMER_ENABLE_0
#error "Task 0 requires timer 0 in the current event example"
#endif
#if(TASK_ENABLE_0 || TIMER_ENABLE_0) && !EVENT_GROUP_ENABLE_0
#error "Task/timer 0 requires event group 0"
#endif

#if TASK_ENABLE_1 && !TIMER_ENABLE_1
#error "Task 1 requires timer 1 in the current event example"
#endif
#if(TASK_ENABLE_1 || TIMER_ENABLE_1) && !EVENT_GROUP_ENABLE_1
#error "Task/timer 1 requires event group 1"
#endif

#define TASK_READY_BIT_0  (1UL << 0)
#define TASK_READY_BIT_1  (1UL << 1)
#define TASK_READY_BIT_2  (1UL << 2)
#define TASK_READY_BIT_3  (1UL << 3)
#define TASK_READY_BIT_4  (1UL << 4)
#define TASK_READY_BIT_5  (1UL << 5)
#define TASK_READY_BIT_6  (1UL << 6)
#define TASK_READY_BIT_7  (1UL << 7)
#define TASK_READY_BIT_8  (1UL << 8)
#define TASK_READY_BIT_9  (1UL << 9)
#define TASK_READY_BIT_10 (1UL << 10)
#define TASK_READY_BIT_11 (1UL << 11)
#define TASK_READY_BIT_12 (1UL << 12)
#define TASK_READY_BIT_13 (1UL << 13)
#define TASK_READY_BIT_14 (1UL << 14)
#define TASK_READY_BIT_15 (1UL << 15)
#define REQUIRED_TASKS                                                                             \
    ((TASK_ENABLE_0 * TASK_READY_BIT_0) | (TASK_ENABLE_1 * TASK_READY_BIT_1) |                     \
     (TASK_ENABLE_2 * TASK_READY_BIT_2) | (TASK_ENABLE_3 * TASK_READY_BIT_3) |                     \
     (TASK_ENABLE_4 * TASK_READY_BIT_4) | (TASK_ENABLE_5 * TASK_READY_BIT_5) |                     \
     (TASK_ENABLE_6 * TASK_READY_BIT_6) | (TASK_ENABLE_7 * TASK_READY_BIT_7) |                     \
     (TASK_ENABLE_8 * TASK_READY_BIT_8) | (TASK_ENABLE_9 * TASK_READY_BIT_9) |                     \
     (TASK_ENABLE_10 * TASK_READY_BIT_10) | (TASK_ENABLE_11 * TASK_READY_BIT_11) |                 \
     (TASK_ENABLE_12 * TASK_READY_BIT_12) | (TASK_ENABLE_13 * TASK_READY_BIT_13) |                 \
     (TASK_ENABLE_14 * TASK_READY_BIT_14) | (TASK_ENABLE_15 * TASK_READY_BIT_15))

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
