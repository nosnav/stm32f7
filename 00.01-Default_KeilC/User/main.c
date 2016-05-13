#include "main.h"

int main(void)
{
    uint32_t time;
    System_Init();
    LED_Init();
    Delay_Init();
    while(1)
    {
        LED_Toggle();
        delay_ms(500);
    }
}
