#include "stm32f7_button.h"


/* Button states */
#define BUTTON_STATE_START        0
#define BUTTON_STATE_DEBOUNCE     1
#define BUTTON_STATE_PRESSED      2
#define BUTTON_STATE_WAITRELEASE  3

/* Internal structure */
typedef struct {
	BUTTON_t* Buttons[BUTTON_MAX_BUTTONS];
	uint16_t ButtonsCount;
} BUTTON_INT_t;
static BUTTON_INT_t Buttons;

/* Internal functions */
static void BUTTON_INT_CheckButton(BUTTON_t* ButtonStruct);

static volatile uint8_t ButtonPressed = 0;

void Button_Init(void)
{
	/* Set pin as input */
	GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_Mode_IN, GPIO_OType_PP, BUTTON_PULL, GPIO_Speed_Low);
}

uint8_t Button_OnPressed(void) {
	/* If button is now pressed, but was not already pressed */
	if (Button_Pressed()) {
		if (!ButtonPressed) {
			/* Set flag */
			ButtonPressed = 1;
			
			/* Return button onpressed */
			return 1;
		}
	} else {
		/* Clear flag */
		ButtonPressed = 0;
	}
	
	/* Button is not pressed or it was already pressed before */
	return 0;
}

uint8_t Button_OnReleased(void) {
	/* If button is now released, but was not already released */
	if (!Button_Pressed()) {
		if (ButtonPressed) {
			/* Set flag */
			ButtonPressed = 0;
			
			/* Return button onreleased */
			return 1;
		}
	} else {
		/* Set flag */
		ButtonPressed = 1;
	}
	
	/* Button is not released or it was already released before */
	return 0;
}


BUTTON_t* BUTTON_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t ButtonState, void (*ButtonHandler)(BUTTON_t*, BUTTON_PressType_t)) {
	BUTTON_t* ButtonStruct;
	GPIO_PuPd_t P;
	
	/* Init delay function */
	//DELAY_Init();
	
	/* Check if available */
	if (Buttons.ButtonsCount >= BUTTON_MAX_BUTTONS) {
		return NULL;
	}
	
	/* Allocate memory for button */
	ButtonStruct = (BUTTON_t *) malloc(sizeof(BUTTON_t));
	
	/* Check if allocated */
	if (ButtonStruct == NULL) {
		return NULL;
	}
	
	/* Save settings */
	ButtonStruct->GPIOx = GPIOx;
	ButtonStruct->GPIO_Pin = GPIO_Pin;
	ButtonStruct->GPIO_State = ButtonState ? 1 : 0;
	ButtonStruct->ButtonHandler = ButtonHandler;
	ButtonStruct->State = BUTTON_STATE_START;
	
	/* Set default values */
	ButtonStruct->PressNormalTime = BUTTON_NORMAL_PRESS_TIME;
	ButtonStruct->PressLongTime = BUTTON_LONG_PRESS_TIME;
	ButtonStruct->PressDebounceTime = BUTTON_DEBOUNCE_TIME;
	
	/* Init pin with pull resistor */
	if (ButtonStruct->GPIO_State) {
		/* Pulldown */
		P = GPIO_PuPd_DOWN;
	} else {
		/* Pullup */
		P = GPIO_PuPd_UP;
	}
	
	/* Init GPIO pin as input with proper pull resistor */
	GPIO_Init(GPIOx, GPIO_Pin, GPIO_Mode_IN, GPIO_OType_PP, P, GPIO_Speed_Low);
	
	/* Save button */
	Buttons.Buttons[Buttons.ButtonsCount++] = ButtonStruct;
	
	/* Return button pointer */
	return ButtonStruct;
}

BUTTON_t* BUTTON_SetPressTime(BUTTON_t* ButtonStruct, uint16_t Normal, uint16_t Long) {
	/* Set values */
	ButtonStruct->PressNormalTime = Normal;
	ButtonStruct->PressLongTime = Long;
	
	/* Return pointer */
	return ButtonStruct;
}

void BUTTON_Update(void) {
	uint16_t i;
	
	/* Go through all buttons */
	for (i = 0; i < Buttons.ButtonsCount; i++) {
		/* Check button */
		BUTTON_INT_CheckButton(Buttons.Buttons[i]);
	}
}

/* Internal functions */
static void BUTTON_INT_CheckButton(BUTTON_t* ButtonStruct) {
	uint32_t now, status;
	
	/* Read values */
	now = millis();
	status = GPIO_GetInputPinValue(ButtonStruct->GPIOx, ButtonStruct->GPIO_Pin);
	
	/* First stage */
	if (ButtonStruct->State == BUTTON_STATE_START) {
		/* Check if pressed */
		if (status == ButtonStruct->GPIO_State) {
			/* Button pressed, go to stage BUTTON_STATE_START */
			ButtonStruct->State = BUTTON_STATE_DEBOUNCE;
			
			/* Save pressed time */
			ButtonStruct->StartTime = now;
		}
	}

	if (ButtonStruct->State == BUTTON_STATE_DEBOUNCE) {
		/* Button still pressed */
		/* Check for debounce */
		if (status == ButtonStruct->GPIO_State) {
			if ((now - ButtonStruct->StartTime) > ButtonStruct->PressDebounceTime) {
				/* Button debounce OK, Goto Normal Press */
				ButtonStruct->State = BUTTON_STATE_PRESSED;

				/* Try to call user function */
				if (ButtonStruct->ButtonHandler) {
					/* Call function callback */
					ButtonStruct->ButtonHandler(ButtonStruct, BUTTON_PressType_OnPressed);
				}
			}
		} else if (status != ButtonStruct->GPIO_State) {
			/* Not pressed */
			/* It was bounce, start over */
			/* Go to state BUTTON_STATE_START */
			ButtonStruct->State = BUTTON_STATE_START;
		}
	}
	
	if (ButtonStruct->State == BUTTON_STATE_PRESSED) {
		/* Button still pressed */
		/* Check for long press */
		if (status == ButtonStruct->GPIO_State) {
			if ((now - ButtonStruct->StartTime) > ButtonStruct->PressLongTime) {
				/* Button pressed OK, call function */
				if (ButtonStruct->ButtonHandler) {
					/* Call function callback */
					ButtonStruct->ButtonHandler(ButtonStruct, BUTTON_PressType_Long);
				}
				
				/* Go to stage BUTTON_STATE_WAITRELEASE */
				ButtonStruct->State = BUTTON_STATE_WAITRELEASE;
			}
		} else if (status != ButtonStruct->GPIO_State) {
			/* Not pressed */
			if ((now - ButtonStruct->StartTime) > ButtonStruct->PressNormalTime) {
				/* Button pressed OK, call function */
				if (ButtonStruct->ButtonHandler) {
					/* Call function callback */
					ButtonStruct->ButtonHandler(ButtonStruct, BUTTON_PressType_Normal);
				}
				
				/* Go to stage BUTTON_STATE_WAITRELEASE */
				ButtonStruct->State = BUTTON_STATE_WAITRELEASE;
			} else {
				/* Go to state BUTTON_STATE_START */
				ButtonStruct->State = BUTTON_STATE_START;
			}
		} else {
			/* Go to state BUTTON_STATE_START */
			ButtonStruct->State = BUTTON_STATE_START;
		}
	}
	
	if (ButtonStruct->State == BUTTON_STATE_WAITRELEASE) {
		/* Wait till button released */
		if (status != ButtonStruct->GPIO_State) {
			/* Go to stage 0 again */
			ButtonStruct->State = BUTTON_STATE_START;
		}
	}
	
	/* Save current status */
	ButtonStruct->LastStatus = status;
}
