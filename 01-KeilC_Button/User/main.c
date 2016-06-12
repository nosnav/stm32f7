#include "main.h"

BUTTON_t* Button;

/* Button callback function */
static void BUTTON_Callback(BUTTON_t* ButtonPtr, BUTTON_PressType_t PressType);

int main(void)
{
    System_Init();
    LED_Init(ALL);
    Delay_Init();
    Button = BUTTON_Init(BUTTON_PORT, BUTTON_PIN, BUTTON_PRESSED, BUTTON_Callback);
    
    /* Set time how button is detected, 30 ms for normal press, 1000 ms for long press */
	BUTTON_SetPressTime(Button, 30, 1000);
    
    while(1)
    {
        /* Update all buttons */
		BUTTON_Update();
    }
}

/* Implement handler function */
static void BUTTON_Callback(BUTTON_t* ButtonPtr, BUTTON_PressType_t PressType)
{
	/* Normal press detected */
	if (PressType == BUTTON_PressType_Normal)
    {
		/* Set LEDS ON */
		LED_On(ALL);
	}
    else if (PressType == BUTTON_PressType_Long)
    {
		/* Set LEDS OFF */
		LED_Off(ALL);
	}
}
