#include "main.h"

#define USART   USART1
char USART_Buffer[100] = "\r\nHello via USART1 with TX DMA";

int main(void)
{
    System_Init();
    LED_Init(ALL);
    Delay_Init();
    /* Init USART, Pins not initialized yet, 256000 bauds */
	USART_Init(USART, USART_PinsPack_Custom, 256000);
	
	/* Say string without DMA */
	USART_Puts(USART, "\r\nHello via USART without DMA");
	
	/* Init TX DMA for USART */
	USART_DMA_Init(USART);
	
	/* Enable interrupts for TX DMA */
	USART_DMA_EnableInterrupts(USART);
	
	/* Send data with DMA */
	USART_DMA_Send(USART, (uint8_t *)USART_Buffer, strlen(USART_Buffer));
	
	/* Wait till DMA works */
	/* You can do other stuff here instead of waiting for DMA to end */
	while (USART_DMA_Transmitting(USART));
	
	while (1)
    {
		/* If any string arrived over USART */
		/* Expecting "\n" at the end of string from USART terminal or any other source */
		if (USART_Gets(USART, USART_Buffer, sizeof(USART_Buffer)))
        {
			/* Send it back over DMA */
			USART_DMA_Send(USART, (uint8_t *)USART_Buffer, strlen(USART_Buffer));

			/* Wait till DMA works */
			/* You can do other stuff here instead of waiting for DMA to end */
			while (USART_DMA_Transmitting(USART));
		}
	}
}

/* USART Custom pins callback function */
void USART_InitCustomPinsCallback(USART_TypeDef* USARTx, uint16_t AlternateFunction) { 
	/* Check for proper USART */
	if (USARTx == USART) {
		/* Init pins for USART 6 */
		GPIO_InitAlternate(GPIOA, GPIO_PIN_9, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Fast, AlternateFunction);
        GPIO_InitAlternate(GPIOB, GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Fast, AlternateFunction);
    }
}

/* DMA transfer complete callback */
void DMA_TransferCompleteHandler(DMA_Stream_TypeDef* DMA_Stream)
{
	/* Check for which stream we were successful */
	if (DMA_Stream == USART_DMA_GetStreamTX(USART))
    {
		/* DMA transfer has finished */
		/* We also have to wait for USART to finish transmitting last byte from DMA */
		while (USART_DMA_Transmitting(USART));
		
		/* Send notification to the same USART port with polling mode */
		USART_Puts(USART, "DMA has sent data!\n");
	}
}
