/**
 * @file rtos_start.h
 * @brief Declares the application scheduler entry point.
 */

#ifndef RTOS_START_H
#define RTOS_START_H

/**
 * @brief Creates module-owned static resources and starts the scheduler.
 * @pre Board initialization has completed; call once from main before scheduling.
 * @note Not reentrant. Failure stops execution; this function never returns.
 */
_Noreturn void rtos_start(void);

#endif /** RTOS_START_H */
