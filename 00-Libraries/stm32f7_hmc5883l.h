#ifndef __STM32F7_HMC5885L_H
#define __STM32F7_HMC5885L_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "stm32f7_i2c.h"
#include "stm32f7_gpio.h"
#include "stm32f7_exti.h"
#include <stdio.h>
	 
/**
 * @defgroup HMC5883L_Macros
 * @brief    Library defines
 * @{
 */

/**
 * @defgroup HMC5883L_I2C_DRDY
 * @brief    I2C and data ready settings
 * @{
 */

/* Default I2C for sensor */
#ifndef HMC5883L_I2C
#define HMC5883L_I2C            I2C3
#define HMC5883L_I2C_PINSPACK   I2C_PinsPack_1
#endif

/* I2C clock speed */
#ifndef HMC5883L_I2C_CLOCK
#define HMC5883L_I2C_CLOCK      400000
#endif

/* I2C address for HMC5883L */
#define HMC5883L_I2C_ADDR       0x3C

/* Data ready for HMC5883L */
#ifndef HMC5883L_DRDY_PIN
#define HMC5883L_DRDY_PORT      GPIOC
#define HMC5883L_DRDY_PIN       GPIO_PIN_3
#endif

/**
 * @}
 */
 
/**
 * @defgroup HMC5883L_Registers
 * @brief    Register settings for HMC5883L
 * @{
 */

#define HMC5883L_CONFA          0x00 /*!< Configuration Register A */
#define HMC5883L_CONFB          0x01 /*!< Configuration Register B */
#define HMC5883L_MODE           0x02 /*!< Mode Register */
#define HMC5883L_DATAXM         0x03 /*!< Data Output X MSB Register */
#define HMC5883L_DATAXL         0x04 /*!< Data Output X LSB Register */
#define HMC5883L_DATAZM         0x05 /*!< Data Output Z MSB Register */
#define HMC5883L_DATAZL         0x06 /*!< Data Output Z LSB Register */
#define HMC5883L_DATAYM         0x07 /*!< Data Output Y MSB Register */
#define HMC5883L_DATAYL         0x08 /*!< Data Output Y MSB Register */
#define HMC5883L_STATUS         0x09 /*!< Status register */
#define HMC5883L_IDA            0x0A /*!< Identification Register A */
#define HMC5883L_IDB            0x0B /*!< Identification Register B */
#define HMC5883L_IDC            0x0C /*!< Identification Register C */

/**
 * @}
 */
 
/**
 * @}
 */
 
/**
 * @defgroup HMC5883L_Typedefs
 * @brief    Library Typedefs
 * @{
 */

typedef enum {
	HMC5883L_Result_Ok = 0x00,
	HMC5883L_Result_Error,
	HMC5883L_Result_DeviceNotConnected
} HMC5883L_Result_t;

typedef enum {
	HMC5883L_Gain_0_88 = 0x00,
	HMC5883L_Gain_1_3 = 0x20,
	HMC5883L_Gain_1_9 = 0x40,
	HMC5883L_Gain_2_5 = 0x60,
	HMC5883L_Gain_4_0 = 0x80,
	HMC5883L_Gain_4_7 = 0xA0,
	HMC5883L_Gain_5_6 = 0xC0,
	HMC5883L_Gain_8_1 = 0xE0
} HMC5883L_Gain_t;

typedef enum {
	HMC5883L_OutputRate_0_75Hz = 0x00,
	HMC5883L_OutputRate_1_5Hz = 0x04,
	HMC5883L_OutputRate_3Hz = 0x08,
	HMC5883L_OutputRate_7_5Hz = 0x0C,
	HMC5883L_OutputRate_15Hz = 0x10,
	HMC5883L_OutputRate_30Hz = 0x14,
	HMC5883L_OutputRate_75Hz = 0x18
} HMC5883L_OutputRate_t;

typedef struct {
	uint8_t ID[3];
	float X;
	float Y;
	float Z;
} HMC5883L_t;

/**
 * @}
 */

/**
 * @defgroup HMC5883L_Functions
 * @brief    Library Functions
 * @{
 */

HMC5883L_Result_t HMC5883L_Init(HMC5883L_t* HMC5883L, HMC5883L_Gain_t Gain, HMC5883L_OutputRate_t OutputRate);

HMC5883L_Result_t HMC5883L_DataReady(HMC5883L_t* HMC5883L);

HMC5883L_Result_t HMC5883L_Read(HMC5883L_t* HMC5883L);

HMC5883L_Result_t HMC5883L_ProcessInterrupt(HMC5883L_t* HMC5883L);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_HMC5885L_H */

