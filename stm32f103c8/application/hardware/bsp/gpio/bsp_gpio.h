/**
 * @file bsp_gpio.h
 * @brief Declares board GPIO initialization.
 */

#ifndef BSP_GPIO_H
#define BSP_GPIO_H

/**
 * @brief Enables board GPIO clocks and configures the LED initially off.
 * @pre Call once during hardware initialization, before concurrent GPIO users start.
 */
void bsp_gpio_init(void);
/**
 * @brief Toggles the board LED; call only after initialization from its owning task.
 * @note Not synchronized with other writers; this interface transfers no resources.
 */
void bsp_gpio_led_toggle(void);
/**
 * @brief Sets the LED off using a single register write, without blocking.
 * @pre GPIO initialization completed; the fatal path masks interrupts before calling.
 * @note Other output writers must be stopped to keep the fallback state latched.
 */
void bsp_gpio_safe_state(void);

#endif /** BSP_GPIO_H */
