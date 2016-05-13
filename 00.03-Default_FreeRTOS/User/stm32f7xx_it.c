#include "main.h"
#include "stm32f7xx_it.h"

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

__weak void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

__weak void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
    osSystickHandler();
	HAL_IncTick();
}
