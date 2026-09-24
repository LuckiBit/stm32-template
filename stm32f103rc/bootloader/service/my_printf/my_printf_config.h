/**
 * @file my_printf_config.h
 * @brief Configures the bootloader formatted UART output service.
 */

#ifndef MY_PRINTF_CONFIG_H
#define MY_PRINTF_CONFIG_H

/* UART output switches: 1 = enabled, 0 = disabled. */
#ifndef MY_PRINTF_UART_1_ENABLE
#define MY_PRINTF_UART_1_ENABLE 1
#endif
#ifndef MY_PRINTF_UART_2_ENABLE
#define MY_PRINTF_UART_2_ENABLE 0
#endif
#ifndef MY_PRINTF_UART_3_ENABLE
#define MY_PRINTF_UART_3_ENABLE 0
#endif
#ifndef MY_PRINTF_UART_4_ENABLE
#define MY_PRINTF_UART_4_ENABLE 0
#endif
#ifndef MY_PRINTF_UART_5_ENABLE
#define MY_PRINTF_UART_5_ENABLE 0
#endif

#if(MY_PRINTF_UART_1_ENABLE != 0) && (MY_PRINTF_UART_1_ENABLE != 1)
#error "MY_PRINTF_UART_1_ENABLE must be 0 or 1"
#endif
#if(MY_PRINTF_UART_2_ENABLE != 0) && (MY_PRINTF_UART_2_ENABLE != 1)
#error "MY_PRINTF_UART_2_ENABLE must be 0 or 1"
#endif
#if(MY_PRINTF_UART_3_ENABLE != 0) && (MY_PRINTF_UART_3_ENABLE != 1)
#error "MY_PRINTF_UART_3_ENABLE must be 0 or 1"
#endif
#if(MY_PRINTF_UART_4_ENABLE != 0) && (MY_PRINTF_UART_4_ENABLE != 1)
#error "MY_PRINTF_UART_4_ENABLE must be 0 or 1"
#endif
#if(MY_PRINTF_UART_5_ENABLE != 0) && (MY_PRINTF_UART_5_ENABLE != 1)
#error "MY_PRINTF_UART_5_ENABLE must be 0 or 1"
#endif

#ifndef MY_PRINTF_BUFFER_SIZE
#define MY_PRINTF_BUFFER_SIZE 128U
#endif
#ifndef MY_PRINTF_TIMEOUT_MS
#define MY_PRINTF_TIMEOUT_MS 100U
#endif

#endif /* MY_PRINTF_CONFIG_H */
