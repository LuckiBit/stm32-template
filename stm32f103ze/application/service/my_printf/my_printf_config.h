/**
 * @file my_printf_config.h
 * @brief Configures the formatted UART output service.
 */

#ifndef MY_PRINTF_CONFIG_H
#define MY_PRINTF_CONFIG_H

/* UART output switches: 1 = enabled, 0 = disabled. */
#define MY_PRINTF_UART_1_ENABLE 1
#define MY_PRINTF_UART_2_ENABLE 0
#define MY_PRINTF_UART_3_ENABLE 0
#define MY_PRINTF_UART_4_ENABLE 0
#define MY_PRINTF_UART_5_ENABLE 0

/* Map UART output switches to presence macros used by the service. */
#if MY_PRINTF_UART_1_ENABLE
#define MY_PRINTF_UART_1_ENABLED
#endif

#if MY_PRINTF_UART_2_ENABLE
#define MY_PRINTF_UART_2_ENABLED
#endif

#if MY_PRINTF_UART_3_ENABLE
#define MY_PRINTF_UART_3_ENABLED
#endif

#if MY_PRINTF_UART_4_ENABLE
#define MY_PRINTF_UART_4_ENABLED
#endif

#if MY_PRINTF_UART_5_ENABLE
#define MY_PRINTF_UART_5_ENABLED
#endif

#define MY_PRINTF_BUFFER_SIZE 128U
#define MY_PRINTF_TIMEOUT_MS  100U

#endif /* MY_PRINTF_CONFIG_H */
