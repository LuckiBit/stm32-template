#include "application_boot.h"
#include "led.h"
#include "my_printf.h"
#include "stm32f1xx_hal.h"
#include "system_init.h"
#include "version.h"

#include <stdint.h>

#ifndef SYSTEM_INFO_MCU_NAME
#error "SYSTEM_INFO_MCU_NAME must be defined by the build system"
#endif
#ifndef SYSTEM_INFO_FIRMWARE_NAME
#error "SYSTEM_INFO_FIRMWARE_NAME must be defined by the build system"
#endif
#ifndef SYSTEM_INFO_BUILD_TYPE
#error "SYSTEM_INFO_BUILD_TYPE must be defined by the build system"
#endif

extern uint8_t __flash_region_start__;
extern uint8_t __flash_region_used_end__;
extern uint8_t __flash_region_end__;
extern uint8_t __ram_region_start__;
extern uint8_t __ram_region_used_end__;
extern uint8_t __ram_region_end__;

typedef struct
{
    uint32_t used_bytes;
    uint32_t total_bytes;
    uint32_t percent_integer;
    uint32_t percent_fraction;
} system_memory_usage_t;

static void system_info_print(void);
static system_memory_usage_t
system_memory_usage_get(uintptr_t region_start, uintptr_t used_end, uintptr_t region_end);

int main(void)
{
    bool application_valid  = false;
    bool printf_initialized = false;

    system_init();
    printf_initialized = my_printf_init();
    if(!printf_initialized)
    {
        Error_Handler();
    }
    system_info_print();
    led_run();
    application_valid = application_is_valid();
    if(application_valid)
    {
        led_stop();
        application_start();
    }

    while(1)
    {
        led_run();
    }
}

static void system_info_print(void)
{
    system_memory_usage_t flash_usage =
        system_memory_usage_get((uintptr_t)&__flash_region_start__,
                                (uintptr_t)&__flash_region_used_end__,
                                (uintptr_t)&__flash_region_end__);
    system_memory_usage_t ram_usage = system_memory_usage_get((uintptr_t)&__ram_region_start__,
                                                              (uintptr_t)&__ram_region_used_end__,
                                                              (uintptr_t)&__ram_region_end__);

    (void)my_printf("================================\r\n");
    (void)my_printf("MCU: %s\r\n", SYSTEM_INFO_MCU_NAME);
    (void)my_printf("Firmware: %s\r\n", SYSTEM_INFO_FIRMWARE_NAME);
    (void)my_printf("Version: %s\r\n", VERSION_STRING);
    (void)my_printf("System clock: %lu MHz\r\n", (unsigned long)(SystemCoreClock / 1000000UL));
    (void)my_printf("Flash: %lu / %lu bytes (%lu.%02lu%%)\r\n",
                    (unsigned long)flash_usage.used_bytes,
                    (unsigned long)flash_usage.total_bytes,
                    (unsigned long)flash_usage.percent_integer,
                    (unsigned long)flash_usage.percent_fraction);
    (void)my_printf("RAM: %lu / %lu bytes (%lu.%02lu%%)\r\n",
                    (unsigned long)ram_usage.used_bytes,
                    (unsigned long)ram_usage.total_bytes,
                    (unsigned long)ram_usage.percent_integer,
                    (unsigned long)ram_usage.percent_fraction);
    (void)my_printf("Build: %s\r\n", SYSTEM_INFO_BUILD_TYPE);
    (void)my_printf("================================\r\n");
}

static system_memory_usage_t
system_memory_usage_get(uintptr_t region_start, uintptr_t used_end, uintptr_t region_end)
{
    system_memory_usage_t usage             = {0};
    uint32_t              scaled_percent    = 0U;
    uint32_t              percent_remainder = 0U;

    usage.used_bytes      = (uint32_t)(used_end - region_start);
    usage.total_bytes     = (uint32_t)(region_end - region_start);
    scaled_percent        = usage.used_bytes * 100U;
    usage.percent_integer = scaled_percent / usage.total_bytes;
    percent_remainder     = scaled_percent % usage.total_bytes;
    usage.percent_fraction =
        (percent_remainder * 100U + (usage.total_bytes / 2U)) / usage.total_bytes;

    if(usage.percent_fraction == 100U)
    {
        ++usage.percent_integer;
        usage.percent_fraction = 0U;
    }

    return usage;
}
