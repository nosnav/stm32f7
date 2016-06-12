#include "main.h"

int main(void)
{
    System_Init();
    LED_Init(ALL);
    Delay_Init();
	
    /* Attach EXTI pin, enable both edges because of different boards support */
	if (EXTI_Attach(BUTTON_PORT, BUTTON_PIN, EXTI_Trigger_Rising_Falling) == EXTI_Result_Ok)
	{
		/* Turn on green LED */
		LED_On(LED1);
	}
	else
	{
		/* Turn on RED led */
		LED_On(LED3);
	}
	
    while(1)
    {
    }
}

/* Handle all EXTI lines */
void EXTI_Handler(uint16_t GPIO_Pin)
{
	/* Check proper line */
	if (GPIO_Pin == BUTTON_PIN)
	{
		/* Toggle pin only if button is pressed */
		if (Button_Pressed())
		{
			/* Toggle LEDs if interrupt on button line happens */
			LED_Toggle(ALL);
		}
	}
}
