#include "main.h"

/* Touch screen data structure */
TOUCH_t TS;

/* For string drawings */
char str[200];

/* Colors used for drawing for touch pressed */
uint16_t TOUCH_Colors[10] = {
	LCD_COLOR_BLACK,
	LCD_COLOR_BLUE,
	LCD_COLOR_RED,
	LCD_COLOR_GREEN,
	LCD_COLOR_YELLOW
};

int main(void) {
	uint8_t i;
	
	System_Init();
    LED_Init();
    Delay_Init();
	
	/* Init LCD */
	LCD_Init();
	
	/* Fill LCD with color */
	LCD_Fill(0xFFFF);
	
	/* Set custom orientation for LCD */
	LCD_SetOrientation(1);
	
	/* Get orientation from LCD and save to Touch Screen structure */
	TS.Orientation = LCD_GetOrientation();
	
	/* Init touch, use default drivers, depends on defines in library */
	/* Check library description for more information */
	TOUCH_Init(NULL, &TS);
    LCD_SetFont(&Font_11x18);

	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLUE);
    
	while (1)
    {
        /* Read touch */
        TOUCH_Read(&TS);

        /* Check if pressed */
        if (TS.NumPresses)
        {
            /* Go through all presses on LCD */
            for (i = 0; i < TS.NumPresses; i++)
            {
                /* Draw circle */
                LCD_DrawFilledCircle(TS.X[i], TS.Y[i], 5, TOUCH_Colors[i]);

                /* Format string */
                sprintf(str, "X: %3d Y: %3d", TS.X[i], TS.Y[i]);

                /* Print on LCD */
                LCD_SetXY(10, 10 + i * 20);
                LCD_Puts(str);
            }
        }
        delay_ms(5);
	}
}
