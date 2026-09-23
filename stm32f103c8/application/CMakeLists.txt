cmake_minimum_required(VERSION 3.22)
project(application C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Expose the compiler-detected target C library to clangd through the database.
# clangd does not query GCC's system paths unless its client enables query-driver.
foreach(SYSTEM_INCLUDE_DIR IN LISTS CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES)
    if(EXISTS "${SYSTEM_INCLUDE_DIR}/stdlib.h")
        list(APPEND CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${SYSTEM_INCLUDE_DIR}")
    endif()
endforeach()

set(FIRMWARE_TARGET ${PROJECT_NAME})
set(HAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hardware/stm32f1xx_hal_driver)
set(FREERTOS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/middleware/freertos)
set(NANOPRINTF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/middleware/nanoprintf)

add_executable(${FIRMWARE_TARGET}
    app/led/led.c
    app/tasks/tasks.c
    app/system_manager/system_manager.c
    core/main.c
    core/system_init.c
    core/rtos_start.c
    core/rtos_fault.c
    core/stm32f1xx_it.c
    core/startup/startup_stm32f103xb.s
    core/system_clock/system_clock.c
    core/system_clock/system_stm32f1xx.c
    hardware/bsp/gpio/bsp_gpio.c
    hardware/bsp/uart/bsp_uart.c
    hardware/bsp/stm32f1xx_hal_msp.c
    service/led/led_service.c
    service/my_printf/my_printf.c
    ${NANOPRINTF_DIR}/npf_config.c
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
    ${HAL_DIR}/src/stm32f1xx_hal_uart.c
    ${FREERTOS_DIR}/source/croutine.c
    ${FREERTOS_DIR}/source/event_groups.c
    ${FREERTOS_DIR}/source/list.c
    ${FREERTOS_DIR}/source/queue.c
    ${FREERTOS_DIR}/source/stream_buffer.c
    ${FREERTOS_DIR}/source/tasks.c
    ${FREERTOS_DIR}/source/timers.c
    ${FREERTOS_DIR}/portable/gcc/arm_cm3/port.c
)

target_include_directories(${FIRMWARE_TARGET} PRIVATE
    app/led
    app/tasks
    app/system_manager
    core
    core/system_clock
    core/version
    hardware/bsp/gpio
    hardware/bsp/uart
    service/led
    service/my_printf
    hardware/cmsis/core/include
    hardware/cmsis/device/include
    ${HAL_DIR}/inc
    ${HAL_DIR}/inc/legacy
    ${FREERTOS_DIR}/include
    ${FREERTOS_DIR}/portable/gcc/arm_cm3
    ${NANOPRINTF_DIR}
)

target_compile_definitions(${FIRMWARE_TARGET} PRIVATE USE_HAL_DRIVER STM32F103xB)
target_compile_options(${FIRMWARE_TARGET} PRIVATE -Wall -Wextra)
target_link_options(${FIRMWARE_TARGET} PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/core/linker/stm32f103c8.ld
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
