#include "main.h"

int main(void)
{
    System_Init();
    LED_Init(ALL);
    Delay_Init();
    
    while(1)
    {
        LED_Toggle(ALL);
        delay_ms(500);
    }
}
