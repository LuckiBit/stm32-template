/**
 * @file bsp_uart.h
 * @brief Declares configurable board UART interfaces.
 */

#ifndef BSP_UART_H
#define BSP_UART_H

#include "stm32f1xx_hal.h"

#include <stdbool.h>
#include <stdint.h>

/* UART switches: 1 = enabled, 0 = disabled. */
#define BSP_UART_1_ENABLE 1
#define BSP_UART_2_ENABLE 0
#define BSP_UART_3_ENABLE 0
#define BSP_UART_4_ENABLE 0
#define BSP_UART_5_ENABLE 0

#if(BSP_UART_1_ENABLE != 0) && (BSP_UART_1_ENABLE != 1)
#error "BSP_UART_1_ENABLE must be 0 or 1"
#endif
#if(BSP_UART_2_ENABLE != 0) && (BSP_UART_2_ENABLE != 1)
#error "BSP_UART_2_ENABLE must be 0 or 1"
#endif
#if(BSP_UART_3_ENABLE != 0) && (BSP_UART_3_ENABLE != 1)
#error "BSP_UART_3_ENABLE must be 0 or 1"
#endif
#if(BSP_UART_4_ENABLE != 0) && (BSP_UART_4_ENABLE != 1)
#error "BSP_UART_4_ENABLE must be 0 or 1"
#endif
#if(BSP_UART_5_ENABLE != 0) && (BSP_UART_5_ENABLE != 1)
#error "BSP_UART_5_ENABLE must be 0 or 1"
#endif

/* Map UART switches to presence macros used by the BSP. */
#if BSP_UART_1_ENABLE
#define BSP_UART_1_ENABLED
#endif

#if BSP_UART_2_ENABLE
#define BSP_UART_2_ENABLED
#endif

#if BSP_UART_3_ENABLE
#define BSP_UART_3_ENABLED
#endif

#if BSP_UART_4_ENABLE
#define BSP_UART_4_ENABLED
#endif

#if BSP_UART_5_ENABLE
#define BSP_UART_5_ENABLED
#endif

#define BSP_UART_BAUD_RATE_1         115200U
#define BSP_UART_WORD_LENGTH_1       UART_WORDLENGTH_8B
#define BSP_UART_STOP_BITS_1         UART_STOPBITS_1
#define BSP_UART_PARITY_1            UART_PARITY_NONE
#define BSP_UART_MODE_1              UART_MODE_TX_RX
#define BSP_UART_HW_FLOW_CONTROL_1   UART_HWCONTROL_NONE
#define BSP_UART_OVERSAMPLING_1      UART_OVERSAMPLING_16
#define BSP_UART_TX_PORT_1           GPIOA
#define BSP_UART_TX_PIN_1            GPIO_PIN_9
#define BSP_UART_RX_PORT_1           GPIOA
#define BSP_UART_RX_PIN_1            GPIO_PIN_10
#define BSP_UART_TX_CLOCK_ENABLE_1() __HAL_RCC_GPIOA_CLK_ENABLE()
#define BSP_UART_RX_CLOCK_ENABLE_1() __HAL_RCC_GPIOA_CLK_ENABLE()
#define BSP_UART_REMAP_1()           __HAL_AFIO_REMAP_USART1_DISABLE()

#define BSP_UART_BAUD_RATE_2         115200U
#define BSP_UART_WORD_LENGTH_2       UART_WORDLENGTH_8B
#define BSP_UART_STOP_BITS_2         UART_STOPBITS_1
#define BSP_UART_PARITY_2            UART_PARITY_NONE
#define BSP_UART_MODE_2              UART_MODE_TX_RX
#define BSP_UART_HW_FLOW_CONTROL_2   UART_HWCONTROL_NONE
#define BSP_UART_OVERSAMPLING_2      UART_OVERSAMPLING_16
#define BSP_UART_TX_PORT_2           GPIOA
#define BSP_UART_TX_PIN_2            GPIO_PIN_2
#define BSP_UART_RX_PORT_2           GPIOA
#define BSP_UART_RX_PIN_2            GPIO_PIN_3
#define BSP_UART_TX_CLOCK_ENABLE_2() __HAL_RCC_GPIOA_CLK_ENABLE()
#define BSP_UART_RX_CLOCK_ENABLE_2() __HAL_RCC_GPIOA_CLK_ENABLE()
#define BSP_UART_REMAP_2()           __HAL_AFIO_REMAP_USART2_DISABLE()

#define BSP_UART_BAUD_RATE_3         115200U
#define BSP_UART_WORD_LENGTH_3       UART_WORDLENGTH_8B
#define BSP_UART_STOP_BITS_3         UART_STOPBITS_1
#define BSP_UART_PARITY_3            UART_PARITY_NONE
#define BSP_UART_MODE_3              UART_MODE_TX_RX
#define BSP_UART_HW_FLOW_CONTROL_3   UART_HWCONTROL_NONE
#define BSP_UART_OVERSAMPLING_3      UART_OVERSAMPLING_16
#define BSP_UART_TX_PORT_3           GPIOB
#define BSP_UART_TX_PIN_3            GPIO_PIN_10
#define BSP_UART_RX_PORT_3           GPIOB
#define BSP_UART_RX_PIN_3            GPIO_PIN_11
#define BSP_UART_TX_CLOCK_ENABLE_3() __HAL_RCC_GPIOB_CLK_ENABLE()
#define BSP_UART_RX_CLOCK_ENABLE_3() __HAL_RCC_GPIOB_CLK_ENABLE()
#define BSP_UART_REMAP_3()           __HAL_AFIO_REMAP_USART3_DISABLE()

#define BSP_UART_BAUD_RATE_4         115200U
#define BSP_UART_WORD_LENGTH_4       UART_WORDLENGTH_8B
#define BSP_UART_STOP_BITS_4         UART_STOPBITS_1
#define BSP_UART_PARITY_4            UART_PARITY_NONE
#define BSP_UART_MODE_4              UART_MODE_TX_RX
#define BSP_UART_HW_FLOW_CONTROL_4   UART_HWCONTROL_NONE
#define BSP_UART_OVERSAMPLING_4      UART_OVERSAMPLING_16
#define BSP_UART_TX_PORT_4           GPIOC
#define BSP_UART_TX_PIN_4            GPIO_PIN_10
#define BSP_UART_RX_PORT_4           GPIOC
#define BSP_UART_RX_PIN_4            GPIO_PIN_11
#define BSP_UART_TX_CLOCK_ENABLE_4() __HAL_RCC_GPIOC_CLK_ENABLE()
#define BSP_UART_RX_CLOCK_ENABLE_4() __HAL_RCC_GPIOC_CLK_ENABLE()

#define BSP_UART_BAUD_RATE_5         115200U
#define BSP_UART_WORD_LENGTH_5       UART_WORDLENGTH_8B
#define BSP_UART_STOP_BITS_5         UART_STOPBITS_1
#define BSP_UART_PARITY_5            UART_PARITY_NONE
#define BSP_UART_MODE_5              UART_MODE_TX_RX
#define BSP_UART_HW_FLOW_CONTROL_5   UART_HWCONTROL_NONE
#define BSP_UART_OVERSAMPLING_5      UART_OVERSAMPLING_16
#define BSP_UART_TX_PORT_5           GPIOC
#define BSP_UART_TX_PIN_5            GPIO_PIN_12
#define BSP_UART_RX_PORT_5           GPIOD
#define BSP_UART_RX_PIN_5            GPIO_PIN_2
#define BSP_UART_TX_CLOCK_ENABLE_5() __HAL_RCC_GPIOC_CLK_ENABLE()
#define BSP_UART_RX_CLOCK_ENABLE_5() __HAL_RCC_GPIOD_CLK_ENABLE()

/**
 * @brief Initializes enabled UARTs using their individual configuration.
 * @pre Call once after the system clock setup and before concurrent UART users.
 * @return true if every enabled UART initialized successfully.
 */
bool bsp_uart_init(void);

/**
 * @brief Sends bytes through an enabled UART using polling.
 * @param uart_number UART number from 1 through 5.
 * @param data Readable buffer for length bytes; NULL is allowed only for zero length.
 * @param length Number of bytes to send; zero is a successful no-op.
 * @param timeout_ms Finite HAL tick timeout; UINT32_MAX is rejected.
 * @pre Initialization succeeded and the HAL tick is running. Serialize callers externally;
 * call from main or task context, never from an ISR or an interrupt-disabled fault path.
 * @return true if all bytes were sent; false on invalid input, disabled UART or timeout.
 */
bool bsp_uart_transmit(uint8_t        uart_number,
                       const uint8_t *data,
                       uint16_t       length,
                       uint32_t       timeout_ms);

#endif /** BSP_UART_H */
