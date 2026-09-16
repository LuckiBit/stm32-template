/**
 * @file delay_service.c
 * @brief Implements blocking delay capabilities used by the Bootloader.
 */

#include "delay_service.h"

#include "stm32f1xx_hal.h"

void delay_service_wait_ms(uint32_t duration_ms)
{
    HAL_Delay(duration_ms);
}
