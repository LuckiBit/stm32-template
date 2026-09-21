/**
 * @file my_printf.h
 * @brief Declares thread-safe formatted UART output.
 */

#ifndef MY_PRINTF_H
#define MY_PRINTF_H

#include "npf_config.h"

#include <stdbool.h>

/**
 * @brief Creates the service-owned static mutex.
 * @pre The selected UART has been initialized; call once before scheduler start.
 * @return true on success; false if already initialized or creation fails.
 */
bool my_printf_init(void);

/**
 * @brief Formats and sends one complete message through all configured UARTs.
 * @param ... A printf-style format string followed by its arguments.
 * @return Number of transmitted characters; -1 on invalid input, buffer overflow,
 * lock timeout or UART failure.
 * @pre my_printf_init succeeded and the scheduler is running.
 * @note Call only from task context. The function rejects truncated output.
 */
#define my_printf(...) (my_printf_(NPF_MAP_ARGS(__VA_ARGS__)))

int my_printf_(const char *format, ...);

#endif /* MY_PRINTF_H */
