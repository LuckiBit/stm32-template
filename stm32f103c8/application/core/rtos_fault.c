/**
 * @file rtos_fault.c
 * @brief Captures the first fatal RTOS error and stops without scheduler services.
 */

#include "rtos_fault.h"
#include "FreeRTOS.h"
#include "bsp_gpio.h"
#include "stm32f1xx.h"
#include "task.h"

#include <stdbool.h>

volatile rtos_fault_t g_rtos_fault = RTOS_FAULT_NONE;

_Noreturn void rtos_fault_stop(rtos_fault_t fault)
{
    bool is_first_fault = false;

    __disable_irq();
    is_first_fault = g_rtos_fault == RTOS_FAULT_NONE;
    if(is_first_fault)
    {
        g_rtos_fault = fault;
    }
    bsp_gpio_safe_state();
    for(;;)
    {
        __NOP();
    }
}

void vApplicationStackOverflowHook(TaskHandle_t task, char *task_name)
{
    (void)task;
    (void)task_name;
    rtos_fault_stop(RTOS_FAULT_STACK_OVERFLOW);
}
