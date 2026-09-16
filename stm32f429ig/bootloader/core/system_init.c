#include "system_init.h"
#include "bsp_gpio.h"
#include "flash_layout.h"
#include "stm32f4xx_hal.h"
#include "system_clock.h"

_Static_assert(BOOTLOADER_END_ADDRESS == APP_START_ADDRESS,
               "Bootloader and Application regions must be adjacent");
_Static_assert(APP_END_ADDRESS == BOOT_INFO_START_ADDRESS,
               "Application and Boot Info regions must be adjacent");
_Static_assert(BOOT_INFO_START_ADDRESS + BOOT_INFO_SIZE == MCU_FLASH_END_ADDRESS,
               "Flash layout must cover the device Flash exactly");

void system_init(void)
{
    HAL_Init();
    system_clock_config();
    bsp_gpio_init();
}
