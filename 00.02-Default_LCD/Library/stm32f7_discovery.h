#ifndef __STM32F7_DISCOVERY_H
#define __STM32F7_DISCOVERY_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"

//#define LED_GREEN
#define LED_PORT        GPIOI
#define LED_PIN         GPIO_PIN_1
     
#define BUTTON_PORT     GPIOI
#define BUTTON_PIN      GPIO_PIN_11

void LED_Init(void);
void LED_Off(void);
void LED_On(void);
void LED_Toggle(void);

void BUTTON_Init(void);
         
#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_DISCOVERY_H */

