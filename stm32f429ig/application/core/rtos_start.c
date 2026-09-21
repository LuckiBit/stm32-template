/**
 * @file rtos_start.c
 * @brief Creates fixed modules before transferring control to the scheduler.
 */

#include "rtos_start.h"
#include "FreeRTOS.h"
#include "my_printf.h"
#include "rtos_fault.h"
#include "system_manager.h"
#include "task.h"
#include "tasks.h"

#include <stdbool.h>

_Noreturn void rtos_start(void)
{
    bool       create_failed = false;
    BaseType_t create_result = pdFAIL;

    create_failed = !my_printf_init();
    if(create_failed)
    {
        rtos_fault_stop(RTOS_FAULT_SERVICE_CREATE);
    }

    create_result = system_manager_create(tasks_start, REQUIRED_TASKS);
    create_failed = create_result != pdPASS;
    if(create_failed)
    {
        rtos_fault_stop(RTOS_FAULT_MANAGER_CREATE);
    }

    create_failed = !tasks_create();
    if(create_failed)
    {
        rtos_fault_stop(RTOS_FAULT_APPLICATION_CREATE);
    }

    vTaskStartScheduler();
    rtos_fault_stop(RTOS_FAULT_SCHEDULER_RETURN);
}
