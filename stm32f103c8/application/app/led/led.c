/**
 * @file led.c
 * @brief Implements periodic LED toggling.
 */

#include "led.h"

#include "FreeRTOS.h"
#include "led_service.h"
#include "task.h"

#define LED_BLINK_PERIOD_MS 500U

void led_run(void)
{
    for(;;)
    {
        led_service_toggle();
        vTaskDelay(pdMS_TO_TICKS(LED_BLINK_PERIOD_MS));
    }
}
