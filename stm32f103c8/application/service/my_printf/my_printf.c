/**
 * @file my_printf.c
 * @brief Implements thread-safe formatted UART output.
 */

#include "my_printf.h"

#include "FreeRTOS.h"
#include "bsp_uart.h"
#include "my_printf_config.h"
#include "semphr.h"
#include "task.h"

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define MY_PRINTF_ERROR (-1)

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

#define MY_PRINTF_UART_ENABLED_COUNT                                                               \
    (MY_PRINTF_UART_1_ENABLE + MY_PRINTF_UART_2_ENABLE + MY_PRINTF_UART_3_ENABLE +                 \
     MY_PRINTF_UART_4_ENABLE + MY_PRINTF_UART_5_ENABLE)

#if MY_PRINTF_UART_ENABLED_COUNT == 0
#error "At least one MY_PRINTF_UART_n_ENABLE switch must be enabled"
#endif
#if defined(MY_PRINTF_UART_1_ENABLED) && !defined(BSP_UART_1_ENABLED)
#error "MY_PRINTF UART 1 output requires BSP_UART_1_ENABLE"
#endif
#if defined(MY_PRINTF_UART_2_ENABLED) && !defined(BSP_UART_2_ENABLED)
#error "MY_PRINTF UART 2 output requires BSP_UART_2_ENABLE"
#endif
#if defined(MY_PRINTF_UART_3_ENABLED) && !defined(BSP_UART_3_ENABLED)
#error "MY_PRINTF UART 3 output requires BSP_UART_3_ENABLE"
#endif
#if defined(MY_PRINTF_UART_4_ENABLED) && !defined(BSP_UART_4_ENABLED)
#error "MY_PRINTF UART 4 output requires BSP_UART_4_ENABLE"
#endif
#if defined(MY_PRINTF_UART_5_ENABLED) && !defined(BSP_UART_5_ENABLED)
#error "MY_PRINTF UART 5 output requires BSP_UART_5_ENABLE"
#endif

_Static_assert(MY_PRINTF_BUFFER_SIZE > 1U, "MY_PRINTF_BUFFER_SIZE must hold data and a terminator");
_Static_assert(MY_PRINTF_BUFFER_SIZE <= UINT16_MAX,
               "MY_PRINTF_BUFFER_SIZE exceeds the BSP UART length type");
_Static_assert(MY_PRINTF_TIMEOUT_MS < UINT32_MAX, "MY_PRINTF_TIMEOUT_MS must be finite");

static StaticSemaphore_t s_my_printf_mutex_buffer;
static SemaphoreHandle_t s_my_printf_mutex = NULL;

static bool my_printf_transmit(const uint8_t *data, uint16_t length);

bool my_printf_init(void)
{
    bool is_uninitialized = s_my_printf_mutex == NULL;
    bool initialized      = false;

    if(!is_uninitialized)
    {
        return false;
    }

    s_my_printf_mutex = xSemaphoreCreateMutexStatic(&s_my_printf_mutex_buffer);
    initialized       = s_my_printf_mutex != NULL;
    return initialized;
}

static bool my_printf_transmit(const uint8_t *data, uint16_t length)
{
    bool all_transmitted = true;

#ifdef MY_PRINTF_UART_1_ENABLED
    {
        bool current_transmitted = bsp_uart_transmit(1U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#ifdef MY_PRINTF_UART_2_ENABLED
    {
        bool current_transmitted = bsp_uart_transmit(2U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#ifdef MY_PRINTF_UART_3_ENABLED
    {
        bool current_transmitted = bsp_uart_transmit(3U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#ifdef MY_PRINTF_UART_4_ENABLED
    {
        bool current_transmitted = bsp_uart_transmit(4U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif
#ifdef MY_PRINTF_UART_5_ENABLED
    {
        bool current_transmitted = bsp_uart_transmit(5U, data, length, MY_PRINTF_TIMEOUT_MS);

        all_transmitted = all_transmitted && current_transmitted;
    }
#endif

    return all_transmitted;
}

int my_printf_(const char *format, ...)
{
    char       buffer[MY_PRINTF_BUFFER_SIZE];
    va_list    arguments;
    int        formatted_length  = MY_PRINTF_ERROR;
    int        result            = MY_PRINTF_ERROR;
    size_t     transmit_length   = 0U;
    TickType_t lock_timeout      = 0U;
    BaseType_t lock_result       = pdFALSE;
    BaseType_t release_result    = pdFALSE;
    bool       is_initialized    = s_my_printf_mutex != NULL;
    bool       scheduler_running = xTaskGetSchedulerState() == taskSCHEDULER_RUNNING;
    bool       input_valid       = format != NULL;
    bool       can_format        = is_initialized && scheduler_running && input_valid;
    bool       formatting_failed = false;
    bool       buffer_overflow   = false;
    bool       output_invalid    = false;
    bool       transmitted       = false;
    bool       released          = false;
    bool       succeeded         = false;

    if(!can_format)
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

    lock_timeout = pdMS_TO_TICKS(MY_PRINTF_TIMEOUT_MS);
    lock_result  = xSemaphoreTake(s_my_printf_mutex, lock_timeout);
    if(lock_result != pdTRUE)
    {
        return MY_PRINTF_ERROR;
    }

    transmitted    = my_printf_transmit((const uint8_t *)buffer, (uint16_t)transmit_length);
    release_result = xSemaphoreGive(s_my_printf_mutex);
    released       = release_result == pdTRUE;
    succeeded      = transmitted && released;
    if(succeeded)
    {
        result = formatted_length;
    }
    return result;
}
