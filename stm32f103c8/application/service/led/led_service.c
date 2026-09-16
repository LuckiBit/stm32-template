/**
 * @file led_service.c
 * @brief Implements generic LED control capabilities.
 */

#include "led_service.h"

#include "bsp_gpio.h"

void led_service_toggle(void)
{
    bsp_gpio_led_toggle();
}
