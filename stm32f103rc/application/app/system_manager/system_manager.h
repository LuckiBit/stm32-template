/**
 * @file system_manager.h
 * @brief Declares the fixed-resource startup coordinator and fault reporting API.
 */

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "FreeRTOS.h"
#include "event_groups.h"

#include <stdbool.h>

#define SYSTEM_STARTUP_TIMEOUT_MS 5000U
#define SYSTEM_READY_BITS_MASK    ((EventBits_t)0xffffU)

typedef bool (*system_start_callback_t)(void);

typedef enum
{
    SYSTEM_STATE_BOOT = 0,
    SYSTEM_STATE_INITIALIZING,
    SYSTEM_STATE_RUNNING,
    SYSTEM_STATE_FAULT
} system_state_t;

/**
 * @brief Creates manager-owned static storage, a startup gate and a resident task.
 * @param start_callback Non-null, bounded task-context startup function. Return true
 * only when services are ready to release business tasks; false causes fail-stop.
 * @param required_tasks Enabled participant mask within SYSTEM_READY_BITS_MASK; zero skips the
 * ready wait.
 * @pre Call once before scheduling. Not reentrant; partial failure requires fail-stop.
 * @return pdPASS on success, pdFAIL for invalid parameters or resource creation failure.
 * @note The callback remains valid for the firmware lifetime; no ownership is transferred.
 */
BaseType_t system_manager_create(system_start_callback_t start_callback,
                                 EventBits_t             required_tasks);

/**
 * @brief Marks a participant ready and wakes the manager; safe across tasks after creation.
 * @param task_bit Exactly one bit from the required mask, owned by the reporting task.
 * @pre Local initialization succeeded. Task context only; invalid bits cause an assertion.
 */
void system_manager_report_ready(EventBits_t task_bit);

/**
 * @brief Blocks the caller until all startup requirements pass; task context only.
 * @pre Manager creation succeeded. Concurrent calls are supported; no bits are consumed.
 * @note One-shot barrier, not a runtime pause/resume API. On startup failure no task passes.
 */
void system_manager_wait_running(void);

/**
 * @brief Latches a fault and wakes the manager; current policy is fail-stop.
 * @pre Manager creation succeeded. Task context only; concurrent calls are supported.
 * @note For urgent hardware hazards, make outputs safe locally before reporting.
 */
void system_manager_report_fault(void);

/**
 * @brief Returns a diagnostic state snapshot, without modifying manager-owned resources.
 * @note Task context only; safe before creation. The snapshot is not a synchronization gate.
 */
system_state_t system_manager_get_state(void);

#endif /** SYSTEM_MANAGER_H */
