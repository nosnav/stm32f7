#include "stm32f7_usart_dma.h"

/* Private structure */
typedef struct {
	uint32_t DMA_Channel;
	DMA_Stream_TypeDef* DMA_Stream;
} USART_DMA_INT_t;

/* Create variables if necessary */
#ifdef USART1
static USART_DMA_INT_t USART1_DMA_INT = {USART1_DMA_TX_CHANNEL, USART1_DMA_TX_STREAM};
#endif
#ifdef USART2
static USART_DMA_INT_t USART2_DMA_INT = {USART2_DMA_TX_CHANNEL, USART2_DMA_TX_STREAM};
#endif
#ifdef USART3
static USART_DMA_INT_t USART3_DMA_INT = {USART3_DMA_TX_CHANNEL, USART3_DMA_TX_STREAM};
#endif
#ifdef UART4
static USART_DMA_INT_t UART4_DMA_INT = {UART4_DMA_TX_CHANNEL, UART4_DMA_TX_STREAM};
#endif
#ifdef UART5
static USART_DMA_INT_t UART5_DMA_INT = {UART5_DMA_TX_CHANNEL, UART5_DMA_TX_STREAM};
#endif
#ifdef USART6
static USART_DMA_INT_t USART6_DMA_INT = {USART6_DMA_TX_CHANNEL, USART6_DMA_TX_STREAM};
#endif
#ifdef UART7
static USART_DMA_INT_t UART7_DMA_INT = {UART7_DMA_TX_CHANNEL, UART7_DMA_TX_STREAM};
#endif
#ifdef UART8
static USART_DMA_INT_t UART8_DMA_INT = {UART8_DMA_TX_CHANNEL, UART8_DMA_TX_STREAM};
#endif

/* Private functions */
static USART_DMA_INT_t* USART_DMA_INT_GetSettings(USART_TypeDef* USARTx);

void USART_DMA_Init(USART_TypeDef* USARTx) {
	/* Init DMA TX mode */
	/* Assuming USART is already initialized and clock is enabled */
	
	/* Get USART settings */
	USART_DMA_INT_t* Settings = USART_DMA_INT_GetSettings(USARTx);
	
	/* Init stream */
	DMA_Init(Settings->DMA_Stream, NULL);
	
	/* Clear flags */
	DMA_ClearFlags(Settings->DMA_Stream);
	
	/* Disable stream */
	Settings->DMA_Stream->CR &= ~DMA_SxCR_EN;
	
	/* Reset NDTR register */
	Settings->DMA_Stream->NDTR = 0;
}

void USART_DMA_InitWithStreamAndChannel(USART_TypeDef* USARTx, DMA_Stream_TypeDef* DMA_Stream, uint32_t DMA_Channel) {
	/* Get USART settings */
	USART_DMA_INT_t* Settings = USART_DMA_INT_GetSettings(USARTx);
	
	/* Set DMA stream and channel */
	Settings->DMA_Stream = DMA_Stream;
	Settings->DMA_Channel = DMA_Channel;
	
	/* Init DMA TX */
	USART_DMA_Init(USARTx);
}

DMA_Stream_TypeDef* USART_DMA_GetStreamTX(USART_TypeDef* USARTx) {
	/* Get USART settings */
	return USART_DMA_INT_GetSettings(USARTx)->DMA_Stream;
}

void USART_DMA_Deinit(USART_TypeDef* USARTx) {
	DMA_HandleTypeDef DMA_InitStruct;
	
	/* Get USART settings */
	USART_DMA_INT_t* Settings = USART_DMA_INT_GetSettings(USARTx);
	
	/* Deinit DMA Stream */
	DMA_DeInit(Settings->DMA_Stream);
}

uint8_t USART_DMA_Send(USART_TypeDef* USARTx, uint8_t* DataArray, uint16_t count) {
	DMA_HandleTypeDef DMA_InitStruct;
	
	/* Get USART settings */
	USART_DMA_INT_t* Settings = USART_DMA_INT_GetSettings(USARTx);
	
	/* Check if DMA is working now */
	if (Settings->DMA_Stream->NDTR) {
		/* DMA works right now */
		return 0;
	}
	
	/* Set DMA options */
	DMA_InitStruct.Instance = Settings->DMA_Stream;
	DMA_InitStruct.Init.Channel = Settings->DMA_Channel;
	DMA_InitStruct.Init.Direction = DMA_MEMORY_TO_PERIPH;
	DMA_InitStruct.Init.PeriphInc = DMA_PINC_DISABLE;
	DMA_InitStruct.Init.MemInc = DMA_MINC_ENABLE;
	DMA_InitStruct.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	DMA_InitStruct.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	DMA_InitStruct.Init.Mode = DMA_NORMAL;
	DMA_InitStruct.Init.Priority = DMA_PRIORITY_LOW;
	DMA_InitStruct.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	DMA_InitStruct.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
	DMA_InitStruct.Init.MemBurst = DMA_MBURST_SINGLE;
	DMA_InitStruct.Init.PeriphBurst = DMA_PBURST_SINGLE;
	
	/* Deinit first, clear all flags */
	DMA_ClearFlags(Settings->DMA_Stream);
	
	/* Init HAL */
	DMA_Init(Settings->DMA_Stream, &DMA_InitStruct);
	
	/* Start transfer */
	DMA_Start(&DMA_InitStruct, (uint32_t) &DataArray[0], (uint32_t) &USART_TX_REG(USARTx), count);
	
	/* Enable USART TX DMA */
	USARTx->CR3 |= USART_CR3_DMAT;
	
	/* DMA has started */
	return 1;
}

uint8_t USART_DMA_Puts(USART_TypeDef* USARTx, char* DataArray) {
	/* Call DMA Send function */
	return USART_DMA_Send(USARTx, (uint8_t *)DataArray, strlen(DataArray));
}

uint16_t USART_DMA_Transmitting(USART_TypeDef* USARTx) {
	/* Get USART settings */
	USART_DMA_INT_t* Settings = USART_DMA_INT_GetSettings(USARTx);
	
	/* DMA has work to do still */
	if (Settings->DMA_Stream->NDTR) {
		return 1;
	}

	/* Check DMA Stream register of remaining data bytes */
	return !USART_TXEMPTY(USARTx);
}

void USART_DMA_EnableInterrupts(USART_TypeDef* USARTx) {
	/* Get USART settings */
	USART_DMA_INT_t* Settings = USART_DMA_INT_GetSettings(USARTx);
	
	/* Enable DMA interrupts */
	DMA_EnableInterrupts(Settings->DMA_Stream);
}

void USART_DMA_DisableInterrupts(USART_TypeDef* USARTx) {
	/* Get USART settings */
	USART_DMA_INT_t* Settings = USART_DMA_INT_GetSettings(USARTx);
	
	/* Disable DMA interrupts */
	DMA_DisableInterrupts(Settings->DMA_Stream);
}

/* Private functions */
static USART_DMA_INT_t* USART_DMA_INT_GetSettings(USART_TypeDef* USARTx) {
	USART_DMA_INT_t* result;
#ifdef USART1
	if (USARTx == USART1) {
		result = &USART1_DMA_INT;
	}
#endif
#ifdef USART2
	if (USARTx == USART2) {
		result = &USART2_DMA_INT;
	}
#endif
#ifdef USART3
	if (USARTx == USART3) {
		result = &USART3_DMA_INT;
	}
#endif
#ifdef UART4
	if (USARTx == UART4) {
		result = &UART4_DMA_INT;
	}
#endif
#ifdef UART5
	if (USARTx == UART5) {
		result = &UART5_DMA_INT;
	}
#endif
#ifdef USART6
	if (USARTx == USART6) {
		result = &USART6_DMA_INT;
	}
#endif
#ifdef UART7
	if (USARTx == UART7) {
		result = &UART7_DMA_INT;
	}
#endif
#ifdef UART8
	if (USARTx == UART8) {
		result = &UART8_DMA_INT;
	}
#endif

	/* Return */
	return result;
}