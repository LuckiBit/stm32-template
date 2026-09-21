/**
 * @file led_service.c
 * @brief Implements generic LED control capabilities.
 */

#include "led_service.h"

#include "bsp_gpio.h"

#define LED_SERVICE_GPIO_PIN BSP_GPIOA_5

void led_service_toggle(void)
{
    (void)bsp_gpio_toggle(LED_SERVICE_GPIO_PIN);
}
