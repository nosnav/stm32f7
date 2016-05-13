#ifndef __STM32F7_SPI_H
#define __STM32F7_SPI_H

/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup STM32Fxxx_HAL_Libraries
 * @{
 */

/**
 * @defgroup SPI
 * @brief    SPI library for STM32Fxxx - http://stm32f4-discovery.com/2015/07/hal-library-08-spi-for-stm32fxxx/
 * @{
 *
 * It supports all 6 SPIs in master with 3 Lines Full Duplex mode
 *
 * \par Default SPI settings
 *
 * All six SPIs work the same principle by default:
 *	- Master mode
 *	- 8 data bits
 *	- Clock polarity low, data sampled at first edge, SPI mode 0
 *	- Prescaler set to 32
 *	- Firstbit MSB
 *	- Software SS pin configure
 *	- Direction is full duplex 3 wires
 *	
 *	\par Pinout
 *
\verbatim
        |PINS PACK 1            |PINS PACK 2            |PINS PACK 3           |PINS PACK 4
SPIX    |MOSI   MISO    SCK     |MOSI   MISO    SCK     |MOSI   MISO    SCK    |MOSI   MISO    SCK
        |                                                                           
SPI1    |PA7    PA6     PA5     |PB5    PB4     PB3     |                      |
SPI2    |PC3    PC2     PB10    |PB15   PB14    PB13    |PI3    PI2     PI0    |PB15   PB14    PI1
SPI3    |PB5    PB4     PB3     |PC12   PC11    PC10    |                      |
SPI4    |PE6    PE5     PE2     |PE14   PE13    PE12    |                      |
SPI5    |PF9    PF8     PF7     |PF11   PH7     PH6     |                      |
SPI6    |PG14   PG12    PG13    |
\endverbatim
 *
 * In case these pins are not good for you, you can use
 * SPI_PinsPack_Custom in function and callback function will be called,
 * where you can initialize your custom pinout for your SPI peripheral
 *	
 * Possible changes to each SPI. Set this defines in your defines.h file.
 *	
 * Change x with 1-6, to match your SPI
 *
\code
//Default prescaler
#define SPIx_PRESCALER   SPI_BAUDRATEPRESCALER_32
//Specify datasize
#define SPIx_DATASIZE    SPI_DATASIZE_8BIT
//Specify which bit is first
#define SPIx_FIRSTBIT    SPI_FIRSTBIT_MSB
//Mode, master or slave
#define SPIx_MASTERSLAVE SPI_MODE_MASTER
//Specify mode of operation, clock polarity and clock phase
#define SPIx_MODE        SPI_Mode_0
\endcode
 *
 * \par Changelog
 *
\verbatim
 Version 1.0
  - First release
\endverbatim
 *
 * \par Dependencies
 *
\verbatim
 - STM32Fxxx HAL
 - defines.h
 - attributes.h
 - TM GPIO
\endverbatim
 */

#include "stm32fxxx_hal.h"
#include "defines.h"
#include "attributes.h"
#include "stm32f7_gpio.h"

/**
 * @defgroup SPI_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  SPI modes selection
 */
typedef enum {
	SPI_Mode_0 = 0x00, /*!< Clock polarity low, clock phase 1st edge */
	SPI_Mode_1,        /*!< Clock polarity low, clock phase 2nd edge */
	SPI_Mode_2,        /*!< Clock polarity high, clock phase 1st edge */
	SPI_Mode_3         /*!< Clock polarity high, clock phase 2nd edge */
} SPI_Mode_t;

/**
 * @brief  SPI PinsPack enumeration to select pins combination for SPI
 */
typedef enum {
	SPI_PinsPack_1 = 0x00, /*!< Select PinsPack1 from Pinout table for specific SPI */
	SPI_PinsPack_2,        /*!< Select PinsPack2 from Pinout table for specific SPI */
	SPI_PinsPack_3,        /*!< Select PinsPack3 from Pinout table for specific SPI */
	SPI_PinsPack_4,        /*!< Select PinsPack4 from Pinout table for specific SPI */
	SPI_PinsPack_Custom    /*!< Select custom pins for specific SPI, callback will be called, look @ref SPI_InitCustomPinsCallback */
} SPI_PinsPack_t;

/**
 * @brief  Daza size enumeration
 */
typedef enum {
	SPI_DataSize_8b = 0x00, /*!< SPI in 8-bits mode */
	SPI_DataSize_16b        /*!< SPI in 16-bits mode */        
} SPI_DataSize_t;

/**
 * @}
 */
 
 /**
 * @defgroup SPI_Macros
 * @brief    Library defines
 * @{
 */

//----- SPI1 options start -------
//Options can be overwriten in defines.h file
#ifndef SPI1_PRESCALER
#define SPI1_PRESCALER	SPI_BAUDRATEPRESCALER_32
#endif
//Specify datasize
#ifndef SPI1_DATASIZE
#define SPI1_DATASIZE 	SPI_DATASIZE_8BIT
#endif
//Specify which bit is first
#ifndef SPI1_FIRSTBIT
#define SPI1_FIRSTBIT 	SPI_FIRSTBIT_MSB
#endif
//Mode, master or slave
#ifndef SPI1_MASTERSLAVE
#define SPI1_MASTERSLAVE	SPI_MODE_MASTER
#endif
//Specify mode of operation, clock polarity and clock phase
#ifndef SPI1_MODE
#define SPI1_MODE		SPI_Mode_0
#endif
//----- SPI1 options end -------

//----- SPI2 options start -------
//Options can be overwriten in defines.h file
#ifndef SPI2_PRESCALER
#define SPI2_PRESCALER	SPI_BAUDRATEPRESCALER_32
#endif
//Specify datasize
#ifndef SPI2_DATASIZE
#define SPI2_DATASIZE 	SPI_DATASIZE_8BIT
#endif
//Specify which bit is first
#ifndef SPI2_FIRSTBIT
#define SPI2_FIRSTBIT 	SPI_FIRSTBIT_MSB
#endif
//Mode, master or slave
#ifndef SPI2_MASTERSLAVE
#define SPI2_MASTERSLAVE SPI_MODE_MASTER
#endif
//Specify mode of operation, clock polarity and clock phase
#ifndef SPI2_MODE
#define SPI2_MODE		SPI_Mode_0
#endif
//----- SPI2 options end -------

//----- SPI3 options start -------
//Options can be overwriten in defines.h file
#ifndef SPI3_PRESCALER
#define SPI3_PRESCALER	SPI_BAUDRATEPRESCALER_32
#endif
//Specify datasize
#ifndef SPI3_DATASIZE
#define SPI3_DATASIZE 	SPI_DATASIZE_8BIT
#endif
//Specify which bit is first
#ifndef SPI3_FIRSTBIT
#define SPI3_FIRSTBIT 	SPI_FIRSTBIT_MSB
#endif
//Mode, master or slave
#ifndef SPI3_MASTERSLAVE
#define SPI3_MASTERSLAVE SPI_MODE_MASTER
#endif
//Specify mode of operation, clock polarity and clock phase
#ifndef SPI3_MODE
#define SPI3_MODE		SPI_Mode_0
#endif
//----- SPI3 options end -------

//----- SPI4 options start -------
//Options can be overwriten in defines.h file
#ifndef SPI4_PRESCALER
#define SPI4_PRESCALER	SPI_BAUDRATEPRESCALER_32
#endif
//Specify datasize
#ifndef SPI4_DATASIZE
#define SPI4_DATASIZE 	SPI_DATASIZE_8BIT
#endif
//Specify which bit is first
#ifndef SPI4_FIRSTBIT
#define SPI4_FIRSTBIT 	SPI_FIRSTBIT_MSB
#endif
//Mode, master or slave
#ifndef SPI4_MASTERSLAVE
#define SPI4_MASTERSLAVE	SPI_MODE_MASTER
#endif
//Specify mode of operation, clock polarity and clock phase
#ifndef SPI4_MODE
#define SPI4_MODE		SPI_Mode_0
#endif
//----- SPI4 options end -------

//----- SPI5 options start -------
//Options can be overwriten in defines.h file
#ifndef SPI5_PRESCALER
#define SPI5_PRESCALER	SPI_BAUDRATEPRESCALER_32
#endif
//Specify datasize
#ifndef SPI5_DATASIZE
#define SPI5_DATASIZE 	SPI_DATASIZE_8BIT
#endif
//Specify which bit is first
#ifndef SPI5_FIRSTBIT
#define SPI5_FIRSTBIT 	SPI_FIRSTBIT_MSB
#endif
//Mode, master or slave
#ifndef SPI5_MASTERSLAVE
#define SPI5_MASTERSLAVE SPI_MODE_MASTER
#endif
//Specify mode of operation, clock polarity and clock phase
#ifndef SPI5_MODE
#define SPI5_MODE		SPI_Mode_0
#endif
//----- SPI5 options end -------

//----- SPI6 options start -------
//Options can be overwriten in defines.h file
#ifndef SPI6_PRESCALER
#define SPI6_PRESCALER	SPI_BAUDRATEPRESCALER_32
#endif
//Specify datasize
#ifndef SPI6_DATASIZE
#define SPI6_DATASIZE 	SPI_DATASIZE_8BIT
#endif
//Specify which bit is first
#ifndef SPI6_FIRSTBIT
#define SPI6_FIRSTBIT 	SPI_FIRSTBIT_MSB
#endif
//Mode, master or slave
#ifndef SPI6_MASTERSLAVE
#define SPI6_MASTERSLAVE SPI_MODE_MASTER
#endif
//Specify mode of operation, clock polarity and clock phase
#ifndef SPI6_MODE
#define SPI6_MODE		SPI_Mode_0
#endif
//----- SPI6 options end -------

/**
 * @brief  Check SPI busy status
 */
#define SPI_IS_BUSY(SPIx)                   (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0)

/**
 * @brief  SPI wait till end
 */
#define SPI_WAIT_TX(SPIx)                   while ((SPIx->SR & SPI_FLAG_TXE) == 0 || (SPIx->SR & SPI_FLAG_BSY))
#define SPI_WAIT_RX(SPIx)                   while ((SPIx->SR & SPI_FLAG_RXNE) == 0 || (SPIx->SR & SPI_FLAG_BSY))

/**
 * @brief  Checks if SPI is enabled
 */
#define SPI_CHECK_ENABLED(SPIx)             if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return;}

/**
 * @brief  Checks if SPI is enabled and returns value from function if not 
 */
#define SPI_CHECK_ENABLED_RESP(SPIx, val)   if (!((SPIx)->CR1 & SPI_CR1_SPE)) {return (val);}

/**
 * @}
 */

/**
 * @defgroup SPI_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes SPIx peripheral with custom pinspack and default other settings
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  pinspack: Pinspack you will use from default SPI table. This parameter can be a value of @ref SPI_PinsPack_t enumeration
 * @retval None
 */
void SPI_Init(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack);

/**
 * @brief  Initializes SPIx peripheral with custom pinspack and SPI mode and default other settings
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  pinspack: Pinspack you will use from default SPI table. This parameter can be a value of @ref SPI_PinsPack_t enumeration
 * @param  SPI_Mode: SPI mode you will use. This parameter can be a value of @ref SPI_Mode_t enumeration
 * @retval None
 */
void SPI_InitWithMode(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, SPI_Mode_t SPI_Mode);

/**
 * @brief  Initializes SPIx peripheral with custom settings
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  pinspack: Pinspack you will use from default SPI table. This parameter can be a value of @ref SPI_PinsPack_t enumeration
 * @param  SPI_BaudRatePrescaler: SPI baudrate prescaler. This parameter can be a value of @ref SPI_BaudRatePrescaler
 * @param  SPI_Mode_t: SPI mode you will use. This parameter can be a value of @ref SPI_Mode_t enumeration
 * @param  SPI_Mode: SPI mode you will use:
 *            - SPI_MODE_MASTER: SPI in master mode (default)
 *            - SPI_MODE_SLAVE: SPI in slave mode
 * @param  SPI_FirstBit: select first bit for SPI
 *            - SPI_FIRSTBIT_MSB: MSB is first bit (default)
 *            - SPI_FIRSTBIT_LSB: LSB is first bit
 * @retval None
 */
void SPI_InitFull(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, uint16_t SPI_BaudRatePrescaler, SPI_Mode_t SPI_Mode_t, uint16_t SPI_Mode, uint16_t SPI_FirstBit);

/**
 * @brief  Calculates bits for SPI prescaler register to get minimal prescaler value for SPI peripheral
 * @note   SPI has 8 prescalers available, 2,4,8,...,128,256
 * @note   This function will return you a bits you must set in your CR1 register.
 *
 * @note   Imagine, you can use 20MHz max clock in your system, your system is running on 168MHz, and you use SPI on APB2 bus.
 *         On 168 and 180MHz devices, APB2 works on Fclk/2, so 84 and 90MHz.
 *         So, if you calculate this, prescaler will need to be 84MHz / 20MHz = 4.xx, but if you use 4 prescaler, then you will be over 20MHz.
 *         You need 8 prescaler then. This function will calculate this.
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6.
 *            Different SPIx works on different clock and is important to know for which SPI you need prescaler.
 * @param  MAX_SPI_Frequency: Max SPI frequency you can use. Function will calculate the minimum prescaler you need for that.
 *
 * @retval Bits combination for SPI_CR1 register, with aligned location already, prepared to set parameter for @ref SPI_InitFull() function.
 */
uint16_t SPI_GetPrescalerFromMaxFrequency(SPI_TypeDef* SPIx, uint32_t MAX_SPI_Frequency);

/**
 * @brief  Sets data size for SPI at runtime
 * @note   You can select either 8 or 16 bits data array. 
 * @param  *SPIx: Pointer to SPIx peripheral where data size will be set
 * @param  DataSize: Datasize which will be used. This parameter can be a value of @ref SPI_DataSize_t enumeration
 * @retval Status of data size before changes happen
 */
SPI_DataSize_t SPI_SetDataSize(SPI_TypeDef* SPIx, SPI_DataSize_t DataSize);

/**
 * @brief  Sends single byte over SPI
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  data: 8-bit data size to send over SPI
 * @retval Received byte from slave device
 */
static __INLINE uint8_t SPI_Send(SPI_TypeDef* SPIx, uint8_t data) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED_RESP(SPIx, 0);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT_TX(SPIx);
	
	/* Fill output buffer with data */
	SPIx->DR = data;
	
	/* Wait for transmission to complete */
	SPI_WAIT_RX(SPIx);
	
	/* Return data from buffer */
	return SPIx->DR;
}

/**
 * @brief  Sends and receives multiple bytes over SPIx
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  *dataOut: Pointer to array with data to send over SPI
 * @param  *dataIn: Pointer to array to to save incoming data
 * @param  count: Number of bytes to send/receive over SPI
 * @retval None
 */
void SPI_SendMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint8_t* dataIn, uint32_t count);

/**
 * @brief  Writes multiple bytes over SPI
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  *dataOut: Pointer to array with data to send over SPI
 * @param  count: Number of elements to send over SPI
 * @retval None
 */
void SPI_WriteMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint32_t count);

/**
 * @brief  Receives multiple data bytes over SPI
 * @note   Selected SPI must be set in 16-bit mode
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  *dataIn: Pointer to 8-bit array to save data into
 * @param  dummy: Dummy byte  to be sent over SPI, to receive data back. In most cases 0x00 or 0xFF
 * @param  count: Number of bytes you want read from device
 * @retval None
 */
void SPI_ReadMulti(SPI_TypeDef* SPIx, uint8_t *dataIn, uint8_t dummy, uint32_t count);

/**
 * @brief  Sends single byte over SPI
 * @note   Selected SPI must be set in 16-bit mode
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  data: 16-bit data size to send over SPI
 * @retval Received 16-bit value from slave device
 */
static __INLINE uint16_t SPI_Send16(SPI_TypeDef* SPIx, uint8_t data) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED_RESP(SPIx, 0);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT_TX(SPIx);
	
	/* Fill output buffer with data */
	SPIx->DR = data;
	
	/* Wait for transmission to complete */
	SPI_WAIT_RX(SPIx);
	
	/* Return data from buffer */
	return SPIx->DR;
}

/**
 * @brief  Sends and receives multiple bytes over SPIx in 16-bit SPI mode
 * @note   Selected SPI must be set in 16-bit mode
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  *dataOut: Pointer to array with data to send over SPI
 * @param  *dataIn: Pointer to array to to save incoming data
 * @param  count: Number of 16-bit values to send/receive over SPI
 * @retval None
 */
void SPI_SendMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint16_t* dataIn, uint32_t count);

/**
 * @brief  Writes multiple data via SPI in 16-bit SPI mode
 * @note   Selected SPI must be set in 16-bit mode
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  *dataOut: Pointer to 16-bit array with data to send over SPI
 * @param  count: Number of elements to send over SPI
 * @retval None
 */
void SPI_WriteMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint32_t count);

/**
 * @brief  Receives multiple data bytes over SPI in 16-bit SPI mode
 * @note   Selected SPI must be set in 16-bit mode
 * @param  *SPIx: Pointer to SPIx peripheral you will use, where x is between 1 to 6
 * @param  *dataIn: Pointer to 16-bit array to save data into
 * @param  dummy: Dummy 16-bit value to be sent over SPI, to receive data back. In most cases 0x00 or 0xFF
 * @param  count: Number of 16-bit values you want read from device
 * @retval None
 */
void SPI_ReadMulti16(SPI_TypeDef* SPIx, uint16_t* dataIn, uint16_t dummy, uint32_t count);

/**
 * @brief  Init custom SPI pins for your SPIx. This is callback function and will be called from my library if needed.
 * @note   When you call SPI_Init() function, and if you pass SPI_PinsPack_Custom to function,
 *         then this function will be called where you can initialize custom pins for SPI peripheral
 *
 * @note   You have to initialize MOSI, MISO and SCK pin
 *
 * @param  *SPIx: Pointer to SPIx peripheral for which you have to set your custom pin settings
 * @param  AlternateFunction: Alternate function number which should be used for GPIO pins
 * @retval None
 * @note   With __weak parameter to prevent link errors if not defined by user
 */
void SPI_InitCustomPinsCallback(SPI_TypeDef* SPIx, uint16_t AlternateFunction);

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

