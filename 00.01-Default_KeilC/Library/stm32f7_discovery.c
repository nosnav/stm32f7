#include "stm32f7_discovery.h"

void LED_Init(Led_TypeDef Led)
{
    uint8_t LED = (uint8_t)Led;
    GPIO_InitTypeDef  GPIO_InitStruct;

    switch(LED)
    {
        case LED1:
            LED1_CLK_ENABLE();
        
            GPIO_InitStruct.Pin = LED1_PIN;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

            HAL_GPIO_Init(LED1_PORT, &GPIO_InitStruct);

            HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
            break;
        case LED3:
            LED3_CLK_ENABLE();
        
            GPIO_InitStruct.Pin = LED3_PIN;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

            HAL_GPIO_Init(LED3_PORT, &GPIO_InitStruct);

            HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET);
            break;
        case LED6:
            LED6_CLK_ENABLE();
        
            GPIO_InitStruct.Pin = LED6_PIN;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

            HAL_GPIO_Init(LED6_PORT, &GPIO_InitStruct);

            HAL_GPIO_WritePin(LED6_PORT, LED6_PIN, GPIO_PIN_SET);
            break;
        case ALL:
            LED1_CLK_ENABLE();
            LED3_CLK_ENABLE();
            LED6_CLK_ENABLE();
        
            GPIO_InitStruct.Pin = LED1_PIN;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
            HAL_GPIO_Init(LED1_PORT, &GPIO_InitStruct);
        
            GPIO_InitStruct.Pin = LED3_PIN;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
            HAL_GPIO_Init(LED3_PORT, &GPIO_InitStruct);
        
            GPIO_InitStruct.Pin = LED6_PIN;
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
            HAL_GPIO_Init(LED6_PORT, &GPIO_InitStruct);

            HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED6_PORT, LED6_PIN, GPIO_PIN_SET);
            break;
    }
}

void LED_Off(Led_TypeDef Led)
{
    uint8_t LED = (uint8_t)Led;
    switch(LED)
    {
        case LED1:
            LED1_PORT->BSRR = (uint32_t)LED1_PIN << 16;
            break;
        case LED3:
            LED3_PORT->BSRR = LED3_PIN;
            break;
        case LED6:
            LED6_PORT->BSRR = LED6_PIN;
            break;
        case ALL:
            LED1_PORT->BSRR = (uint32_t)LED1_PIN << 16;
            LED3_PORT->BSRR = LED3_PIN;
            LED6_PORT->BSRR = LED6_PIN;
            break;
    }
}

void LED_On(Led_TypeDef Led)
{
    uint8_t LED = (uint8_t)Led;
    switch(LED)
    {
        case LED1:
            LED1_PORT->BSRR = LED1_PIN;
            break;
        case LED3:
            LED3_PORT->BSRR = (uint32_t)LED3_PIN << 16;
            break;
        case LED6:
            LED6_PORT->BSRR = (uint32_t)LED6_PIN << 16;
            break;
        case ALL:
            LED1_PORT->BSRR = LED1_PIN;
            LED3_PORT->BSRR = (uint32_t)LED3_PIN << 16;
            LED6_PORT->BSRR = (uint32_t)LED6_PIN << 16;
            break;
    }
    
} 

void LED_Toggle(Led_TypeDef Led)
{
    uint8_t LED = (uint8_t)Led;
    switch(LED)
    {
        case LED1:
            LED1_PORT->ODR ^= LED1_PIN;
            break;
        case LED3:
            LED3_PORT->ODR ^= LED3_PIN;
            break;
        case LED6:
            LED6_PORT->ODR ^= LED6_PIN;
            break;
        case ALL:
            LED1_PORT->ODR ^= LED1_PIN;
            LED3_PORT->ODR ^= LED3_PIN;
            LED6_PORT->ODR ^= LED6_PIN;
            break;
    }
}

void BUTTON_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    __GPIOI_CLK_ENABLE();
    
    GPIO_InitStruct.Pin = BUTTON_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(BUTTON_PORT, &GPIO_InitStruct);
}

