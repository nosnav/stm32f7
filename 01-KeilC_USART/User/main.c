#include "main.h"

int main(void)
{
    System_Init();
    LED_Init(ALL);
    Delay_Init();
    /* Init USART, Pins not initialized yet, 256000 bauds */
	USART_Init(USART1, USART_PinsPack_Custom, 256000);
	
	/* Put test string */
	USART_Puts(USART1, "Hello world\n");
	
	while (1) {
		/* Check if anything received */
		while (!USART_BufferEmpty(USART1)) {
			/* Send data back from buffer */
			USART_Putc(USART1, USART_Getc(USART1));
		}
	}
}

/* USART Custom pins callback function */
void USART_InitCustomPinsCallback(USART_TypeDef* USARTx, uint16_t AlternateFunction) { 
	/* Check for proper USART */
	if (USARTx == USART1) {
		/* Init pins for USART 6 */
		GPIO_InitAlternate(GPIOA, GPIO_PIN_9, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Fast, AlternateFunction);
        GPIO_InitAlternate(GPIOB, GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_Fast, AlternateFunction);
    }
}
