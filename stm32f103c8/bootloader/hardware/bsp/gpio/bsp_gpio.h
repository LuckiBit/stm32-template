/**
 * @file bsp_gpio.h
 * @brief Declares generic board GPIO pin operations.
 */

#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include <stdbool.h>

/**
 * @brief Physical GPIO identifiers available on this MCU package.
 * @note Identifiers use the GPIO port and pin number directly.
 */
typedef enum
{
    BSP_GPIOA_0 = 0,
    BSP_GPIOA_1,
    BSP_GPIOA_2,
    BSP_GPIOA_3,
    BSP_GPIOA_4,
    BSP_GPIOA_5,
    BSP_GPIOA_6,
    BSP_GPIOA_7,
    BSP_GPIOA_8,
    BSP_GPIOA_9,
    BSP_GPIOA_10,
    BSP_GPIOA_11,
    BSP_GPIOA_12,
    BSP_GPIOA_13,
    BSP_GPIOA_14,
    BSP_GPIOA_15,
    BSP_GPIOB_0,
    BSP_GPIOB_1,
    BSP_GPIOB_2,
    BSP_GPIOB_3,
    BSP_GPIOB_4,
    BSP_GPIOB_5,
    BSP_GPIOB_6,
    BSP_GPIOB_7,
    BSP_GPIOB_8,
    BSP_GPIOB_9,
    BSP_GPIOB_10,
    BSP_GPIOB_11,
    BSP_GPIOB_12,
    BSP_GPIOB_13,
    BSP_GPIOB_14,
    BSP_GPIOB_15,
    BSP_GPIOC_13,
    BSP_GPIOC_14,
    BSP_GPIOC_15,
    BSP_GPIOD_0,
    BSP_GPIOD_1,
    BSP_GPIO_PIN_COUNT
} bsp_gpio_pin_t;

/** @brief Raw electrical level used by GPIO pin operations. */
typedef enum
{
    BSP_GPIO_LEVEL_LOW = 0,
    BSP_GPIO_LEVEL_HIGH
} bsp_gpio_level_t;

/**
 * @brief Initializes every pin whose independent INITIALIZE macro is true.
 * @pre Call once after HAL and system clock initialization, before peripheral BSP initialization.
 */
void bsp_gpio_init(void);

/**
 * @brief Writes one configured output pin using an atomic BSRR access.
 * @return true when the pin is initialized as an output; otherwise false.
 */
bool bsp_gpio_write(bsp_gpio_pin_t pin_id, bsp_gpio_level_t level);

/**
 * @brief Toggles one configured output pin.
 * @note Not synchronized with other writers; each pin must have a single owner.
 * @return true when the pin is initialized as an output; otherwise false.
 */
bool bsp_gpio_toggle(bsp_gpio_pin_t pin_id);

/**
 * @brief Reads the electrical level of one initialized pin.
 * @param level Destination for the sampled level.
 * @return true when the pin is initialized and the destination is valid; otherwise false.
 */
bool bsp_gpio_read(bsp_gpio_pin_t pin_id, bsp_gpio_level_t *level);

/**
 * @brief Drives every initialized output to its independently configured safe level.
 * @note Uses direct BSRR writes and is safe for the interrupt-disabled fatal path.
 */
void bsp_gpio_safe_state(void);

#endif /* BSP_GPIO_H */
