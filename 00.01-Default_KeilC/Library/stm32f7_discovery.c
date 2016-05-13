#include "stm32f7_discovery.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    __GPIOI_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);
}

void LED_Off(void)
{
    LED_PORT->BSRR = (uint32_t)LED_PIN << 16;
}

void LED_On(void)
{
    GPIOA->BSRR = LED_PIN;
} 

void LED_Toggle(void)
{
    LED_PORT->ODR ^= LED_PIN;
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

