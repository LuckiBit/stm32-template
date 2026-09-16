#include "system_clock.h"

#include "stm32f4xx_hal.h"

#include <stdbool.h>

static void system_clock_handle_error(void)
{
    __disable_irq();

    while(1)
    {
    }
}

void system_clock_config(void)
{
    bool               config_failed;
    HAL_StatusTypeDef  config_result;
    RCC_OscInitTypeDef oscillator_config = {0};
    RCC_ClkInitTypeDef clock_config      = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    oscillator_config.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscillator_config.HSEState       = RCC_HSE_ON;
    oscillator_config.PLL.PLLState   = RCC_PLL_ON;
    oscillator_config.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    oscillator_config.PLL.PLLM       = 16U;
    oscillator_config.PLL.PLLN       = 192U;
    oscillator_config.PLL.PLLP       = RCC_PLLP_DIV2;
    oscillator_config.PLL.PLLQ       = 4U;
    config_result                    = HAL_RCC_OscConfig(&oscillator_config);
    config_failed                    = config_result != HAL_OK;
    if(config_failed)
    {
        system_clock_handle_error();
    }

    clock_config.ClockType =
        RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    clock_config.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    clock_config.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    clock_config.APB1CLKDivider = RCC_HCLK_DIV4;
    clock_config.APB2CLKDivider = RCC_HCLK_DIV2;
    config_result               = HAL_RCC_ClockConfig(&clock_config, FLASH_LATENCY_4);
    config_failed               = config_result != HAL_OK;
    if(config_failed)
    {
        system_clock_handle_error();
    }
}
