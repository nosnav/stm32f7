#ifndef __STM32F7_USART_DMA_H
#define __STM32F7_USART_DMA_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f7xx_hal.h"
#include "stm32f7_dma.h"
#include "stm32f7_usart.h"
#include "string.h"
     
/*     
USARTx     | DMA  | DMA Stream   | DMA Channel

USART1     | DMA2 | DMA Stream 7 | DMA Channel 4
USART2     | DMA1 | DMA Stream 6 | DMA Channel 4
USART3     | DMA1 | DMA Stream 3 | DMA Channel 4
UART4      | DMA1 | DMA Stream 4 | DMA Channel 4
UART5      | DMA1 | DMA Stream 7 | DMA Channel 4
USART6     | DMA2 | DMA Stream 6 | DMA Channel 5
UART7      | DMA1 | DMA Stream 1 | DMA Channel 5
UART8      | DMA1 | DMA Stream 0 | DMA Channel 5
 */


/**
 * @defgroup USART_DMA_Macros
 * @brief    Library defines
 * @{
 */

/* Default DMA Stream and Channel for USART1 */
#ifndef USART1_DMA_TX_STREAM
#define USART1_DMA_TX_STREAM      DMA2_Stream7
#define USART1_DMA_TX_CHANNEL     DMA_CHANNEL_4
#endif

/* Default DMA Stream and Channel for USART2 */
#ifndef USART2_DMA_TX_STREAM
#define USART2_DMA_TX_STREAM      DMA1_Stream6
#define USART2_DMA_TX_CHANNEL     DMA_CHANNEL_4
#endif

/* Default DMA Stream and Channel for USART3 */
#ifndef USART3_DMA_TX_STREAM
#define USART3_DMA_TX_STREAM      DMA1_Stream3
#define USART3_DMA_TX_CHANNEL     DMA_CHANNEL_4
#endif

/* Default DMA Stream and Channel for UART4 */
#ifndef UART4_DMA_TX_STREAM
#define UART4_DMA_TX_STREAM       DMA1_Stream4
#define UART4_DMA_TX_CHANNEL      DMA_CHANNEL_4
#endif

/* Default DMA Stream and Channel for UART5 */
#ifndef UART5_DMA_TX_STREAM
#define UART5_DMA_TX_STREAM       DMA1_Stream7
#define UART5_DMA_TX_CHANNEL      DMA_CHANNEL_4
#endif

/* Default DMA Stream and Channel for USART6 */
#ifndef USART6_DMA_TX_STREAM
#define USART6_DMA_TX_STREAM      DMA1_Stream6
#define USART6_DMA_TX_CHANNEL     DMA_CHANNEL_5
#endif

/* Default DMA Stream and Channel for UART7 */
#ifndef UART7_DMA_TX_STREAM
#define UART7_DMA_TX_STREAM       DMA1_Stream1
#define UART7_DMA_TX_CHANNEL      DMA_CHANNEL_5
#endif

/* Default DMA Stream and Channel for UART8 */
#ifndef UART8_DMA_TX_STREAM
#define UART8_DMA_TX_STREAM       DMA1_Stream0
#define UART8_DMA_TX_CHANNEL      DMA_CHANNEL_5
#endif

/**
 * @}
 */
 
/**
 * @defgroup USART_DMA_Typedefs
 * @brief    Library Typedefs
 * @{
 */
/* Typedefs here */
/**
 * @}
 */

/**
 * @defgroup USART_DMA_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes USART DMA TX functionality
 * @note   USART HAVE TO be previously initialized using @ref USART library
 * @param  *USARTx: Pointer to USARTx where you want to enable DMA TX mode
 * @retval None
 */
void USART_DMA_Init(USART_TypeDef* USARTx);

/**
 * @brief  Initializes USART DMA TX functionality with custom DMA stream and Channel options
 * @note   USART HAVE TO be previously initialized using @ref USART library
 *
 * @note   Use this function only in case default Stream and Channel settings are not good for you
 * @param  *USARTx: Pointer to USARTx where you want to enable DMA TX mode
 * @param  *DMA_Stream: Pointer to DMAy_Streamx, where y is DMA (1 or 2) and x is Stream (0 to 7)
 * @param  DMA_Channel: Select DMA channel for your USART in specific DMA Stream
 * @retval None
 */
void USART_DMA_InitWithStreamAndChannel(USART_TypeDef* USARTx, DMA_Stream_TypeDef* DMA_Stream, uint32_t DMA_Channel);

/**
 * @brief  Deinitializes USART DMA TX functionality
 * @param  *USARTx: Pointer to USARTx where you want to disable DMA TX mode
 * @retval None
 */
void USART_DMA_Deinit(USART_TypeDef* USARTx);

/**
 * @breif  Enables interrupts for DMA for USART streams
 * @note   USART DMA must be initialized first using @ref USART_DMA_Init() or @ref USART_DMA_InitWithStreamAndChannel() functions
 * @param  *USARTx: Pointer to USARTx where DMA interrupts will be enabled
 * @retval None
 */
void USART_DMA_EnableInterrupts(USART_TypeDef* USARTx);

/**
 * @breif  Disables interrupts for DMA for USART streams
 * @param  *USARTx: Pointer to USARTx where DMA interrupts will be disabled
 * @retval None
 */
void USART_DMA_DisableInterrupts(USART_TypeDef* USARTx);

/**
 * @brief  Gets poitner to DMA TX stream for desired USART 
 * @param  *USARTx: Pointer to USART where you wanna get its stream pointer
 * @retval Pointer to DMA stream for desired USART
 */
DMA_Stream_TypeDef* USART_DMA_GetStreamTX(USART_TypeDef* USARTx);

/**
 * @brief  Puts string to USART port with DMA
 * @note   Try not to use local variables pointers for DMA memory as parameter *str
 * @param  *USARTx: Pointer to USARTx peripheral you will use
 * @param  *str: Pointer to string to send over USART with DMA
 * @retval Sending started status:
 *            - 0: DMA has not started with sending data
 *            - > 0: DMA has started with sending data
 */
uint8_t USART_DMA_Puts(USART_TypeDef* USARTx, char* str);

/**
 * @brief  Sends data over USART with DMA TX functionality
 * @note   Try not to use local variables pointers for DMA memory as parameter *str
 * @param  *USARTx: Pointer to USARTx to use for send
 * @param  *DataArray: Pointer to array of data to be sent over USART
 * @param  count: Number of data bytes to be sent over USART with DMA
 * @retval Sending started status:
 *            - 0: DMA has not started with sending data
 *            - > 0: DMA has started with sending data
 */
uint8_t USART_DMA_Send(USART_TypeDef* USARTx, uint8_t* DataArray, uint16_t count);

/**
 * @brief  Checks if USART DMA TX is still sending data
 * @param  *USARTx: Pointer to USARTx where you want to check if DMA is still working
 * @retval Sending status:
 *            - 0: USART does not sending anymore
 *            - > 0: USART DMA is still sending data
 */
uint16_t USART_DMA_Transmitting(USART_TypeDef* USARTx);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F7_USART_DMA_H */

