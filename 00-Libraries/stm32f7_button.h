#ifndef __STM32F7_BUTTON_H
#define __STM32F7_BUTTON_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdlib.h>
#include "stm32f7xx_hal.h"
#include "stm32f7_gpio.h"
#include "stm32f7_delay.h"

#define BUTTON_PORT			GPIOI
#define BUTTON_PIN			0x0800
#define BUTTON_PRESSED		1
#define BUTTON_PULL			GPIO_PuPd_DOWN
     
/* Number of maximal supported buttons */
#ifndef BUTTON_MAX_BUTTONS
#define BUTTON_MAX_BUTTONS        10
#endif

/* Time for debounce */
#ifndef BUTTON_DEBOUNCE_TIME
#define BUTTON_DEBOUNCE_TIME      5
#endif

/* Number of milliseconds for normal press detection */
#ifndef BUTTON_NORMAL_PRESS_TIME
#define BUTTON_NORMAL_PRESS_TIME  100
#endif

/* Number of milliseconds for long press detection */
#ifndef BUTTON_LONG_PRESS_TIME
#define BUTTON_LONG_PRESS_TIME    1500
#endif

/* Library allocation function */
#ifndef LIB_ALLOC_FUNC
#define LIB_ALLOC_FUNC            malloc
#endif

/* Library free function */
#ifndef LIB_FREE_FUNC
#define LIB_FREE_FUNC             free
#endif

/**
 * @}
 */
 
/**
 * @defgroup BUTTON_Typedefs
 * @brief    Library Typedefs
 * @{
 */
 
/**
 * @brief  Button possible press types
 */
typedef enum {
  BUTTON_PressType_OnPressed = 0x00, /*!< Button pressed */
  BUTTON_PressType_Debounce,         /*!< Button debounce */
	BUTTON_PressType_Normal,           /*!< Normal press type, released */
	BUTTON_PressType_Long              /*!< Long press type */
} BUTTON_PressType_t;

/** 
 * @brief  Button structure 
 */
typedef struct _BUTTON_t {
	GPIO_TypeDef* GPIOx;                                                /*!< GPIOx PORT for button */
	uint16_t GPIO_Pin;                                                  /*!< GPIO pin for button */
	uint8_t GPIO_State;                                                 /*!< GPIO state for pin when pressed */
	void (*ButtonHandler)(struct _BUTTON_t*, BUTTON_PressType_t); /*!< Button function handler */
	uint32_t StartTime;                                                 /*!< Time when button was pressed */
	uint8_t LastStatus;                                                 /*!< Button status on last check */
	uint8_t State;                                                      /*!< Current button state */
	uint16_t PressDebounceTime;                                         /*!< Time in ms for normal press for button */
	uint16_t PressNormalTime;                                           /*!< Time in ms for normal press for button */
	uint16_t PressLongTime;                                             /*!< Time in ms for long press for button */
} BUTTON_t;

/**
 * @}
 */

/**
 * @defgroup BUTTON_Functions
 * @brief    Library Functions
 * @{
 */
/**
 * @brief  Configures Button pin as input
 * @param  None
 * @retval None
 */
void Button_Init(void);
/**
 * @brief  Checks if user button is pressed
 * @param  None
 * @retval Button status
 *            - 0: Button is not pressed
 *            - > 0: Button is pressed
 */
#define Button_Pressed()       ((GPIO_GetInputPinValue(BUTTON_PORT, BUTTON_PIN) == 0) != BUTTON_PRESSED)

/**
 * @brief  Checks if button was pressed now, but was not already pressed before
 * @param  None
 * @retval Button on pressed value
 *           - 0: In case that button has been already pressed on last call or was not pressed at all yet
 *           - > 0: Button was pressed, but state before was released
 */
uint8_t Button_OnPressed(void);

/**
 * @brief  Checks if button was released now, but was already pressed before
 * @param  None
 * @retval Button on released value
 *           - 0: In case that button has been already released on last call or was not released at all yet
 *           - > 0: Button was released, but state before was pressed
 */
uint8_t Button_OnReleased(void);
/**
 * @brief  Initializes a new button to library
 * @note   This library uses @ref malloc() to allocate memory, so make sure you have enough heap memory
 * @param  *GPIOx: Pointer to GPIOx where button is located
 * @param  GPIO_Pin: GPIO pin where button is located
 * @param  ButtonState: Button state when it is pressed.
 *            - 0: Button is low when pressed
 *            - > 0: Button is high when pressed
 * @param  *ButtonHandler:
 * @retval Button creation status:
 *            - 0: Button was not created 
 *            - > 0: Button created and saved to library, button pointer is returned
 */
BUTTON_t* BUTTON_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, uint8_t ButtonState, void (*ButtonHandler)(BUTTON_t*, BUTTON_PressType_t));

/**
 * @brief  Sets press timing values
 * @param  *ButtonStruct: Pointer to @ref BUTTON_t structure for button used
 * @param  Normal: Time that button must be pressed to indicate normal press. Value is in milliseconds
 * @param  Normal: Time that button must be pressed to indicate long press. Value is in milliseconds
 * @retval Pointer to @ref BUTTON_t
 */
BUTTON_t* BUTTON_SetPressTime(BUTTON_t* ButtonStruct, uint16_t Normal, uint16_t Long);

/**
 * @brief  Updates buttons. This function have to be called periodically
 * @note   Function will automatically call callback functions for buttons if needed
 * @param  None
 * @retval None
 */
void BUTTON_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_BUTTON_H */

