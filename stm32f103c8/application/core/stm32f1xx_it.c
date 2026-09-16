#include "stm32f1xx_it.h"

#include "FreeRTOS.h"
#include "stm32f1xx_hal.h"
#include "task.h"

void xPortSysTickHandler(void);

void NMI_Handler(void)
{
    while(1)
    {
    }
}

void HardFault_Handler(void)
{
    while(1)
    {
    }
}

void MemManage_Handler(void)
{
    while(1)
    {
    }
}

void BusFault_Handler(void)
{
    while(1)
    {
    }
}

void UsageFault_Handler(void)
{
    while(1)
    {
    }
}

void DebugMon_Handler(void)
{
}

void SysTick_Handler(void)
{
    HAL_IncTick();

    if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        xPortSysTickHandler();
    }
}
