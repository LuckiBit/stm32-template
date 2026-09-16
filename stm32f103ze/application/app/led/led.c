/**
 * @file led.c
 * @brief Implements the LED state machine.
 */

#include "led.h"

#include "FreeRTOS.h"
#include "led_service.h"
#include "task.h"

#include <stdbool.h>
#include <stdint.h>

#define LED_FAST_BLINK_PERIOD_MS 300U
#define LED_SLOW_BLINK_PERIOD_MS 500U
#define LED_FAST_BLINK_COUNT     100U

typedef enum
{
    LED_STATE_FAST_BLINK = 0,
    LED_STATE_SLOW_BLINK
} led_state_t;

void led_run(void)
{
    bool        fast_blink_complete;
    uint32_t    blink_count = 0U;
    TickType_t  blink_delay;
    led_state_t led_state = LED_STATE_FAST_BLINK;

    for(;;)
    {
        led_service_toggle();

        switch(led_state)
        {
            case LED_STATE_FAST_BLINK:
                blink_count++;
                blink_delay         = pdMS_TO_TICKS(LED_FAST_BLINK_PERIOD_MS);
                fast_blink_complete = blink_count >= LED_FAST_BLINK_COUNT;
                if(fast_blink_complete)
                {
                    led_state = LED_STATE_SLOW_BLINK;
                }
                break;

            case LED_STATE_SLOW_BLINK:
                blink_delay = pdMS_TO_TICKS(LED_SLOW_BLINK_PERIOD_MS);
                break;

            default:
                led_state   = LED_STATE_FAST_BLINK;
                blink_count = 0U;
                blink_delay = pdMS_TO_TICKS(LED_FAST_BLINK_PERIOD_MS);
                break;
        }

        vTaskDelay(blink_delay);
    }
}
