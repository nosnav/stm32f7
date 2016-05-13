#include "stm32f7_delay.h"

__IO uint32_t msTime = 0;
__IO uint32_t usTicks = 0;
__IO uint32_t CycleCounter = 0;

uint32_t Delay_Init(void)
{
    uint32_t c;
    usTicks = (HAL_RCC_GetHCLKFreq() / 1000000);
    /* Enable TRC */
    CoreDebug->DEMCR &= ~0x01000000;
    CoreDebug->DEMCR |=  0x01000000;

    /* Enable counter */
    DWT->CTRL &= ~0x00000001;
    DWT->CTRL |=  0x00000001;

    /* Reset counter */
    DWT->CYCCNT = 0;

    /* Check if DWT has started */
    c = DWT->CYCCNT;

    /* 2 dummys */
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");

    /* Return difference, if result is zero, DWT has not started */
    return (DWT->CYCCNT - c);
}

/* Called from Systick handler */
void HAL_IncTick(void)
{
	/* Increase system time */
    CycleCounter = *DWT_CYCCNT;
	msTime++;
}

void HAL_Delay(uint32_t Delay)
{
    /* Delay for amount of milliseconds */
    /* Check if we are called from ISR */
    if (__get_IPSR() == 0)
    {
        /* Called from thread mode */
        uint32_t tickstart = HAL_GetTick();

        /* Count interrupts */
        while ((HAL_GetTick() - tickstart) < Delay);
    }
    else
    {
        /* Called from interrupt mode */
        while (Delay)
        {
            /* Check if timer reached zero after we last checked COUNTFLAG bit*/
            if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
            {
                Delay--;
            }
        }
    }
}

uint32_t HAL_GetTick(void)
{
	/* Return current time in milliseconds */
	return msTime;
}

uint32_t micros(void)
{
    register uint32_t OldCycle, Cycle, TimeMs;

    do
    {
        TimeMs = __LDREXW(&msTime);
        Cycle = *DWT_CYCCNT;
        OldCycle = CycleCounter;
    }
    while ( __STREXW( TimeMs , &msTime) );

    return (TimeMs * 1000) + (Cycle - OldCycle) / usTicks;
}

uint32_t millis(void)
{
    return msTime;
}
