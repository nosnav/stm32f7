#ifndef __STM32F7_SYSTEM_H
#define __STM32F7_SYSTEM_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"
     
void System_Init(void);
void SystemClock_Init(void);
void Error_Handler(void);
void MPU_Config(void);
void CPU_CACHE_Enable(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_SYSTEM_H */

