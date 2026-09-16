/**
 * @file rtos_fault.h
 * @brief Declares non-returning fault handling and debugger-visible fault codes.
 */

#ifndef RTOS_FAULT_H
#define RTOS_FAULT_H

typedef enum
{
    RTOS_FAULT_NONE = 0,
    RTOS_FAULT_MANAGER_CREATE,
    RTOS_FAULT_APPLICATION_CREATE,
    RTOS_FAULT_SCHEDULER_RETURN,
    RTOS_FAULT_STARTUP_TIMEOUT,
    RTOS_FAULT_SERVICE_START,
    RTOS_FAULT_RUNTIME,
    RTOS_FAULT_STACK_OVERFLOW,
    RTOS_FAULT_ASSERT
} rtos_fault_t;

/** First fault, retained in RAM for the debugger; not persistent over reset. */
extern volatile rtos_fault_t g_rtos_fault;

/**
 * @brief Records the first fault, masks interrupts, places board outputs in their fallback state.
 * @param fault Non-NONE error code describing the failure; no resources are transferred.
 * @note Callable before or after scheduler start; never returns. No heap or blocking APIs.
 * Nested maskable interrupts are excluded before shared state is modified.
 */
_Noreturn void rtos_fault_stop(rtos_fault_t fault);

#endif /** RTOS_FAULT_H */
