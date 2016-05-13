#ifndef __STM32F7_TOUCH_FT5336_H
#define __STM32F7_TOUCH_FT5336_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx.h"
#include "stm32f7_touch.h"
#include "stm32f7_i2c.h"
#include "stm32f7_gpio.h"

/**
 * @defgroup TOUCH_FT5336_Macros
 * @brief    Library defines
 * @{
 */

/* Touch I2C settings */
#ifndef TOUCH_FT5336_I2C
#define TOUCH_FT5336_I2C        I2C3
#define TOUCH_FT5336_I2C_PP     I2C_PinsPack_2
#endif

/* I2C device address */
#define TOUCH_FT5336_I2C_DEV    0x70

/**
 * @}
 */
 
/**
 * @defgroup TOUCH_FT5336_Typedefs
 * @brief    Library Typedefs
 * @{
 */
/* Typedefs here */
/**
 * @}
 */

/**
 * @defgroup TOUCH_FT5336_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes FT5336 touch controller
 * @param  *TS: Pointer to @ref TOUCH_t structure with settings
 * @retval Touch status:
 *            - 0: OK
 *            - > 0: Error
 */
uint8_t TOUCH_FT5336_Init(TOUCH_t* TS);

/**
 * @brief  Reads touch data from FT5336 touch controller
 * @param  *TS: Pointer to @ref TOUCH_t to save data into
 * @retval Touch status:
 *            - 0: OK
 *            - > 0: Error
 */
uint8_t TOUCH_FT5336_Read(TOUCH_t* TS);

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
