/**
 * @file bsp_uart.c
 * @brief Implements configurable board UART interfaces.
 */

#include "bsp_uart.h"
#include "stm32f1xx_hal.h"

#ifdef BSP_UART_1_ENABLED
static UART_HandleTypeDef s_uart_handle_1;
#endif
#ifdef BSP_UART_2_ENABLED
static UART_HandleTypeDef s_uart_handle_2;
#endif
#ifdef BSP_UART_3_ENABLED
static UART_HandleTypeDef s_uart_handle_3;
#endif
#ifdef BSP_UART_4_ENABLED
static UART_HandleTypeDef s_uart_handle_4;
#endif
#ifdef BSP_UART_5_ENABLED
static UART_HandleTypeDef s_uart_handle_5;
#endif

static UART_HandleTypeDef *bsp_uart_get_handle(uint8_t uart_number)
{
    UART_HandleTypeDef *uart_handle = NULL;

    switch(uart_number)
    {
#ifdef BSP_UART_1_ENABLED
        case 1U:
            uart_handle = &s_uart_handle_1;
            break;
#endif
#ifdef BSP_UART_2_ENABLED
        case 2U:
            uart_handle = &s_uart_handle_2;
            break;
#endif
#ifdef BSP_UART_3_ENABLED
        case 3U:
            uart_handle = &s_uart_handle_3;
            break;
#endif
#ifdef BSP_UART_4_ENABLED
        case 4U:
            uart_handle = &s_uart_handle_4;
            break;
#endif
#ifdef BSP_UART_5_ENABLED
        case 5U:
            uart_handle = &s_uart_handle_5;
            break;
#endif
        default:
            break;
    }

    return uart_handle;
}

/**
 * @brief Configures clocks and TX/RX pins for enabled UARTs.
 * @param uart_handle Valid handle supplied by HAL_UART_Init.
 * @note Pin ports, GPIO clocks and remapping must describe the same hardware mapping.
 */
void HAL_UART_MspInit(UART_HandleTypeDef *uart_handle)
{
    GPIO_TypeDef    *tx_port       = NULL;
    GPIO_TypeDef    *rx_port       = NULL;
    uint32_t         tx_pin        = 0U;
    uint32_t         rx_pin        = 0U;
    bool             pins_selected = false;
    GPIO_InitTypeDef gpio_config   = {0};

    (void)uart_handle;

#ifdef BSP_UART_1_ENABLED
    {
        bool is_uart = uart_handle->Instance == USART1;

        if(is_uart)
        {
            __HAL_RCC_AFIO_CLK_ENABLE();
            __HAL_RCC_USART1_CLK_ENABLE();
            BSP_UART_TX_CLOCK_ENABLE_1();
            BSP_UART_RX_CLOCK_ENABLE_1();
            BSP_UART_REMAP_1();
            tx_port = BSP_UART_TX_PORT_1;
            rx_port = BSP_UART_RX_PORT_1;
            tx_pin  = BSP_UART_TX_PIN_1;
            rx_pin  = BSP_UART_RX_PIN_1;
        }
    }
#endif

#ifdef BSP_UART_2_ENABLED
    {
        bool is_uart = uart_handle->Instance == USART2;

        if(is_uart)
        {
            __HAL_RCC_AFIO_CLK_ENABLE();
            __HAL_RCC_USART2_CLK_ENABLE();
            BSP_UART_TX_CLOCK_ENABLE_2();
            BSP_UART_RX_CLOCK_ENABLE_2();
            BSP_UART_REMAP_2();
            tx_port = BSP_UART_TX_PORT_2;
            rx_port = BSP_UART_RX_PORT_2;
            tx_pin  = BSP_UART_TX_PIN_2;
            rx_pin  = BSP_UART_RX_PIN_2;
        }
    }
#endif

#ifdef BSP_UART_3_ENABLED
    {
        bool is_uart = uart_handle->Instance == USART3;

        if(is_uart)
        {
            __HAL_RCC_AFIO_CLK_ENABLE();
            __HAL_RCC_USART3_CLK_ENABLE();
            BSP_UART_TX_CLOCK_ENABLE_3();
            BSP_UART_RX_CLOCK_ENABLE_3();
            BSP_UART_REMAP_3();
            tx_port = BSP_UART_TX_PORT_3;
            rx_port = BSP_UART_RX_PORT_3;
            tx_pin  = BSP_UART_TX_PIN_3;
            rx_pin  = BSP_UART_RX_PIN_3;
        }
    }
#endif

#ifdef BSP_UART_4_ENABLED
    {
        bool is_uart = uart_handle->Instance == UART4;

        if(is_uart)
        {
            __HAL_RCC_AFIO_CLK_ENABLE();
            __HAL_RCC_UART4_CLK_ENABLE();
            BSP_UART_TX_CLOCK_ENABLE_4();
            BSP_UART_RX_CLOCK_ENABLE_4();
            tx_port = BSP_UART_TX_PORT_4;
            rx_port = BSP_UART_RX_PORT_4;
            tx_pin  = BSP_UART_TX_PIN_4;
            rx_pin  = BSP_UART_RX_PIN_4;
        }
    }
#endif

#ifdef BSP_UART_5_ENABLED
    {
        bool is_uart = uart_handle->Instance == UART5;

        if(is_uart)
        {
            __HAL_RCC_AFIO_CLK_ENABLE();
            __HAL_RCC_UART5_CLK_ENABLE();
            BSP_UART_TX_CLOCK_ENABLE_5();
            BSP_UART_RX_CLOCK_ENABLE_5();
            tx_port = BSP_UART_TX_PORT_5;
            rx_port = BSP_UART_RX_PORT_5;
            tx_pin  = BSP_UART_TX_PIN_5;
            rx_pin  = BSP_UART_RX_PIN_5;
        }
    }
#endif

    pins_selected = tx_port != NULL;
    if(!pins_selected)
    {
        return;
    }

    gpio_config.Pin   = tx_pin;
    gpio_config.Mode  = GPIO_MODE_AF_PP;
    gpio_config.Pull  = GPIO_NOPULL;
    gpio_config.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(tx_port, &gpio_config);

    gpio_config.Pin  = rx_pin;
    gpio_config.Mode = GPIO_MODE_INPUT;
    gpio_config.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(rx_port, &gpio_config);
}

bool bsp_uart_init(void)
{
    bool initialized = true;
#if defined(BSP_UART_1_ENABLED) || defined(BSP_UART_2_ENABLED) || defined(BSP_UART_3_ENABLED) ||   \
    defined(BSP_UART_4_ENABLED) || defined(BSP_UART_5_ENABLED)
    bool              current = false;
    HAL_StatusTypeDef result  = HAL_ERROR;
#endif

#ifdef BSP_UART_1_ENABLED
    s_uart_handle_1.Instance          = USART1;
    s_uart_handle_1.Init.BaudRate     = BSP_UART_BAUD_RATE_1;
    s_uart_handle_1.Init.WordLength   = BSP_UART_WORD_LENGTH_1;
    s_uart_handle_1.Init.StopBits     = BSP_UART_STOP_BITS_1;
    s_uart_handle_1.Init.Parity       = BSP_UART_PARITY_1;
    s_uart_handle_1.Init.Mode         = BSP_UART_MODE_1;
    s_uart_handle_1.Init.HwFlowCtl    = BSP_UART_HW_FLOW_CONTROL_1;
    s_uart_handle_1.Init.OverSampling = BSP_UART_OVERSAMPLING_1;

    result      = HAL_UART_Init(&s_uart_handle_1);
    current     = result == HAL_OK;
    initialized = initialized && current;
#endif
#ifdef BSP_UART_2_ENABLED
    s_uart_handle_2.Instance          = USART2;
    s_uart_handle_2.Init.BaudRate     = BSP_UART_BAUD_RATE_2;
    s_uart_handle_2.Init.WordLength   = BSP_UART_WORD_LENGTH_2;
    s_uart_handle_2.Init.StopBits     = BSP_UART_STOP_BITS_2;
    s_uart_handle_2.Init.Parity       = BSP_UART_PARITY_2;
    s_uart_handle_2.Init.Mode         = BSP_UART_MODE_2;
    s_uart_handle_2.Init.HwFlowCtl    = BSP_UART_HW_FLOW_CONTROL_2;
    s_uart_handle_2.Init.OverSampling = BSP_UART_OVERSAMPLING_2;

    result      = HAL_UART_Init(&s_uart_handle_2);
    current     = result == HAL_OK;
    initialized = initialized && current;
#endif
#ifdef BSP_UART_3_ENABLED
    s_uart_handle_3.Instance          = USART3;
    s_uart_handle_3.Init.BaudRate     = BSP_UART_BAUD_RATE_3;
    s_uart_handle_3.Init.WordLength   = BSP_UART_WORD_LENGTH_3;
    s_uart_handle_3.Init.StopBits     = BSP_UART_STOP_BITS_3;
    s_uart_handle_3.Init.Parity       = BSP_UART_PARITY_3;
    s_uart_handle_3.Init.Mode         = BSP_UART_MODE_3;
    s_uart_handle_3.Init.HwFlowCtl    = BSP_UART_HW_FLOW_CONTROL_3;
    s_uart_handle_3.Init.OverSampling = BSP_UART_OVERSAMPLING_3;

    result      = HAL_UART_Init(&s_uart_handle_3);
    current     = result == HAL_OK;
    initialized = initialized && current;
#endif
#ifdef BSP_UART_4_ENABLED
    s_uart_handle_4.Instance          = UART4;
    s_uart_handle_4.Init.BaudRate     = BSP_UART_BAUD_RATE_4;
    s_uart_handle_4.Init.WordLength   = BSP_UART_WORD_LENGTH_4;
    s_uart_handle_4.Init.StopBits     = BSP_UART_STOP_BITS_4;
    s_uart_handle_4.Init.Parity       = BSP_UART_PARITY_4;
    s_uart_handle_4.Init.Mode         = BSP_UART_MODE_4;
    s_uart_handle_4.Init.HwFlowCtl    = BSP_UART_HW_FLOW_CONTROL_4;
    s_uart_handle_4.Init.OverSampling = BSP_UART_OVERSAMPLING_4;

    result      = HAL_UART_Init(&s_uart_handle_4);
    current     = result == HAL_OK;
    initialized = initialized && current;
#endif
#ifdef BSP_UART_5_ENABLED
    s_uart_handle_5.Instance          = UART5;
    s_uart_handle_5.Init.BaudRate     = BSP_UART_BAUD_RATE_5;
    s_uart_handle_5.Init.WordLength   = BSP_UART_WORD_LENGTH_5;
    s_uart_handle_5.Init.StopBits     = BSP_UART_STOP_BITS_5;
    s_uart_handle_5.Init.Parity       = BSP_UART_PARITY_5;
    s_uart_handle_5.Init.Mode         = BSP_UART_MODE_5;
    s_uart_handle_5.Init.HwFlowCtl    = BSP_UART_HW_FLOW_CONTROL_5;
    s_uart_handle_5.Init.OverSampling = BSP_UART_OVERSAMPLING_5;

    result      = HAL_UART_Init(&s_uart_handle_5);
    current     = result == HAL_OK;
    initialized = initialized && current;
#endif

    return initialized;
}

bool bsp_uart_transmit(uint8_t        uart_number,
                       const uint8_t *data,
                       uint16_t       length,
                       uint32_t       timeout_ms)
{
    UART_HandleTypeDef *uart_handle = bsp_uart_get_handle(uart_number);
    bool                is_empty    = length == 0U;
    bool input_valid = (uart_handle != NULL) && (data != NULL) && (timeout_ms != UINT32_MAX);
    HAL_StatusTypeDef result = HAL_ERROR;

    if(is_empty)
    {
        return uart_handle != NULL;
    }
    if(!input_valid)
    {
        return false;
    }

    result = HAL_UART_Transmit(uart_handle, data, length, timeout_ms);
    return result == HAL_OK;
}
