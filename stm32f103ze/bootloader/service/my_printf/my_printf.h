/**
 * @file my_printf.h
 * @brief Declares bare-metal formatted UART output.
 */

#ifndef MY_PRINTF_H
#define MY_PRINTF_H

#include "npf_config.h"

#include <stdbool.h>

/**
 * @brief Marks the service ready after the selected UART has been initialized.
 * @pre Call once after bsp_uart_init and before using my_printf.
 * @return true on first initialization; false if already initialized.
 */
bool my_printf_init(void);

/**
 * @brief Formats and sends one complete message through all configured UARTs.
 * @param ... A printf-style format string followed by its arguments.
 * @return Number of transmitted characters; -1 on invalid input, buffer overflow or UART failure.
 * @pre my_printf_init succeeded. Serialize callers externally and never call from an ISR.
 * @note The function rejects truncated output.
 */
#define my_printf(...) (my_printf_(NPF_MAP_ARGS(__VA_ARGS__)))

int my_printf_(const char *format, ...);

#endif /* MY_PRINTF_H */
