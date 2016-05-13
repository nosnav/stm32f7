#ifndef __STM32F7_TOUCH_H
#define __STM32F7_TOUCH_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"

/**
 * @defgroup TOUCH_Macros
 * @brief    Library defines
 * @{
 */
/* Macros here */
/**
 * @}
 */
 
/**
 * @defgroup TOUCH_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  Touch working structure
 */
typedef struct {
	uint8_t NumPresses;   /*!< Number of touches (fingers) detected */
	uint16_t X[10];       /*!< X positions for touches */
	uint16_t Y[10];       /*!< Y positions for touches */
	uint8_t Events;       /*!< Events, if any. For example, touch has detected "zoom" with fingers or similar */
	uint8_t Orientation;  /*!< Touch orientation to match LCD orientation if needed */
	uint16_t MaxX;        /*!< Touch MAX X value. Maximal value for touch X coordinate */
	uint16_t MaxY;        /*!< Touch MAX Y value. Maximal value for touch Y coordinate */
} TOUCH_t;

/**
 * @brief  TOUCH Driver structure
 */
typedef struct {
	uint8_t (*Init)(TOUCH_t*); /*!< Pointer to init function for touch controller */
	uint8_t (*Read)(TOUCH_t*); /*!< Pointer to read function for touch controller */
} TOUCH_DRIVER_t;

/**
 * @brief  TOUCH result enumeration
 */
typedef enum {
	TOUCH_Result_Ok = 0x00, /*!< Everything OK */
	TOUCH_Result_Error      /*!< An error occurred */
} TOUCH_Result_t;

/**
 * @}
 */

/**
 * @defgroup TOUCH_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes touch controller 
 * @param  *Driver: Pointer to filled @ref TOUCH_DRIVER_t to be used for touch. Set parameter to NULL if you want to use default drivers which lib supports
 * @param  *TS: Pointer to empty @ref TOUCH_t structure
 * @retval Member of @ref TOUCH_Result_t enumeration
 */
TOUCH_Result_t TOUCH_Init(TOUCH_DRIVER_t* Driver, TOUCH_t* TS);

/**
 * @brief  Reads touch data from sensor 
 * @param  *TouchData: Poiter to @ref TOUCH_t structure where data will be stored
 * @retval Touch status:
 *            - 0: OK
 *            - > 0: Error
 */
uint8_t TOUCH_Read(TOUCH_t* TouchData);

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif
