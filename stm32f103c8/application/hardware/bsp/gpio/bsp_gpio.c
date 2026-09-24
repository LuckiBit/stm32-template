/**
 * @file bsp_gpio.c
 * @brief Configures every package GPIO from an independent per-pin macro block.
 */

#include "bsp_gpio.h"

#include "stm32f1xx_hal.h"

#include <stddef.h>
#include <stdint.h>

/*
 * Modify only the macros in the required pin block when its electrical
 * configuration changes. HSE and debug pins remain listed but INITIALIZE is false.
 */
/* GPIOA pin 0 configuration. */
#define BSP_GPIOA_0_PORT          GPIOA
#define BSP_GPIOA_0_PIN           GPIO_PIN_0
#define BSP_GPIOA_0_INITIALIZE    true
#define BSP_GPIOA_0_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_0_PULL          GPIO_NOPULL
#define BSP_GPIOA_0_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_0_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_0_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_0_IS_OUTPUT     false

/* GPIOA pin 1 configuration. */
#define BSP_GPIOA_1_PORT          GPIOA
#define BSP_GPIOA_1_PIN           GPIO_PIN_1
#define BSP_GPIOA_1_INITIALIZE    true
#define BSP_GPIOA_1_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_1_PULL          GPIO_NOPULL
#define BSP_GPIOA_1_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_1_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_1_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_1_IS_OUTPUT     false

/* GPIOA pin 2 configuration. */
#define BSP_GPIOA_2_PORT          GPIOA
#define BSP_GPIOA_2_PIN           GPIO_PIN_2
#define BSP_GPIOA_2_INITIALIZE    true
#define BSP_GPIOA_2_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_2_PULL          GPIO_NOPULL
#define BSP_GPIOA_2_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_2_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_2_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_2_IS_OUTPUT     false

/* GPIOA pin 3 configuration. */
#define BSP_GPIOA_3_PORT          GPIOA
#define BSP_GPIOA_3_PIN           GPIO_PIN_3
#define BSP_GPIOA_3_INITIALIZE    true
#define BSP_GPIOA_3_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_3_PULL          GPIO_NOPULL
#define BSP_GPIOA_3_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_3_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_3_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_3_IS_OUTPUT     false

/* GPIOA pin 4 configuration. */
#define BSP_GPIOA_4_PORT          GPIOA
#define BSP_GPIOA_4_PIN           GPIO_PIN_4
#define BSP_GPIOA_4_INITIALIZE    true
#define BSP_GPIOA_4_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_4_PULL          GPIO_NOPULL
#define BSP_GPIOA_4_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_4_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_4_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_4_IS_OUTPUT     false

/* GPIOA pin 5 configuration. */
#define BSP_GPIOA_5_PORT          GPIOA
#define BSP_GPIOA_5_PIN           GPIO_PIN_5
#define BSP_GPIOA_5_INITIALIZE    true
#define BSP_GPIOA_5_MODE          GPIO_MODE_OUTPUT_PP
#define BSP_GPIOA_5_PULL          GPIO_NOPULL
#define BSP_GPIOA_5_SPEED         GPIO_SPEED_FREQ_HIGH
#define BSP_GPIOA_5_INITIAL_STATE GPIO_PIN_SET
#define BSP_GPIOA_5_SAFE_STATE    GPIO_PIN_SET
#define BSP_GPIOA_5_IS_OUTPUT     true

/* GPIOA pin 6 configuration. */
#define BSP_GPIOA_6_PORT          GPIOA
#define BSP_GPIOA_6_PIN           GPIO_PIN_6
#define BSP_GPIOA_6_INITIALIZE    true
#define BSP_GPIOA_6_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_6_PULL          GPIO_NOPULL
#define BSP_GPIOA_6_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_6_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_6_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_6_IS_OUTPUT     false

/* GPIOA pin 7 configuration. */
#define BSP_GPIOA_7_PORT          GPIOA
#define BSP_GPIOA_7_PIN           GPIO_PIN_7
#define BSP_GPIOA_7_INITIALIZE    true
#define BSP_GPIOA_7_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_7_PULL          GPIO_NOPULL
#define BSP_GPIOA_7_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_7_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_7_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_7_IS_OUTPUT     false

/* GPIOA pin 8 configuration. */
#define BSP_GPIOA_8_PORT          GPIOA
#define BSP_GPIOA_8_PIN           GPIO_PIN_8
#define BSP_GPIOA_8_INITIALIZE    true
#define BSP_GPIOA_8_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_8_PULL          GPIO_NOPULL
#define BSP_GPIOA_8_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_8_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_8_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_8_IS_OUTPUT     false

/* GPIOA pin 9 configuration. */
#define BSP_GPIOA_9_PORT          GPIOA
#define BSP_GPIOA_9_PIN           GPIO_PIN_9
#define BSP_GPIOA_9_INITIALIZE    true
#define BSP_GPIOA_9_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_9_PULL          GPIO_NOPULL
#define BSP_GPIOA_9_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_9_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_9_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_9_IS_OUTPUT     false

/* GPIOA pin 10 configuration. */
#define BSP_GPIOA_10_PORT          GPIOA
#define BSP_GPIOA_10_PIN           GPIO_PIN_10
#define BSP_GPIOA_10_INITIALIZE    true
#define BSP_GPIOA_10_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_10_PULL          GPIO_NOPULL
#define BSP_GPIOA_10_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_10_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_10_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_10_IS_OUTPUT     false

/* GPIOA pin 11 configuration. */
#define BSP_GPIOA_11_PORT          GPIOA
#define BSP_GPIOA_11_PIN           GPIO_PIN_11
#define BSP_GPIOA_11_INITIALIZE    true
#define BSP_GPIOA_11_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_11_PULL          GPIO_NOPULL
#define BSP_GPIOA_11_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_11_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_11_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_11_IS_OUTPUT     false

/* GPIOA pin 12 configuration. */
#define BSP_GPIOA_12_PORT          GPIOA
#define BSP_GPIOA_12_PIN           GPIO_PIN_12
#define BSP_GPIOA_12_INITIALIZE    true
#define BSP_GPIOA_12_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_12_PULL          GPIO_NOPULL
#define BSP_GPIOA_12_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_12_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_12_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_12_IS_OUTPUT     false

/* GPIOA pin 13 configuration. */
#define BSP_GPIOA_13_PORT          GPIOA
#define BSP_GPIOA_13_PIN           GPIO_PIN_13
#define BSP_GPIOA_13_INITIALIZE    false
#define BSP_GPIOA_13_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_13_PULL          GPIO_NOPULL
#define BSP_GPIOA_13_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_13_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_13_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_13_IS_OUTPUT     false

/* GPIOA pin 14 configuration. */
#define BSP_GPIOA_14_PORT          GPIOA
#define BSP_GPIOA_14_PIN           GPIO_PIN_14
#define BSP_GPIOA_14_INITIALIZE    false
#define BSP_GPIOA_14_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_14_PULL          GPIO_NOPULL
#define BSP_GPIOA_14_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_14_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_14_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_14_IS_OUTPUT     false

/* GPIOA pin 15 configuration. */
#define BSP_GPIOA_15_PORT          GPIOA
#define BSP_GPIOA_15_PIN           GPIO_PIN_15
#define BSP_GPIOA_15_INITIALIZE    true
#define BSP_GPIOA_15_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOA_15_PULL          GPIO_NOPULL
#define BSP_GPIOA_15_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOA_15_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOA_15_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOA_15_IS_OUTPUT     false

/* GPIOB pin 0 configuration. */
#define BSP_GPIOB_0_PORT          GPIOB
#define BSP_GPIOB_0_PIN           GPIO_PIN_0
#define BSP_GPIOB_0_INITIALIZE    true
#define BSP_GPIOB_0_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_0_PULL          GPIO_NOPULL
#define BSP_GPIOB_0_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_0_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_0_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_0_IS_OUTPUT     false

/* GPIOB pin 1 configuration. */
#define BSP_GPIOB_1_PORT          GPIOB
#define BSP_GPIOB_1_PIN           GPIO_PIN_1
#define BSP_GPIOB_1_INITIALIZE    true
#define BSP_GPIOB_1_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_1_PULL          GPIO_NOPULL
#define BSP_GPIOB_1_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_1_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_1_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_1_IS_OUTPUT     false

/* GPIOB pin 2 configuration. */
#define BSP_GPIOB_2_PORT          GPIOB
#define BSP_GPIOB_2_PIN           GPIO_PIN_2
#define BSP_GPIOB_2_INITIALIZE    true
#define BSP_GPIOB_2_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_2_PULL          GPIO_NOPULL
#define BSP_GPIOB_2_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_2_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_2_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_2_IS_OUTPUT     false

/* GPIOB pin 3 configuration. */
#define BSP_GPIOB_3_PORT          GPIOB
#define BSP_GPIOB_3_PIN           GPIO_PIN_3
#define BSP_GPIOB_3_INITIALIZE    true
#define BSP_GPIOB_3_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_3_PULL          GPIO_NOPULL
#define BSP_GPIOB_3_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_3_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_3_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_3_IS_OUTPUT     false

/* GPIOB pin 4 configuration. */
#define BSP_GPIOB_4_PORT          GPIOB
#define BSP_GPIOB_4_PIN           GPIO_PIN_4
#define BSP_GPIOB_4_INITIALIZE    true
#define BSP_GPIOB_4_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_4_PULL          GPIO_NOPULL
#define BSP_GPIOB_4_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_4_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_4_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_4_IS_OUTPUT     false

/* GPIOB pin 5 configuration. */
#define BSP_GPIOB_5_PORT          GPIOB
#define BSP_GPIOB_5_PIN           GPIO_PIN_5
#define BSP_GPIOB_5_INITIALIZE    true
#define BSP_GPIOB_5_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_5_PULL          GPIO_NOPULL
#define BSP_GPIOB_5_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_5_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_5_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_5_IS_OUTPUT     false

/* GPIOB pin 6 configuration. */
#define BSP_GPIOB_6_PORT          GPIOB
#define BSP_GPIOB_6_PIN           GPIO_PIN_6
#define BSP_GPIOB_6_INITIALIZE    true
#define BSP_GPIOB_6_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_6_PULL          GPIO_NOPULL
#define BSP_GPIOB_6_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_6_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_6_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_6_IS_OUTPUT     false

/* GPIOB pin 7 configuration. */
#define BSP_GPIOB_7_PORT          GPIOB
#define BSP_GPIOB_7_PIN           GPIO_PIN_7
#define BSP_GPIOB_7_INITIALIZE    true
#define BSP_GPIOB_7_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_7_PULL          GPIO_NOPULL
#define BSP_GPIOB_7_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_7_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_7_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_7_IS_OUTPUT     false

/* GPIOB pin 8 configuration. */
#define BSP_GPIOB_8_PORT          GPIOB
#define BSP_GPIOB_8_PIN           GPIO_PIN_8
#define BSP_GPIOB_8_INITIALIZE    true
#define BSP_GPIOB_8_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_8_PULL          GPIO_NOPULL
#define BSP_GPIOB_8_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_8_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_8_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_8_IS_OUTPUT     false

/* GPIOB pin 9 configuration. */
#define BSP_GPIOB_9_PORT          GPIOB
#define BSP_GPIOB_9_PIN           GPIO_PIN_9
#define BSP_GPIOB_9_INITIALIZE    true
#define BSP_GPIOB_9_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_9_PULL          GPIO_NOPULL
#define BSP_GPIOB_9_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_9_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_9_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_9_IS_OUTPUT     false

/* GPIOB pin 10 configuration. */
#define BSP_GPIOB_10_PORT          GPIOB
#define BSP_GPIOB_10_PIN           GPIO_PIN_10
#define BSP_GPIOB_10_INITIALIZE    true
#define BSP_GPIOB_10_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_10_PULL          GPIO_NOPULL
#define BSP_GPIOB_10_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_10_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_10_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_10_IS_OUTPUT     false

/* GPIOB pin 11 configuration. */
#define BSP_GPIOB_11_PORT          GPIOB
#define BSP_GPIOB_11_PIN           GPIO_PIN_11
#define BSP_GPIOB_11_INITIALIZE    true
#define BSP_GPIOB_11_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_11_PULL          GPIO_NOPULL
#define BSP_GPIOB_11_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_11_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_11_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_11_IS_OUTPUT     false

/* GPIOB pin 12 configuration. */
#define BSP_GPIOB_12_PORT          GPIOB
#define BSP_GPIOB_12_PIN           GPIO_PIN_12
#define BSP_GPIOB_12_INITIALIZE    true
#define BSP_GPIOB_12_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_12_PULL          GPIO_NOPULL
#define BSP_GPIOB_12_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_12_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_12_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_12_IS_OUTPUT     false

/* GPIOB pin 13 configuration. */
#define BSP_GPIOB_13_PORT          GPIOB
#define BSP_GPIOB_13_PIN           GPIO_PIN_13
#define BSP_GPIOB_13_INITIALIZE    true
#define BSP_GPIOB_13_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_13_PULL          GPIO_NOPULL
#define BSP_GPIOB_13_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_13_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_13_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_13_IS_OUTPUT     false

/* GPIOB pin 14 configuration. */
#define BSP_GPIOB_14_PORT          GPIOB
#define BSP_GPIOB_14_PIN           GPIO_PIN_14
#define BSP_GPIOB_14_INITIALIZE    true
#define BSP_GPIOB_14_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_14_PULL          GPIO_NOPULL
#define BSP_GPIOB_14_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_14_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_14_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_14_IS_OUTPUT     false

/* GPIOB pin 15 configuration. */
#define BSP_GPIOB_15_PORT          GPIOB
#define BSP_GPIOB_15_PIN           GPIO_PIN_15
#define BSP_GPIOB_15_INITIALIZE    true
#define BSP_GPIOB_15_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOB_15_PULL          GPIO_NOPULL
#define BSP_GPIOB_15_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOB_15_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOB_15_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOB_15_IS_OUTPUT     false

/* GPIOC pin 13 configuration. */
#define BSP_GPIOC_13_PORT          GPIOC
#define BSP_GPIOC_13_PIN           GPIO_PIN_13
#define BSP_GPIOC_13_INITIALIZE    true
#define BSP_GPIOC_13_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOC_13_PULL          GPIO_NOPULL
#define BSP_GPIOC_13_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOC_13_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOC_13_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOC_13_IS_OUTPUT     false

/* GPIOC pin 14 configuration. */
#define BSP_GPIOC_14_PORT          GPIOC
#define BSP_GPIOC_14_PIN           GPIO_PIN_14
#define BSP_GPIOC_14_INITIALIZE    true
#define BSP_GPIOC_14_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOC_14_PULL          GPIO_NOPULL
#define BSP_GPIOC_14_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOC_14_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOC_14_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOC_14_IS_OUTPUT     false

/* GPIOC pin 15 configuration. */
#define BSP_GPIOC_15_PORT          GPIOC
#define BSP_GPIOC_15_PIN           GPIO_PIN_15
#define BSP_GPIOC_15_INITIALIZE    true
#define BSP_GPIOC_15_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOC_15_PULL          GPIO_NOPULL
#define BSP_GPIOC_15_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOC_15_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOC_15_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOC_15_IS_OUTPUT     false

/* GPIOD pin 0 configuration. */
#define BSP_GPIOD_0_PORT          GPIOD
#define BSP_GPIOD_0_PIN           GPIO_PIN_0
#define BSP_GPIOD_0_INITIALIZE    false
#define BSP_GPIOD_0_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOD_0_PULL          GPIO_NOPULL
#define BSP_GPIOD_0_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOD_0_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOD_0_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOD_0_IS_OUTPUT     false

/* GPIOD pin 1 configuration. */
#define BSP_GPIOD_1_PORT          GPIOD
#define BSP_GPIOD_1_PIN           GPIO_PIN_1
#define BSP_GPIOD_1_INITIALIZE    false
#define BSP_GPIOD_1_MODE          GPIO_MODE_ANALOG
#define BSP_GPIOD_1_PULL          GPIO_NOPULL
#define BSP_GPIOD_1_SPEED         GPIO_SPEED_FREQ_LOW
#define BSP_GPIOD_1_INITIAL_STATE GPIO_PIN_RESET
#define BSP_GPIOD_1_SAFE_STATE    GPIO_PIN_RESET
#define BSP_GPIOD_1_IS_OUTPUT     false

#define BSP_GPIO_PIN_CONFIG_LIST(APPLY)                                                            \
    APPLY(BSP_GPIOA_0)                                                                             \
    APPLY(BSP_GPIOA_1)                                                                             \
    APPLY(BSP_GPIOA_2)                                                                             \
    APPLY(BSP_GPIOA_3)                                                                             \
    APPLY(BSP_GPIOA_4)                                                                             \
    APPLY(BSP_GPIOA_5)                                                                             \
    APPLY(BSP_GPIOA_6)                                                                             \
    APPLY(BSP_GPIOA_7)                                                                             \
    APPLY(BSP_GPIOA_8)                                                                             \
    APPLY(BSP_GPIOA_9)                                                                             \
    APPLY(BSP_GPIOA_10)                                                                            \
    APPLY(BSP_GPIOA_11)                                                                            \
    APPLY(BSP_GPIOA_12)                                                                            \
    APPLY(BSP_GPIOA_13)                                                                            \
    APPLY(BSP_GPIOA_14)                                                                            \
    APPLY(BSP_GPIOA_15)                                                                            \
    APPLY(BSP_GPIOB_0)                                                                             \
    APPLY(BSP_GPIOB_1)                                                                             \
    APPLY(BSP_GPIOB_2)                                                                             \
    APPLY(BSP_GPIOB_3)                                                                             \
    APPLY(BSP_GPIOB_4)                                                                             \
    APPLY(BSP_GPIOB_5)                                                                             \
    APPLY(BSP_GPIOB_6)                                                                             \
    APPLY(BSP_GPIOB_7)                                                                             \
    APPLY(BSP_GPIOB_8)                                                                             \
    APPLY(BSP_GPIOB_9)                                                                             \
    APPLY(BSP_GPIOB_10)                                                                            \
    APPLY(BSP_GPIOB_11)                                                                            \
    APPLY(BSP_GPIOB_12)                                                                            \
    APPLY(BSP_GPIOB_13)                                                                            \
    APPLY(BSP_GPIOB_14)                                                                            \
    APPLY(BSP_GPIOB_15)                                                                            \
    APPLY(BSP_GPIOC_13)                                                                            \
    APPLY(BSP_GPIOC_14)                                                                            \
    APPLY(BSP_GPIOC_15)                                                                            \
    APPLY(BSP_GPIOD_0)                                                                             \
    APPLY(BSP_GPIOD_1)

#define BSP_GPIO_LOAD_CASE(pin_name)                                                               \
    case pin_name:                                                                                 \
        config.port          = pin_name##_PORT;                                                    \
        config.pin           = pin_name##_PIN;                                                     \
        config.initialize    = pin_name##_INITIALIZE;                                              \
        config.mode          = pin_name##_MODE;                                                    \
        config.pull          = pin_name##_PULL;                                                    \
        config.speed         = pin_name##_SPEED;                                                   \
        config.initial_state = pin_name##_INITIAL_STATE;                                           \
        config.safe_state    = pin_name##_SAFE_STATE;                                              \
        config.is_output     = pin_name##_IS_OUTPUT;                                               \
        break;

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
    uint32_t      mode;
    uint32_t      pull;
    uint32_t      speed;
    GPIO_PinState initial_state;
    GPIO_PinState safe_state;
    bool          initialize;
    bool          is_output;
} bsp_gpio_pin_config_t;

static bool bsp_gpio_pin_is_valid(bsp_gpio_pin_t pin_id)
{
    return (uint32_t)pin_id < (uint32_t)BSP_GPIO_PIN_COUNT;
}

static bool bsp_gpio_level_is_valid(bsp_gpio_level_t level)
{
    return (level == BSP_GPIO_LEVEL_LOW) || (level == BSP_GPIO_LEVEL_HIGH);
}

static bsp_gpio_pin_config_t bsp_gpio_get_config(bsp_gpio_pin_t pin_id)
{
    bsp_gpio_pin_config_t config = {0};

    switch(pin_id)
    {
        BSP_GPIO_PIN_CONFIG_LIST(BSP_GPIO_LOAD_CASE)

        default:
            break;
    }

    return config;
}

static void bsp_gpio_apply_level(GPIO_TypeDef *port, uint16_t pin, bsp_gpio_level_t level)
{
    uint32_t bsrr_value = (uint32_t)pin;

    if(level == BSP_GPIO_LEVEL_LOW)
    {
        bsrr_value <<= 16U;
    }
    port->BSRR = bsrr_value;
}

static void bsp_gpio_enable_port_clocks(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
}

void bsp_gpio_init(void)
{
    GPIO_InitTypeDef gpio_config = {0};
    uint32_t         pin_index   = 0U;

    bsp_gpio_enable_port_clocks();

    for(pin_index = 0U; pin_index < (uint32_t)BSP_GPIO_PIN_COUNT; pin_index++)
    {
        bsp_gpio_pin_config_t config = bsp_gpio_get_config((bsp_gpio_pin_t)pin_index);

        if(!config.initialize)
        {
            continue;
        }

        if(config.is_output)
        {
            bsp_gpio_apply_level(config.port,
                                 config.pin,
                                 config.initial_state == GPIO_PIN_SET ? BSP_GPIO_LEVEL_HIGH
                                                                      : BSP_GPIO_LEVEL_LOW);
        }

        gpio_config.Pin   = config.pin;
        gpio_config.Mode  = config.mode;
        gpio_config.Pull  = config.pull;
        gpio_config.Speed = config.speed;
        HAL_GPIO_Init(config.port, &gpio_config);
    }
}

bool bsp_gpio_write(bsp_gpio_pin_t pin_id, bsp_gpio_level_t level)
{
    bsp_gpio_pin_config_t config = {0};

    if(!bsp_gpio_pin_is_valid(pin_id) || !bsp_gpio_level_is_valid(level))
    {
        return false;
    }

    config = bsp_gpio_get_config(pin_id);
    if(!config.initialize || !config.is_output)
    {
        return false;
    }

    bsp_gpio_apply_level(config.port, config.pin, level);
    return true;
}

bool bsp_gpio_toggle(bsp_gpio_pin_t pin_id)
{
    bsp_gpio_pin_config_t config = {0};

    if(!bsp_gpio_pin_is_valid(pin_id))
    {
        return false;
    }

    config = bsp_gpio_get_config(pin_id);
    if(!config.initialize || !config.is_output)
    {
        return false;
    }

    HAL_GPIO_TogglePin(config.port, config.pin);
    return true;
}

bool bsp_gpio_read(bsp_gpio_pin_t pin_id, bsp_gpio_level_t *level)
{
    bsp_gpio_pin_config_t config    = {0};
    GPIO_PinState         pin_state = GPIO_PIN_RESET;

    if(!bsp_gpio_pin_is_valid(pin_id) || (level == NULL))
    {
        return false;
    }

    config = bsp_gpio_get_config(pin_id);
    if(!config.initialize)
    {
        return false;
    }

    pin_state = HAL_GPIO_ReadPin(config.port, config.pin);
    *level    = pin_state == GPIO_PIN_SET ? BSP_GPIO_LEVEL_HIGH : BSP_GPIO_LEVEL_LOW;
    return true;
}

void bsp_gpio_safe_state(void)
{
    uint32_t pin_index = 0U;

    for(pin_index = 0U; pin_index < (uint32_t)BSP_GPIO_PIN_COUNT; pin_index++)
    {
        bsp_gpio_pin_config_t config = bsp_gpio_get_config((bsp_gpio_pin_t)pin_index);

        if(config.initialize && config.is_output)
        {
            bsp_gpio_apply_level(config.port,
                                 config.pin,
                                 config.safe_state == GPIO_PIN_SET ? BSP_GPIO_LEVEL_HIGH
                                                                   : BSP_GPIO_LEVEL_LOW);
        }
    }
}
