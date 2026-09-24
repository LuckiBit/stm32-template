/**
 * @file my_printf.c
 * @brief Implements bare-metal formatted UART output.
 */

#include "my_printf.h"

#include "bsp_uart.h"
#include "my_printf_config.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define MY_PRINTF_ERROR (-1)

#define MY_PRINTF_UART_ENABLED_COUNT                                                               \
    (MY_PRINTF_UART_1_ENABLE + MY_PRINTF_UART_2_ENABLE + MY_PRINTF_UART_3_ENABLE +                 \
     MY_PRINTF_UART_4_ENABLE + MY_PRINTF_UART_5_ENABLE)

#if MY_PRINTF_UART_ENABLED_COUNT == 0
#error "At least one MY_PRINTF_UART_n_ENABLE switch must be enabled"
#endif
#if MY_PRINTF_UART_1_ENABLE && !BSP_UART_1_ENABLE
#error "MY_PRINTF UART 1 output requires BSP_UART_1_ENABLE"
#endif
#if MY_PRINTF_UART_2_ENABLE && !BSP_UART_2_ENABLE
#error "MY_PRINTF UART 2 output requires BSP_UART_2_ENABLE"
#endif
#if MY_PRINTF_UART_3_ENABLE && !BSP_UART_3_ENABLE
#error "MY_PRINTF UART 3 output requires BSP_UART_3_ENABLE"
#endif
#if MY_PRINTF_UART_4_ENABLE && !BSP_UART_4_ENABLE
#error "MY_PRINTF UART 4 output requires BSP_UART_4_ENABLE"
#endif
#if MY_PRINTF_UART_5_ENABLE && !BSP_UART_5_ENABLE
#error "MY_PRINTF UART 5 output requires BSP_UART_5_ENABLE"
#endif

_Static_assert(MY_PRINTF_BUFFER_SIZE > 1U, "MY_PRINTF_BUFFER_SIZE must hold data and a terminator");
_Static_assert(MY_PRINTF_BUFFER_SIZE <= UINT16_MAX,
               "MY_PRINTF_BUFFER_SIZE exceeds the BSP UART length type");
_Static_assert(MY_PRINTF_TIMEOUT_MS < UINT32_MAX, "MY_PRINTF_TIMEOUT_MS must be finite");

static bool s_initialized = false;

static bool my_printf_transmit(const uint8_t *data, uint16_t length);

bool my_printf_init(void)
{
    bool was_initialized = s_initialized;

    s_initialized = true;
    return !was_initialized;
}

static bool my_printf_transmit(const uint8_t *data, uint16_t length)
{
    bool all_transmitted = true;

#if MY_PRINTF_UART_1_ENABLE
    {
        bool current_transmitted = bsp_uart_transmit(1U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#if MY_PRINTF_UART_2_ENABLE
    {
        bool current_transmitted = bsp_uart_transmit(2U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#if MY_PRINTF_UART_3_ENABLE
    {
        bool current_transmitted = bsp_uart_transmit(3U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#if MY_PRINTF_UART_4_ENABLE
    {
        bool current_transmitted = bsp_uart_transmit(4U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#if MY_PRINTF_UART_5_ENABLE
    {
        bool current_transmitted = bsp_uart_transmit(5U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif

    return all_transmitted;
}

int my_printf_(const char *format, ...)
{
    char    buffer[MY_PRINTF_BUFFER_SIZE];
    va_list arguments;
    int     formatted_length  = MY_PRINTF_ERROR;
    int     result            = MY_PRINTF_ERROR;
    size_t  transmit_length   = 0U;
    bool    input_valid       = s_initialized && format != NULL;
    bool    formatting_failed = false;
    bool    buffer_overflow   = false;
    bool    output_invalid    = false;
    bool    transmitted       = false;

    if(!input_valid)
    {
        return MY_PRINTF_ERROR;
    }

    va_start(arguments, format);
    formatted_length = npf_vsnprintf(buffer, sizeof(buffer), format, arguments);
    va_end(arguments);

    formatting_failed = formatted_length < 0;
    if(!formatting_failed)
    {
        transmit_length = (size_t)formatted_length;
        buffer_overflow = transmit_length >= sizeof(buffer);
    }
    output_invalid = formatting_failed || buffer_overflow;
    if(output_invalid)
    {
        return MY_PRINTF_ERROR;
    }

    transmitted = my_printf_transmit((const uint8_t *)buffer, (uint16_t)transmit_length);
    if(transmitted)
    {
        result = formatted_length;
    }
    return result;
}
