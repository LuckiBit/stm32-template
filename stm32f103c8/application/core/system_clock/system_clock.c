#include "system_clock.h"

#include "stm32f1xx_hal.h"

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

    oscillator_config.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    oscillator_config.HSEState       = RCC_HSE_ON;
    oscillator_config.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    oscillator_config.HSIState       = RCC_HSI_ON;
    oscillator_config.PLL.PLLState   = RCC_PLL_ON;
    oscillator_config.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    oscillator_config.PLL.PLLMUL     = RCC_PLL_MUL9;
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
    clock_config.APB1CLKDivider = RCC_HCLK_DIV2;
    clock_config.APB2CLKDivider = RCC_HCLK_DIV1;
    config_result               = HAL_RCC_ClockConfig(&clock_config, FLASH_LATENCY_2);
    config_failed               = config_result != HAL_OK;
    if(config_failed)
    {
        system_clock_handle_error();
    }
}
