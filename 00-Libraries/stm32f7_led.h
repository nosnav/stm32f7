#ifndef __STM32F7_LED_H
#define __STM32F7_LED_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"

typedef enum 
{
    LED1 = 0,
    LED3 = 1,
    LED6 = 2,
    ALL = 3
} Led_TypeDef;

typedef enum 
{
    OFF = 0,
    ON = 1
} Led_State;

#define LED1_PIN                         GPIO_PIN_1
#define LED1_PORT                   GPIOI
#define LED1_CLK_ENABLE()           __GPIOI_CLK_ENABLE()

#define LED3_PIN                         GPIO_PIN_3
#define LED3_PORT                   GPIOE
#define LED3_CLK_ENABLE()           __GPIOE_CLK_ENABLE() 
   
#define LED6_PIN                         GPIO_PIN_4
#define LED6_PORT                   GPIOD
#define LED6_CLK_ENABLE()           __GPIOD_CLK_ENABLE()

void LED_Init(Led_TypeDef Led);
void LED_Off(Led_TypeDef Led);
void LED_On(Led_TypeDef Led);
void LED_Toggle(Led_TypeDef Led);
void LED_Set(Led_TypeDef led, Led_State state);
         
#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_LED_H */

