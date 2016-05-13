#ifndef __STM32F7_DELAY_H
#define __STM32F7_DELAY_H
#ifdef __cplusplus
 extern "C" {
#endif
     
#include "stm32f7xx_hal.h"

#define DWT_CYCCNT  ((volatile uint32_t *)0xE0001004)
         
uint32_t Delay_Init(void);
uint32_t micros(void);
uint32_t millis(void);
__STATIC_INLINE void delay_us(__IO uint32_t micros)
{
    uint32_t start = DWT->CYCCNT;

    /* Go to number of cycles for system */
    micros *= (HAL_RCC_GetHCLKFreq() / 1000000);

    /* Delay till end */
    while ((DWT->CYCCNT - start) < micros);
}

__STATIC_INLINE void delay_ms(uint32_t millis)
{
	/* Use HAL library for delay ms purpose */
	HAL_Delay(millis);
}

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_DELAY_H */

