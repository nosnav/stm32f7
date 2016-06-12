#include "stm32f7_usart.h"

/* Set alternate function mappings */

#if defined(USART1)
#define GPIO_AF_USART1     GPIO_AF7_USART1
#define IRQ_USART1         USART1_IRQn
#endif
#if defined(USART2)
#define GPIO_AF_USART2     GPIO_AF7_USART2
#define IRQ_USART2         USART2_IRQn
#endif
#if defined(USART3)
#define GPIO_AF_USART3     GPIO_AF7_USART3
#define IRQ_USART3         USART3_IRQn
#endif
#if defined(UART4)
#define GPIO_AF_UART4      GPIO_AF8_UART4
#define IRQ_UART4          UART4_IRQn
#endif
#if defined(UART5)
#define IRQ_UART5          UART5_IRQn
#endif
#if defined(USART6)
#define GPIO_AF_USART6     GPIO_AF8_USART6
#define IRQ_USART6         USART6_IRQn
#endif
#if defined(UART7)
#define GPIO_AF_UART7      GPIO_AF8_UART7
#define IRQ_UART7          UART7_IRQn
#endif
#if defined(UART8)
#define GPIO_AF_UART8      GPIO_AF8_UART8
#define IRQ_UART8          UART8_IRQn
#endif

/* Set variables for buffers */
#ifdef USART1
uint8_t USART1_Buffer[USART1_BUFFER_SIZE];
#endif
#ifdef USART2
uint8_t USART2_Buffer[USART2_BUFFER_SIZE];
#endif
#ifdef USART3
uint8_t USART3_Buffer[USART3_BUFFER_SIZE];
#endif
#ifdef UART4
uint8_t UART4_Buffer[UART4_BUFFER_SIZE];
#endif
#ifdef UART5
uint8_t UART5_Buffer[UART5_BUFFER_SIZE];
#endif
#ifdef USART6
uint8_t USART6_Buffer[USART6_BUFFER_SIZE];
#endif
#ifdef UART7
uint8_t UART7_Buffer[UART7_BUFFER_SIZE];
#endif
#ifdef UART8
uint8_t UART8_Buffer[UART8_BUFFER_SIZE];
#endif

#ifdef USART1
BUFFER_t USART1_BF = {USART1_BUFFER_SIZE, 0, 0, USART1_Buffer, 0, USART_STRING_DELIMITER};
#endif
#ifdef USART2
BUFFER_t USART2_BF = {USART2_BUFFER_SIZE, 0, 0, USART2_Buffer, 0, USART_STRING_DELIMITER};
#endif
#ifdef USART3
BUFFER_t USART3_BF = {USART3_BUFFER_SIZE, 0, 0, USART3_Buffer, 0, USART_STRING_DELIMITER};
#endif
#ifdef UART4
BUFFER_t UART4_BF = {UART4_BUFFER_SIZE, 0, 0, UART4_Buffer, 0, USART_STRING_DELIMITER};
#endif
#ifdef UART5
BUFFER_t UART5_BF = {UART5_BUFFER_SIZE, 0, 0, UART5_Buffer, 0, USART_STRING_DELIMITER};
#endif
#ifdef USART6
BUFFER_t USART6_BF = {USART6_BUFFER_SIZE, 0, 0, USART6_Buffer, 0, USART_STRING_DELIMITER};
#endif
#ifdef UART7
BUFFER_t UART7_BF = {UART7_BUFFER_SIZE, 0, 0, UART7_Buffer, 0, USART_STRING_DELIMITER};
#endif
#ifdef UART8
BUFFER_t UART8_BF = {UART8_BUFFER_SIZE, 0, 0, UART8_Buffer, 0, USART_STRING_DELIMITER};
#endif

/* Private functions */
void USART1_InitPins(USART_PinsPack_t pinspack);
void USART2_InitPins(USART_PinsPack_t pinspack);
void USART3_InitPins(USART_PinsPack_t pinspack);
void UART4_InitPins(USART_PinsPack_t pinspack);
void UART5_InitPins(USART_PinsPack_t pinspack);
void USART6_InitPins(USART_PinsPack_t pinspack);
void UART7_InitPins(USART_PinsPack_t pinspack);
void UART8_InitPins(USART_PinsPack_t pinspack);
static void USART_INT_InsertToBuffer(BUFFER_t* u, uint8_t c);
static void USART_INT_ClearAllFlags(USART_TypeDef* USARTx, IRQn_Type irq);
static BUFFER_t* USART_INT_GetUSARTBuffer(USART_TypeDef* USARTx);
static uint8_t USART_INT_GetSubPriority(USART_TypeDef* USARTx);
uint8_t USART_BufferFull(USART_TypeDef* USARTx);

/* Private initializator function */
static void USART_INT_Init(
	USART_TypeDef* USARTx,
	USART_PinsPack_t pinspack,
	uint32_t baudrate,
	USART_HardwareFlowControl_t FlowControl,
	uint32_t Mode,
	uint32_t Parity,
	uint32_t StopBits,
	uint32_t WordLength
);

void USART_Init(USART_TypeDef* USARTx, USART_PinsPack_t pinspack, uint32_t baudrate) {
#ifdef USART1
	if (USARTx == USART1) {
		USART_INT_Init(USART1, pinspack, baudrate, USART1_HARDWARE_FLOW_CONTROL, USART1_MODE, USART1_PARITY, USART1_STOP_BITS, USART1_WORD_LENGTH);
	}
#endif
#ifdef USART2
	if (USARTx == USART2) {
		USART_INT_Init(USART2, pinspack, baudrate, USART2_HARDWARE_FLOW_CONTROL, USART2_MODE, USART2_PARITY, USART2_STOP_BITS, USART2_WORD_LENGTH);
	}
#endif
#ifdef USART3
	if (USARTx == USART3) {
		USART_INT_Init(USART3, pinspack, baudrate, USART3_HARDWARE_FLOW_CONTROL, USART3_MODE, USART3_PARITY, USART3_STOP_BITS, USART3_WORD_LENGTH);
	}
#endif
#ifdef UART4
	if (USARTx == UART4) {
		USART_INT_Init(UART4, pinspack, baudrate, UART4_HARDWARE_FLOW_CONTROL, UART4_MODE, UART4_PARITY, UART4_STOP_BITS, UART4_WORD_LENGTH);
	}
#endif
#ifdef UART5
	if (USARTx == UART5) {
		USART_INT_Init(UART5, pinspack, baudrate, UART5_HARDWARE_FLOW_CONTROL, UART5_MODE, UART5_PARITY, UART5_STOP_BITS, UART5_WORD_LENGTH);
	}
#endif
#ifdef USART6
	if (USARTx == USART6) {
		USART_INT_Init(USART6, pinspack, baudrate, USART6_HARDWARE_FLOW_CONTROL, USART6_MODE, USART6_PARITY, USART6_STOP_BITS, USART6_WORD_LENGTH);
	}
#endif
#ifdef UART7
	if (USARTx == UART7) {
		USART_INT_Init(UART7, pinspack, baudrate, UART7_HARDWARE_FLOW_CONTROL, UART7_MODE, UART7_PARITY, UART7_STOP_BITS, UART7_WORD_LENGTH);
	}
#endif
#ifdef UART8
	if (USARTx == UART8) {
		USART_INT_Init(UART8, pinspack, baudrate, UART8_HARDWARE_FLOW_CONTROL, UART8_MODE, UART8_PARITY, UART8_STOP_BITS, UART8_WORD_LENGTH);
	}
#endif
	
/* STM32F0xx related */
#ifdef USART4
	if (USARTx == USART4) {
		USART_INT_Init(USART4, pinspack, baudrate, USART4_HARDWARE_FLOW_CONTROL, USART4_MODE, USART4_PARITY, USART4_STOP_BITS, USART4_WORD_LENGTH);
	}
#endif	
#ifdef USART5
	if (USARTx == USART5) {
		USART_INT_Init(USART5, pinspack, baudrate, USART5_HARDWARE_FLOW_CONTROL, USART5_MODE, USART5_PARITY, USART5_STOP_BITS, USART5_WORD_LENGTH);
	}
#endif	
#ifdef USART7
	if (USARTx == USART7) {
		USART_INT_Init(USART7, pinspack, baudrate, USART7_HARDWARE_FLOW_CONTROL, USART7_MODE, USART7_PARITY, USART7_STOP_BITS, USART7_WORD_LENGTH);
	}
#endif	
#ifdef USART8
	if (USARTx == USART8) {
		USART_INT_Init(USART8, pinspack, baudrate, USART8_HARDWARE_FLOW_CONTROL, USART8_MODE, USART8_PARITY, USART8_STOP_BITS, USART8_WORD_LENGTH);
	}
#endif
}

void USART_InitWithFlowControl(USART_TypeDef* USARTx, USART_PinsPack_t pinspack, uint32_t baudrate, USART_HardwareFlowControl_t FlowControl) {
#ifdef USART1
	if (USARTx == USART1) {
		USART_INT_Init(USART1, pinspack, baudrate, FlowControl, USART1_MODE, USART1_PARITY, USART1_STOP_BITS, USART1_WORD_LENGTH);
	}
#endif
#ifdef USART2
	if (USARTx == USART2) {
		USART_INT_Init(USART2, pinspack, baudrate, FlowControl, USART2_MODE, USART2_PARITY, USART2_STOP_BITS, USART2_WORD_LENGTH);
	}
#endif
#ifdef USART3
	if (USARTx == USART3) {
		USART_INT_Init(USART3, pinspack, baudrate, FlowControl, USART3_MODE, USART3_PARITY, USART3_STOP_BITS, USART3_WORD_LENGTH);
	}
#endif
#ifdef UART4
	if (USARTx == UART4) {
		USART_INT_Init(UART4, pinspack, baudrate, FlowControl, UART4_MODE, UART4_PARITY, UART4_STOP_BITS, UART4_WORD_LENGTH);
	}
#endif
#ifdef UART5
	if (USARTx == UART5) {
		USART_INT_Init(UART5, pinspack, baudrate, FlowControl, UART5_MODE, UART5_PARITY, UART5_STOP_BITS, UART5_WORD_LENGTH);
	}
#endif
#ifdef USART6
	if (USARTx == USART6) {
		USART_INT_Init(USART6, pinspack, baudrate, FlowControl, USART6_MODE, USART6_PARITY, USART6_STOP_BITS, USART6_WORD_LENGTH);
	}
#endif
#ifdef UART7
	if (USARTx == UART7) {
		USART_INT_Init(UART7, pinspack, baudrate, FlowControl, UART7_MODE, UART7_PARITY, UART7_STOP_BITS, UART7_WORD_LENGTH);
	}
#endif
#ifdef UART8
	if (USARTx == UART8) {
		USART_INT_Init(UART8, pinspack, baudrate, FlowControl, UART8_MODE, UART8_PARITY, UART8_STOP_BITS, UART8_WORD_LENGTH);
	}
#endif
	
/* STM32F0xx related */
#ifdef USART4
	if (USARTx == USART4) {
		USART_INT_Init(USART4, pinspack, baudrate, FlowControl, USART4_MODE, USART4_PARITY, USART4_STOP_BITS, USART4_WORD_LENGTH);
	}
#endif	
#ifdef USART5
	if (USARTx == USART5) {
		USART_INT_Init(USART5, pinspack, baudrate, FlowControl, USART5_MODE, USART5_PARITY, USART5_STOP_BITS, USART5_WORD_LENGTH);
	}
#endif	
#ifdef USART7
	if (USARTx == USART7) {
		USART_INT_Init(USART7, pinspack, baudrate, FlowControl, USART7_MODE, USART7_PARITY, USART7_STOP_BITS, USART7_WORD_LENGTH);
	}
#endif	
#ifdef USART8
	if (USARTx == USART8) {
		USART_INT_Init(USART8, pinspack, baudrate, FlowControl, USART8_MODE, USART8_PARITY, USART8_STOP_BITS, USART8_WORD_LENGTH);
	}
#endif
}

uint8_t USART_Getc(USART_TypeDef* USARTx) {
	uint8_t c;
	
	/* Read character from buffer */
	if (BUFFER_Read(USART_INT_GetUSARTBuffer(USARTx), &c, 1)) {
		return c;
	}
	
	/* Read was not successfull */
	return 0;
}

uint16_t USART_Gets(USART_TypeDef* USARTx, char* buffer, uint16_t bufsize) {
	return BUFFER_ReadString(USART_INT_GetUSARTBuffer(USARTx), buffer, bufsize);
}

void USART_Puts(USART_TypeDef* USARTx, char* str) {
	/* Go through entire string */
	while (*str) {
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
		/* Send data */
		USART_WRITE_DATA(USARTx, (uint16_t)(*str++));
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
	}
}

void USART_Send(USART_TypeDef* USARTx, uint8_t* DataArray, uint16_t count) {
	/* Go through entire data array */
	while (count--) {
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
		/* Send data */
		USART_WRITE_DATA(USARTx, (uint16_t)(*DataArray++));
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
	}
}

int16_t USART_FindCharacter(USART_TypeDef* USARTx, uint8_t c) {
	return BUFFER_FindElement(USART_INT_GetUSARTBuffer(USARTx), c);
}

int16_t USART_FindString(USART_TypeDef* USARTx, char* str) {
	return BUFFER_Find(USART_INT_GetUSARTBuffer(USARTx), (uint8_t *)str, strlen(str));
}

uint8_t USART_BufferEmpty(USART_TypeDef* USARTx) {
	return BUFFER_GetFull(USART_INT_GetUSARTBuffer(USARTx)) == 0;
}

uint8_t USART_BufferFull(USART_TypeDef* USARTx) {
	return BUFFER_GetFree(USART_INT_GetUSARTBuffer(USARTx)) == 0;
}

uint16_t USART_BufferCount(USART_TypeDef* USARTx) {
	return BUFFER_GetFull(USART_INT_GetUSARTBuffer(USARTx));
}

void USART_ClearBuffer(USART_TypeDef* USARTx) {
	BUFFER_Reset(USART_INT_GetUSARTBuffer(USARTx));
}

void USART_SetCustomStringEndCharacter(USART_TypeDef* USARTx, uint8_t Character) {
	BUFFER_SetStringDelimiter(USART_INT_GetUSARTBuffer(USARTx), Character);
}

/************************************/
/*    USART CUSTOM PINS CALLBACK    */
/************************************/
__weak void USART_InitCustomPinsCallback(USART_TypeDef* USARTx, uint16_t AlternateFunction) { 
	/* NOTE: This function Should not be modified, when the callback is needed,
           the USART_InitCustomPinsCallback could be implemented in the user file
	*/
}

/* Private functions */
static void USART_INT_InsertToBuffer(BUFFER_t* u, uint8_t c) {
	BUFFER_Write(u, &c, 1);
}

static BUFFER_t* USART_INT_GetUSARTBuffer(USART_TypeDef* USARTx) {
	BUFFER_t* u;
	
#ifdef USART1
	if (USARTx == USART1) {
		u = &USART1_BF;
	}
#endif
#ifdef USART2
	if (USARTx == USART2) {
		u = &USART2_BF;
	}
#endif
#ifdef USART3
	if (USARTx == USART3) {
		u = &USART3_BF;
	}
#endif
#ifdef UART4
	if (USARTx == UART4) {
		u = &UART4_BF;
	}
#endif
#ifdef UART5
	if (USARTx == UART5) {
		u = &UART5_BF;
	}
#endif
#ifdef USART6
	if (USARTx == USART6) {
		u = &USART6_BF;
	}
#endif
#ifdef UART7
	if (USARTx == UART7) {
		u = &UART7_BF;
	}
#endif
#ifdef UART8
	if (USARTx == UART8) {
		u = &UART8_BF;
	}
#endif

/* STM32F0xx related */
#ifdef USART4
	if (USARTx == USART4) {
		u = &USART4;
	}
#endif
#ifdef USART5
	if (USARTx == USART5) {
		u = &USART5;
	}
#endif
#ifdef USART7
	if (USARTx == USART7) {
		u = &USART7;
	}
#endif
#ifdef USART8
	if (USARTx == USART8) {
		u = &USART8;
	}
#endif

	return u;
}

static uint8_t USART_INT_GetSubPriority(USART_TypeDef* USARTx) {
	uint8_t u;
	
#ifdef USART1
	if (USARTx == USART1) {
		u = 0;
	}
#endif
#ifdef USART2
	if (USARTx == USART2) {
		u = 1;
	}
#endif
#ifdef USART3
	if (USARTx == USART3) {
		u = 2;
	}
#endif
#ifdef UART4
	if (USARTx == UART4) {
		u = 4;
	}
#endif
#ifdef UART5
	if (USARTx == UART5) {
		u = 5;
	}
#endif
#ifdef USART6
	if (USARTx == USART6) {
		u = 6;
	}
#endif
#ifdef UART7
	if (USARTx == UART7) {
		u = 7;
	}
#endif
#ifdef UART8
	if (USARTx == UART8) {
		u = 8;
	}
#endif
	
	return u;
}

/* PIN initializations */
#ifdef USART1
void USART1_InitPins(USART_PinsPack_t pinspack) {	
	/* Init pins */
#if defined(GPIOA)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOA, GPIO_PIN_9 | GPIO_PIN_10, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART1);
	}
#endif
#if defined(GPIOB)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_6 | GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART1);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART1, GPIO_AF_USART1);
	}
}
#endif

#ifdef USART2
void USART2_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOA)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOA, GPIO_PIN_2 | GPIO_PIN_3, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART2);
	}
#endif
#if defined(GPIOD)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOD, GPIO_PIN_5 | GPIO_PIN_6, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART2);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART2, GPIO_AF_USART2);
	}
}
#endif

#ifdef USART3
void USART3_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOB)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_10 | GPIO_PIN_11, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART3);
	}
#endif
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_10 | GPIO_PIN_11, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART3);
	}
#endif
#if defined(GPIOD)
	if (pinspack == USART_PinsPack_3) {
		GPIO_InitAlternate(GPIOD, GPIO_PIN_8 | GPIO_PIN_9, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART3);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART3, GPIO_AF_USART3);
	}
}
#endif

#ifdef UART4
void UART4_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOA)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_UART4);
	}
#endif
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_10 | GPIO_PIN_11, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_UART4);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(UART4, GPIO_AF_UART4);
	}
}
#endif

#ifdef UART5
void UART5_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOC) && defined(GPIOD)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_12, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_UART5);
		GPIO_InitAlternate(GPIOD, GPIO_PIN_2, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_UART5);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(UART5, GPIO_AF_UART5);
	}
}
#endif

#ifdef USART6
void USART6_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_6 | GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART6);
	}
#endif
#if defined(GPIOG)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOG, GPIO_PIN_14 | GPIO_PIN_9, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART6);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART6, GPIO_AF_USART6);
	}
}
#endif

#ifdef UART7
void UART7_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOE)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOE, GPIO_PIN_8 | GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_UART7);
	}
#endif
#if defined(GPIOF)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOF, GPIO_PIN_7 | GPIO_PIN_6, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_UART7);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(UART7, GPIO_AF_UART7);
	}
}
#endif

#ifdef UART8
void UART8_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOE)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOE, GPIO_PIN_1 | GPIO_PIN_0, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_UART8);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(UART8, GPIO_AF_UART8);
	}
}
#endif

/* STM32F0xx related */
#ifdef USART4
void USART4_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOA)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART4);
	}
#endif
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_10 | GPIO_PIN_11, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART4);
	}
#endif
#if defined(GPIOE)
	if (pinspack == USART_PinsPack_3) {
		GPIO_InitAlternate(GPIOE, GPIO_PIN_8 | GPIO_PIN_9, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART4);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART4, GPIO_AF_USART4);
	}
}
#endif
#ifdef USART5
void USART5_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOB)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_3 | GPIO_PIN_4, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART5);
	}
#endif
#if defined(GPIOC) && defined(GPIOD)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_12, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART5);
		GPIO_InitAlternate(GPIOD, GPIO_PIN_2, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART5);
	}
#endif
#if defined(GPIOE)
	if (pinspack == USART_PinsPack_3) {
		GPIO_InitAlternate(GPIOE, GPIO_PIN_10 | GPIO_PIN_11, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART5);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART5, GPIO_AF_USART5);
	}
}
#endif
#ifdef USART7
void USART7_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_0 | GPIO_PIN_1, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART7);
	}
#endif
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_6 | GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART7);
	}
#endif
#if defined(GPIOF)
	if (pinspack == USART_PinsPack_3) {
		GPIO_InitAlternate(GPIOF, GPIO_PIN_2 | GPIO_PIN_3, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART7);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART7, GPIO_AF_USART7);
	}
}
#endif
#ifdef USART8
void USART8_InitPins(USART_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_1) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_2 | GPIO_PIN_3, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART8);
	}
#endif
#if defined(GPIOC)
	if (pinspack == USART_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_8 | GPIO_PIN_9, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART8);
	}
#endif
#if defined(GPIOD)
	if (pinspack == USART_PinsPack_3) {
		GPIO_InitAlternate(GPIOD, GPIO_PIN_13 | GPIO_PIN_14, GPIO_OType_PP, GPIO_PuPd_UP, GPIO_Speed_High, GPIO_AF_USART8);
	}
#endif
	if (pinspack == USART_PinsPack_Custom) {
		/* Init custom pins, callback used */
		USART_InitCustomPinsCallback(USART8, GPIO_AF_USART8);
	}
}
#endif

/* Interrupt handlers */
#ifdef USART1
void USART1_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (USART1->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART1_USE_CUSTOM_IRQ
		/* Call user function */
		USART1_ReceiveHandler(USART_READ_DATA(USART1));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART1_BF, USART_READ_DATA(USART1));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(USART1, IRQ_USART1);
}
#endif

#ifdef USART2
void USART2_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (USART2->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART2_USE_CUSTOM_IRQ
		/* Call user function */
		USART2_ReceiveHandler(USART_READ_DATA(USART2));
#else 
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART2_BF, USART_READ_DATA(USART2));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(USART2, IRQ_USART2);
}
#endif

#ifdef USART3
void USART3_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (USART3->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART3_USE_CUSTOM_IRQ
		/* Call user function */
		USART3_ReceiveHandler(USART_READ_DATA(USART3));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART3_BF, USART_READ_DATA(USART3));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(USART3, IRQ_USART3);
}
#endif

#ifdef UART4
void UART4_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (UART4->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef UART4_USE_CUSTOM_IRQ
		/* Call user function */
		UART4_ReceiveHandler(USART_READ_DATA(UART4));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&UART4_BF, USART_READ_DATA(UART4));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(UART4, IRQ_UART4);
}
#endif

#ifdef UART5
void UART5_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (UART5->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef UART5_USE_CUSTOM_IRQ
		/* Call user function */
		UART5_ReceiveHandler(USART_READ_DATA(UART5));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&UART5_BF, USART_READ_DATA(UART5));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(UART5, IRQ_UART5);
}
#endif

#ifdef USART6
void USART6_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (USART6->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART6_USE_CUSTOM_IRQ
		/* Call user function */
		USART6_ReceiveHandler(USART_READ_DATA(USART6));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART6_BF, USART_READ_DATA(USART6));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(USART6, IRQ_USART6);
}
#endif

#ifdef UART7
void UART7_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (UART7->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef UART7_USE_CUSTOM_IRQ
		/* Call user function */
		UART7_ReceiveHandler(USART_READ_DATA(UART7));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&UART7_BF, USART_READ_DATA(UART7));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(UART7, IRQ_UART7);
}
#endif

#ifdef UART8
void UART8_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (UART8->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef UART8_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(UART8));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&UART8_BF, USART_READ_DATA(UART8));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(UART8, IRQ_UART8);
}
#endif

#if defined(STM32F0xx)
#ifdef USART8
void USART3_8_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (USART3->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART3_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART3));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART3, USART_READ_DATA(USART3));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART4->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART4_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART4));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART4, USART_READ_DATA(USART4));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART5->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART5_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART5));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART5, USART_READ_DATA(USART5));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART6->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART6_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART6));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART6, USART_READ_DATA(USART6));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART7->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART7_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART7));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART7, USART_READ_DATA(USART7));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART8->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART8_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART8));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART8, USART_READ_DATA(USART8));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(USART3, IRQ_USART3);
	USART_INT_ClearAllFlags(USART4, IRQ_USART4);
	USART_INT_ClearAllFlags(USART5, IRQ_USART5);
	USART_INT_ClearAllFlags(USART6, IRQ_USART6);
	USART_INT_ClearAllFlags(USART7, IRQ_USART7);
	USART_INT_ClearAllFlags(USART8, IRQ_USART8);
}
#elif defined(USART6)
void USART3_6_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (USART3->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART3_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART3));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART3, USART_READ_DATA(USART3));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART4->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART4_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART4));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART4, USART_READ_DATA(USART4));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART5->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART5_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART5));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART5, USART_READ_DATA(USART5));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART6->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART6_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART6));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART6, USART_READ_DATA(USART6));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(USART3);
	USART_INT_ClearAllFlags(USART4);
	USART_INT_ClearAllFlags(USART5);
	USART_INT_ClearAllFlags(USART6);
}
#elif defined(USART4)
void USART3_6_IRQHandler(void) {
	/* Check if interrupt was because data is received */
	if (USART3->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART3_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART3));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART3, USART_READ_DATA(USART3));
#endif
	}

	/* Check if interrupt was because data is received */
	if (USART4->USART_STATUS_REG & USART_ISR_RXNE) {
#ifdef USART4_USE_CUSTOM_IRQ
		/* Call user function */
		UART8_ReceiveHandler(USART_READ_DATA(USART4));
#else
		/* Put received data into internal buffer */
		USART_INT_InsertToBuffer(&USART4, USART_READ_DATA(USART4));
#endif
	}
	
	/* Clear all USART flags */
	USART_INT_ClearAllFlags(USART3);
	USART_INT_ClearAllFlags(USART4);
}
#endif
#endif

static void USART_INT_Init(
	USART_TypeDef* USARTx,
	USART_PinsPack_t pinspack,
	uint32_t baudrate,
	USART_HardwareFlowControl_t FlowControl,
	uint32_t Mode,
	uint32_t Parity,
	uint32_t StopBits,
	uint32_t WordLength
) {
	UART_HandleTypeDef UARTHandle;
	IRQn_Type irq;
	
	/*
	 * Initialize USARTx pins
	 * Set channel for USARTx NVIC
	 */
#ifdef USART1
	if (USARTx == USART1) {
		/* Enable USART clock */
		__HAL_RCC_USART1_CLK_ENABLE();
		__HAL_RCC_USART1_FORCE_RESET();
		__HAL_RCC_USART1_RELEASE_RESET();
		
		/* Init pins */
		USART1_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART1;
	}
#endif
#ifdef USART2
	if (USARTx == USART2) {
		/* Enable USART clock */
		__HAL_RCC_USART2_CLK_ENABLE();
		__HAL_RCC_USART2_FORCE_RESET();
		__HAL_RCC_USART2_RELEASE_RESET();
		
		/* Init pins */
		USART2_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART2;
	}
#endif
#ifdef USART3
	if (USARTx == USART3) {
		/* Enable USART clock */
		__HAL_RCC_USART3_CLK_ENABLE();
		__HAL_RCC_USART3_FORCE_RESET();
		__HAL_RCC_USART3_RELEASE_RESET();
		
		/* Init pins */
		USART3_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART3;
	}
#endif
#ifdef UART4
	if (USARTx == UART4) {
		/* Enable UART clock */
		__HAL_RCC_UART4_CLK_ENABLE();
		__HAL_RCC_UART4_FORCE_RESET();
		__HAL_RCC_UART4_RELEASE_RESET();
		
		/* Init pins */
		UART4_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_UART4;
	}
#endif
#ifdef UART5
	if (USARTx == UART5) {
		/* Enable UART clock */
		__HAL_RCC_UART5_CLK_ENABLE();
		__HAL_RCC_UART5_FORCE_RESET();
		__HAL_RCC_UART5_RELEASE_RESET();

		/* Init pins */
		UART5_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_UART5;
	}
#endif
#ifdef USART6
	if (USARTx == USART6) {
		/* Enable UART clock */
		__HAL_RCC_USART6_CLK_ENABLE();
		__HAL_RCC_USART6_FORCE_RESET();
		__HAL_RCC_USART6_RELEASE_RESET();
		
		/* Init pins */
		USART6_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART6;
	}
#endif
#ifdef UART7
	if (USARTx == UART7) {
		/* Enable UART clock */
		__HAL_RCC_UART7_CLK_ENABLE();
		__HAL_RCC_UART7_FORCE_RESET();
		__HAL_RCC_UART7_RELEASE_RESET();
		
		/* Init pins */
		UART7_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_UART7;
	}
#endif
#ifdef UART8
	if (USARTx == UART8) {
		/* Enable UART clock */
		__HAL_RCC_UART8_CLK_ENABLE();
		__HAL_RCC_UART8_FORCE_RESET();
		__HAL_RCC_UART8_RELEASE_RESET();

		/* Init pins */
		UART8_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_UART8;
	}
#endif
	
/* STM32F0xx related */
#ifdef USART4
	if (USARTx == USART4) {
		/* Enable UART clock */
		__HAL_RCC_USART4_CLK_ENABLE();
		__HAL_RCC_USART4_FORCE_RESET();
		__HAL_RCC_USART4_RELEASE_RESET();
		
		/* Init pins */
		USART4_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART4;
	}
#endif
#ifdef USART5
	if (USARTx == USART5) {
		/* Enable UART clock */
		__HAL_RCC_USART5_CLK_ENABLE();
		__HAL_RCC_USART5_FORCE_RESET();
		__HAL_RCC_USART5_RELEASE_RESET();
		
		/* Init pins */
		USART5_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART5;
	}
#endif
#ifdef USART7
	if (USARTx == USART7) {
		/* Enable UART clock */
		__HAL_RCC_USART7_CLK_ENABLE();
		__HAL_RCC_USART7_FORCE_RESET();
		__HAL_RCC_USART7_RELEASE_RESET();
		
		/* Init pins */
		USART7_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART7;
	}
#endif
#ifdef USART8
	if (USARTx == USART8) {
		/* Enable UART clock */
		__HAL_RCC_USART8_CLK_ENABLE();
		__HAL_RCC_USART8_FORCE_RESET();
		__HAL_RCC_USART8_RELEASE_RESET();
		
		/* Init pins */
		USART8_InitPins(pinspack);
		
		/* Set IRQ channel */
		irq = IRQ_USART8;
	}
#endif
	
	/* Fill default settings */
	UARTHandle.Instance = USARTx;
	UARTHandle.Init.BaudRate = baudrate;
	UARTHandle.Init.HwFlowCtl = FlowControl;
	UARTHandle.Init.Mode = Mode;
	UARTHandle.Init.Parity = Parity;
	UARTHandle.Init.StopBits = StopBits;
	UARTHandle.Init.WordLength = WordLength;
	UARTHandle.Init.OverSampling = UART_OVERSAMPLING_16;
#if defined(STM32F0xx)
	UARTHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
#endif
	
	/* Disable IRQ */
	HAL_NVIC_DisableIRQ(irq);

	/* Set priority */
	HAL_NVIC_SetPriority(irq, USART_NVIC_PRIORITY, USART_INT_GetSubPriority(USARTx));
	
	/* Enable interrupt */
	HAL_NVIC_EnableIRQ(irq);
	
	/* Clear interrupt */
	HAL_NVIC_ClearPendingIRQ(irq);
	
	/* Init USART */
	HAL_UART_Init(&UARTHandle);
	
	/* Enable RX interrupt */
	USARTx->CR1 |= USART_CR1_RXNEIE;
}

static UART_HandleTypeDef UART_Handle;
static void USART_INT_ClearAllFlags(USART_TypeDef* USARTx, IRQn_Type irq) {
	UART_Handle.Instance = USARTx;
	
#ifdef __HAL_UART_CLEAR_PEFLAG
	__HAL_UART_CLEAR_PEFLAG(&UART_Handle);
#endif
#ifdef __HAL_UART_CLEAR_FEFLAG
	__HAL_UART_CLEAR_FEFLAG(&UART_Handle);
#endif
#ifdef __HAL_UART_CLEAR_NEFLAG
	__HAL_UART_CLEAR_NEFLAG(&UART_Handle);
#endif
#ifdef __HAL_UART_CLEAR_OREFLAG
	__HAL_UART_CLEAR_OREFLAG(&UART_Handle);
#endif
#ifdef __HAL_UART_CLEAR_IDLEFLAG
	__HAL_UART_CLEAR_IDLEFLAG(&UART_Handle);
#endif
	
	/* Clear IRQ bit */
	HAL_NVIC_ClearPendingIRQ(irq);
}

