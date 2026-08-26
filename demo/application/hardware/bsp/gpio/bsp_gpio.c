#include "bsp_gpio.h"

#include "stm32f1xx_hal.h"

#define BSP_GPIO_LED_PIN  GPIO_PIN_10
#define BSP_GPIO_LED_PORT GPIOC

void bsp_gpio_init(void)
{
    GPIO_InitTypeDef gpio_config = {0};

    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    HAL_GPIO_WritePin(BSP_GPIO_LED_PORT, BSP_GPIO_LED_PIN, GPIO_PIN_SET);

    gpio_config.Pin   = BSP_GPIO_LED_PIN;
    gpio_config.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio_config.Pull  = GPIO_NOPULL;
    gpio_config.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(BSP_GPIO_LED_PORT, &gpio_config);
}

void bsp_gpio_led_toggle(void)
{
    HAL_GPIO_TogglePin(BSP_GPIO_LED_PORT, BSP_GPIO_LED_PIN);
}
