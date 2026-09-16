#include "system_init.h"
#include "bsp_gpio.h"
#include "bsp_uart.h"
#include "flash_layout.h"
#include "stm32f1xx_hal.h"
#include "system_clock.h"

#include <stdbool.h>

_Static_assert(BOOTLOADER_END_ADDRESS == APP_START_ADDRESS,
               "Bootloader and Application regions must be adjacent");
_Static_assert(APP_END_ADDRESS == BOOT_INFO_START_ADDRESS,
               "Application and Boot Info regions must be adjacent");
_Static_assert(BOOT_INFO_START_ADDRESS + BOOT_INFO_SIZE == MCU_FLASH_END_ADDRESS,
               "Flash layout must cover the device Flash exactly");

void system_init(void)
{
    bool uart_initialized = false;

    HAL_Init();
    system_clock_config();
    bsp_gpio_init();
    uart_initialized = bsp_uart_init();
    if(!uart_initialized)
    {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    __disable_irq();

    while(1)
    {
    }
}
