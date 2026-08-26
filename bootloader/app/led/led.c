/**
 * @file led.c
 * @brief Implements the Bootloader LED workflow.
 */

#include "led.h"

#include "delay_service.h"
#include "led_service.h"

#include <stdbool.h>
#include <stdint.h>

#define LED_BLINK_INTERVAL_MS 100U
#define LED_TOGGLE_COUNT      4U

void led_run(void)
{
    bool     blink_complete = false;
    uint32_t toggle_count   = 0U;

    while(!blink_complete)
    {
        led_service_toggle();
        delay_service_wait_ms(LED_BLINK_INTERVAL_MS);
        toggle_count++;
        blink_complete = toggle_count >= LED_TOGGLE_COUNT;
    }
}

void led_stop(void)
{
    led_service_turn_off();
}
