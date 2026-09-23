cmake_minimum_required(VERSION 3.22)
project(bootloader C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FIRMWARE_TARGET ${PROJECT_NAME})
set(HAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hardware/stm32f1xx_hal_driver)

add_executable(${FIRMWARE_TARGET}
    app/led/led.c
    core/application_boot.c
    core/main.c
    core/system_init.c
    core/stm32f1xx_it.c
    core/startup/startup_stm32f103xe.s
    core/system_clock/system_clock.c
    core/system_clock/system_stm32f1xx.c
    hardware/bsp/gpio/bsp_gpio.c
    hardware/bsp/stm32f1xx_hal_msp.c
    service/led/led_service.c
    service/time/delay_service.c
    ${HAL_DIR}/src/stm32f1xx_hal.c
    ${HAL_DIR}/src/stm32f1xx_hal_cortex.c
    ${HAL_DIR}/src/stm32f1xx_hal_dma.c
    ${HAL_DIR}/src/stm32f1xx_hal_exti.c
    ${HAL_DIR}/src/stm32f1xx_hal_flash.c
    ${HAL_DIR}/src/stm32f1xx_hal_flash_ex.c
    ${HAL_DIR}/src/stm32f1xx_hal_gpio.c
    ${HAL_DIR}/src/stm32f1xx_hal_gpio_ex.c
    ${HAL_DIR}/src/stm32f1xx_hal_pwr.c
    ${HAL_DIR}/src/stm32f1xx_hal_rcc.c
    ${HAL_DIR}/src/stm32f1xx_hal_rcc_ex.c
)

target_include_directories(${FIRMWARE_TARGET} PRIVATE
    app/led
    core
    core/system_clock
    core/version
    hardware/bsp/gpio
    service/led
    service/time
    hardware/cmsis/core/include
    hardware/cmsis/device/include
    ${HAL_DIR}/inc
    ${HAL_DIR}/inc/legacy
)

target_compile_definitions(${FIRMWARE_TARGET} PRIVATE USE_HAL_DRIVER STM32F103xE)
target_compile_options(${FIRMWARE_TARGET} PRIVATE -Wall -Wextra)
target_link_options(${FIRMWARE_TARGET} PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/core/linker/stm32f103ze.ld
    -L${CMAKE_CURRENT_SOURCE_DIR}/core/linker
    --specs=nano.specs
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map
    -Wl,--print-memory-usage
)
target_link_libraries(${FIRMWARE_TARGET} PRIVATE m)

set_target_properties(${FIRMWARE_TARGET} PROPERTIES SUFFIX ".elf")

add_custom_command(TARGET ${FIRMWARE_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/output
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${FIRMWARE_TARGET}> ${CMAKE_CURRENT_BINARY_DIR}/output/${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${FIRMWARE_TARGET}> ${CMAKE_CURRENT_BINARY_DIR}/output/${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${FIRMWARE_TARGET}>
)
