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
    BSP_GPIOC_0,
    BSP_GPIOC_1,
    BSP_GPIOC_2,
    BSP_GPIOC_3,
    BSP_GPIOC_4,
    BSP_GPIOC_5,
    BSP_GPIOC_6,
    BSP_GPIOC_7,
    BSP_GPIOC_8,
    BSP_GPIOC_9,
    BSP_GPIOC_10,
    BSP_GPIOC_11,
    BSP_GPIOC_12,
    BSP_GPIOC_13,
    BSP_GPIOC_14,
    BSP_GPIOC_15,
    BSP_GPIOD_0,
    BSP_GPIOD_1,
    BSP_GPIOD_2,
    BSP_GPIOD_3,
    BSP_GPIOD_4,
    BSP_GPIOD_5,
    BSP_GPIOD_6,
    BSP_GPIOD_7,
    BSP_GPIOD_8,
    BSP_GPIOD_9,
    BSP_GPIOD_10,
    BSP_GPIOD_11,
    BSP_GPIOD_12,
    BSP_GPIOD_13,
    BSP_GPIOD_14,
    BSP_GPIOD_15,
    BSP_GPIOE_0,
    BSP_GPIOE_1,
    BSP_GPIOE_2,
    BSP_GPIOE_3,
    BSP_GPIOE_4,
    BSP_GPIOE_5,
    BSP_GPIOE_6,
    BSP_GPIOE_7,
    BSP_GPIOE_8,
    BSP_GPIOE_9,
    BSP_GPIOE_10,
    BSP_GPIOE_11,
    BSP_GPIOE_12,
    BSP_GPIOE_13,
    BSP_GPIOE_14,
    BSP_GPIOE_15,
    BSP_GPIOF_0,
    BSP_GPIOF_1,
    BSP_GPIOF_2,
    BSP_GPIOF_3,
    BSP_GPIOF_4,
    BSP_GPIOF_5,
    BSP_GPIOF_6,
    BSP_GPIOF_7,
    BSP_GPIOF_8,
    BSP_GPIOF_9,
    BSP_GPIOF_10,
    BSP_GPIOF_11,
    BSP_GPIOF_12,
    BSP_GPIOF_13,
    BSP_GPIOF_14,
    BSP_GPIOF_15,
    BSP_GPIOG_0,
    BSP_GPIOG_1,
    BSP_GPIOG_2,
    BSP_GPIOG_3,
    BSP_GPIOG_4,
    BSP_GPIOG_5,
    BSP_GPIOG_6,
    BSP_GPIOG_7,
    BSP_GPIOG_8,
    BSP_GPIOG_9,
    BSP_GPIOG_10,
    BSP_GPIOG_11,
    BSP_GPIOG_12,
    BSP_GPIOG_13,
    BSP_GPIOG_14,
    BSP_GPIOG_15,
    BSP_GPIOH_0,
    BSP_GPIOH_1,
    BSP_GPIOH_2,
    BSP_GPIOH_3,
    BSP_GPIOH_4,
    BSP_GPIOH_5,
    BSP_GPIOH_6,
    BSP_GPIOH_7,
    BSP_GPIOH_8,
    BSP_GPIOH_9,
    BSP_GPIOH_10,
    BSP_GPIOH_11,
    BSP_GPIOH_12,
    BSP_GPIOH_13,
    BSP_GPIOH_14,
    BSP_GPIOH_15,
    BSP_GPIOI_0,
    BSP_GPIOI_1,
    BSP_GPIOI_2,
    BSP_GPIOI_3,
    BSP_GPIOI_4,
    BSP_GPIOI_5,
    BSP_GPIOI_6,
    BSP_GPIOI_7,
    BSP_GPIOI_8,
    BSP_GPIOI_9,
    BSP_GPIOI_10,
    BSP_GPIOI_11,
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
