/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#include "tm_stm32_spi.h"

/* Defines for alternate functions */
//#if defined(STM32F4xx) || defined(STM32F7xx)
#define GPIO_AFx_SPI1    GPIO_AF5_SPI1
#define GPIO_AFx_SPI2    0x05
#define GPIO_AFx_SPI3    0x06
#define GPIO_AFx_SPI4    GPIO_AF5_SPI4
#define GPIO_AFx_SPI5    0x05
#define GPIO_AFx_SPI6    GPIO_AF5_SPI6
//#endif
//#if defined(STM32F0xx)
//#define GPIO_AFx_SPI1    GPIO_AF0_SPI1
//#define GPIO_AFx_SPI2    GPIO_AF0_SPI2
//#endif

/* Private functions */
static void SPIx_Init(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, SPI_Mode_t SPI_Mode, uint16_t SPI_BaudRatePrescaler, uint16_t SPI_MasterSlave, uint16_t SPI_FirstBit);
void SPI1_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI2_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI3_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI4_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI5_INT_InitPins(SPI_PinsPack_t pinspack);
void SPI6_INT_InitPins(SPI_PinsPack_t pinspack);

void SPI_Init(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack) {
	/* Init with default settings */
#ifdef SPI1
	if (SPIx == SPI1) {
		SPIx_Init(SPI1, pinspack, SPI1_MODE, SPI1_PRESCALER, SPI1_MASTERSLAVE, SPI1_FIRSTBIT);
	}
#endif
#ifdef SPI2
	if (SPIx == SPI2) {
		SPIx_Init(SPI2, pinspack, SPI2_MODE, SPI2_PRESCALER, SPI2_MASTERSLAVE, SPI2_FIRSTBIT);
	}
#endif
#ifdef SPI3
	if (SPIx == SPI3) {
		SPIx_Init(SPI3, pinspack, SPI3_MODE, SPI3_PRESCALER, SPI3_MASTERSLAVE, SPI3_FIRSTBIT);
	}
#endif
#ifdef SPI4
	if (SPIx == SPI4) {
		SPIx_Init(SPI4, pinspack, SPI4_MODE, SPI4_PRESCALER, SPI4_MASTERSLAVE, SPI4_FIRSTBIT);
	}
#endif
#ifdef SPI5
	if (SPIx == SPI5) {
		SPIx_Init(SPI5, pinspack, SPI5_MODE, SPI5_PRESCALER, SPI5_MASTERSLAVE, SPI5_FIRSTBIT);
	}
#endif
#ifdef SPI6
	if (SPIx == SPI6) {
		SPIx_Init(SPI6, pinspack, SPI6_MODE, SPI6_PRESCALER, SPI6_MASTERSLAVE, SPI6_FIRSTBIT);
	}
#endif
}

void SPI_InitWithMode(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, SPI_Mode_t SPI_Mode) {
	/* Init with custom mode, 0, 1, 2, 3 */
#ifdef SPI1
	if (SPIx == SPI1) {
		SPIx_Init(SPI1, pinspack, SPI_Mode, SPI1_PRESCALER, SPI1_MASTERSLAVE, SPI1_FIRSTBIT);
	}
#endif
#ifdef SPI2
	if (SPIx == SPI2) {
		SPIx_Init(SPI2, pinspack, SPI_Mode, SPI2_PRESCALER, SPI2_MASTERSLAVE, SPI2_FIRSTBIT);
	}
#endif
#ifdef SPI3
	if (SPIx == SPI3) {
		SPIx_Init(SPI3, pinspack, SPI_Mode, SPI3_PRESCALER, SPI3_MASTERSLAVE, SPI3_FIRSTBIT);
	}
#endif
#ifdef SPI4
	if (SPIx == SPI4) {
		SPIx_Init(SPI4, pinspack, SPI_Mode, SPI4_PRESCALER, SPI4_MASTERSLAVE, SPI4_FIRSTBIT);
	}
#endif
#ifdef SPI5
	if (SPIx == SPI5) {
		SPIx_Init(SPI5, pinspack, SPI_Mode, SPI5_PRESCALER, SPI5_MASTERSLAVE, SPI5_FIRSTBIT);
	}
#endif
#ifdef SPI6
	if (SPIx == SPI6) {
		SPIx_Init(SPI6, pinspack, SPI_Mode, SPI6_PRESCALER, SPI6_MASTERSLAVE, SPI6_FIRSTBIT);
	}
#endif
}

void SPI_InitFull(
	SPI_TypeDef* SPIx,              \
	SPI_PinsPack_t pinspack,     \
	uint16_t SPI_BaudRatePrescaler, \
	SPI_Mode_t SPI_Mode_t,       \
	uint16_t SPI_Mode,              \
	uint16_t SPI_FirstBit           \
) {
	/* Init FULL SPI settings by user */
#ifdef SPI1
	if (SPIx == SPI1) {
		SPIx_Init(SPI1, pinspack, SPI_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef SPI2
	if (SPIx == SPI2) {
		SPIx_Init(SPI2, pinspack, SPI_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef SPI3
	if (SPIx == SPI3) {
		SPIx_Init(SPI3, pinspack, SPI_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef SPI4
	if (SPIx == SPI4) {
		SPIx_Init(SPI4, pinspack, SPI_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef SPI5
	if (SPIx == SPI5) {
		SPIx_Init(SPI5, pinspack, SPI_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
#ifdef SPI6
	if (SPIx == SPI6) {
		SPIx_Init(SPI6, pinspack, SPI_Mode_t, SPI_BaudRatePrescaler, SPI_Mode, SPI_FirstBit);
	}
#endif
}

uint16_t SPI_GetPrescalerFromMaxFrequency(SPI_TypeDef* SPIx, uint32_t MAX_SPI_Frequency) {
	uint32_t APB_Frequency;
	uint8_t i;
	
	/* Prevent false input */
	if (MAX_SPI_Frequency == 0) {
		return SPI_BAUDRATEPRESCALER_256;
	}
	
	/* Calculate max SPI clock */
	if (0
#ifdef SPI1	
		|| SPIx == SPI1
#endif
#ifdef SPI4
		|| SPIx == SPI4
#endif
#ifdef SPI5
		|| SPIx == SPI5
#endif
#ifdef SPI6
		|| SPIx == SPI6
#endif
	) {
		APB_Frequency = HAL_RCC_GetPCLK2Freq();
	} else {
		APB_Frequency = HAL_RCC_GetPCLK1Freq();
	}
	
	/* Calculate prescaler value */
	/* Bits 5:3 in CR1 SPI registers are prescalers */
	/* 000 = 2, 001 = 4, 002 = 8, ..., 111 = 256 */
	for (i = 0; i < 8; i++) {
		if (APB_Frequency / (1 << (i + 1)) <= MAX_SPI_Frequency) {
			/* Bits for BP are 5:3 in CR1 register */
			return (i << 3);
		}
	}
	
	/* Use max prescaler possible */
	return SPI_BAUDRATEPRESCALER_256;
}

SPI_DataSize_t SPI_SetDataSize(SPI_TypeDef* SPIx, SPI_DataSize_t DataSize) {
	SPI_DataSize_t status;
	
	/* Disable SPI first */
	SPIx->CR1 &= ~SPI_CR1_SPE;
	
//#if defined(STM32F7xx)
	/* Read current SPI status */
	status = ((SPIx->CR2 & SPI_CR2_DS) == SPI_CR2_DS) ? SPI_DataSize_16b : SPI_DataSize_8b;
	
	/* Set proper value */
	if (DataSize == SPI_DataSize_16b) {
		/* Set bit for frame */
		SPIx->CR2 |= SPI_CR2_DS;
	} else {
		/* Clear bit for frame */
		SPIx->CR2 = (SPIx->CR2 & ~SPI_CR2_DS) | (SPI_CR2_DS_3);
	}
//#else
//	/* Read current SPI status */
//	status = (SPIx->CR1 & SPI_CR1_DFF) ? SPI_DataSize_16b : SPI_DataSize_8b;

//	/* Set proper value */
//	if (DataSize == SPI_DataSize_16b) {
//		/* Set bit for frame */
//		SPIx->CR1 |= SPI_CR1_DFF;
//	} else {
//		/* Clear bit for frame */
//		SPIx->CR1 &= ~SPI_CR1_DFF;
//	}
//#endif
	
	/* Enable SPI back */
	SPIx->CR1 |= SPI_CR1_SPE;
	
	/* Return status */
	return status;	
}

void SPI_SendMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint8_t* dataIn, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint8_t *)&SPIx->DR = *dataOut++;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Read data register */
		*dataIn++ = *(__IO uint8_t *)&SPIx->DR;
	}
}

void SPI_WriteMulti(SPI_TypeDef* SPIx, uint8_t* dataOut, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint8_t *)&SPIx->DR = *dataOut++;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Read data register */
		(void)*(__IO uint16_t *)&SPIx->DR;
	}
}

void SPI_ReadMulti(SPI_TypeDef* SPIx, uint8_t* dataIn, uint8_t dummy, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint8_t *)&SPIx->DR = dummy;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Save data to buffer */
		*dataIn++ = *(__IO uint8_t *)&SPIx->DR;
	}
}

void SPI_SendMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint16_t* dataIn, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint16_t *)&SPIx->DR = *dataOut++;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Read data register */
		*dataIn++ = *(__IO uint16_t *)&SPIx->DR;
	}
}

void SPI_WriteMulti16(SPI_TypeDef* SPIx, uint16_t* dataOut, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		*(__IO uint16_t *)&SPIx->DR = *dataOut++;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Read data register */
		(void)*(__IO uint16_t *)&SPIx->DR;
	}
}

void SPI_ReadMulti16(SPI_TypeDef* SPIx, uint16_t* dataIn, uint16_t dummy, uint32_t count) {
	/* Check if SPI is enabled */
	SPI_CHECK_ENABLED(SPIx);
	
	/* Wait for previous transmissions to complete if DMA TX enabled for SPI */
	SPI_WAIT_TX(SPIx);
	
	while (count--) {
		/* Wait busy */
		SPI_WAIT_TX(SPIx);
		
		/* Fill output buffer with data */
		SPIx->DR = dummy;
		
		/* Wait for SPI to end everything */
		SPI_WAIT_RX(SPIx);
		
		/* Save data to buffer */
		*dataIn++ = SPIx->DR;
	}
}

__weak void SPI_InitCustomPinsCallback(SPI_TypeDef* SPIx, uint16_t AlternateFunction) { 
	/* NOTE: This function Should not be modified, when the callback is needed,
           the SPI_InitCustomPinsCallback could be implemented in the user file
   */
}

/* Private functions */
static void SPIx_Init(SPI_TypeDef* SPIx, SPI_PinsPack_t pinspack, SPI_Mode_t SPI_Mode, uint16_t SPI_BaudRatePrescaler, uint16_t SPI_MasterSlave, uint16_t SPI_FirstBit) {
	SPI_HandleTypeDef SPIHandle;
	
	/* Save instance */
	SPIHandle.Instance = SPIx;
	
#ifdef SPI1	
	if (SPIx == SPI1) {
		/* Enable SPI clock */
		__HAL_RCC_SPI1_CLK_ENABLE();
		
		/* Init pins */
		SPI1_INT_InitPins(pinspack);
		
		/* Set options */
		SPIHandle.Init.DataSize = SPI1_DATASIZE;
	}
#endif
#ifdef SPI2
	if (SPIx == SPI2) {
		/* Enable SPI clock */
		__HAL_RCC_SPI2_CLK_ENABLE();
		
		/* Init pins */
		SPI2_INT_InitPins(pinspack);
		
		/* Set options */
		SPIHandle.Init.DataSize = SPI2_DATASIZE;
	}
#endif
#ifdef SPI3
	if (SPIx == SPI3) {
		/* Enable SPI clock */
		__HAL_RCC_SPI3_CLK_ENABLE();
		
		/* Init pins */
		SPI3_INT_InitPins(pinspack);
		
		/* Set options */
		SPIHandle.Init.DataSize = SPI3_DATASIZE;
	
	}
#endif
#ifdef SPI4
	if (SPIx == SPI4) {
		/* Enable SPI clock */
		__HAL_RCC_SPI4_CLK_ENABLE();
		
		/* Init pins */
		SPI4_INT_InitPins(pinspack);
		
		/* Set options */
		SPIHandle.Init.DataSize = SPI4_DATASIZE;
	}
#endif
#ifdef SPI5
	if (SPIx == SPI5) {
		/* Enable SPI clock */
		__HAL_RCC_SPI5_CLK_ENABLE();
		
		/* Init pins */
		SPI5_INT_InitPins(pinspack);
		
		/* Set options */
		SPIHandle.Init.DataSize = SPI5_DATASIZE;
	}
#endif
#ifdef SPI6
	if (SPIx == SPI6) {
		/* Enable SPI clock */
		__HAL_RCC_SPI6_CLK_ENABLE();
		
		/* Init pins */
		SPI6_INT_InitPins(pinspack);
		
		/* Set options */
		SPIHandle.Init.DataSize = SPI6_DATASIZE;
	}
#endif

	/* Fill SPI settings */
	SPIHandle.Init.BaudRatePrescaler = SPI_BaudRatePrescaler;
	SPIHandle.Init.FirstBit = SPI_FirstBit;
	SPIHandle.Init.Mode = SPI_MasterSlave;
	
	SPIHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPIHandle.Init.CRCPolynomial = 7;
	SPIHandle.Init.TIMode = SPI_TIMODE_DISABLE;
	SPIHandle.Init.NSS = SPI_NSS_SOFT;
	SPIHandle.Init.Direction = SPI_DIRECTION_2LINES;
	
#if defined(STM32F7xx)
	SPIHandle.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	SPIHandle.Init.CRCLength = SPI_CRC_LENGTH_8BIT;
#endif
	
	/* SPI mode */
	if (SPI_Mode == SPI_Mode_0) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
		SPIHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	} else if (SPI_Mode == SPI_Mode_1) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
		SPIHandle.Init.CLKPhase = SPI_PHASE_2EDGE;
	} else if (SPI_Mode == SPI_Mode_2) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_HIGH;
		SPIHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	} else if (SPI_Mode == SPI_Mode_3) {
		SPIHandle.Init.CLKPolarity = SPI_POLARITY_HIGH;
		SPIHandle.Init.CLKPhase = SPI_PHASE_2EDGE;
	}
	
	/* Disable first */
	__HAL_SPI_DISABLE(&SPIHandle);
	
	/* Init SPI */
	HAL_SPI_Init(&SPIHandle);
	
	/* Enable SPI */
	__HAL_SPI_ENABLE(&SPIHandle);
}

/* Private functions */
#ifdef SPI1
void SPI1_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOA)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI1);
	}
#endif
#if defined(GPIOB)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI1);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI1, GPIO_AFx_SPI1);
	}
}
#endif

#ifdef SPI2
void SPI2_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOB) && defined(GPIOC)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_10, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI2);
		GPIO_InitAlternate(GPIOC, GPIO_PIN_2 | GPIO_PIN_3, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI2);
	}
#endif
#if defined(GPIOB)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI2);
	}
#endif
#if defined(GPIOI)
	if (pinspack == SPI_PinsPack_3) {
		GPIO_InitAlternate(GPIOI, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI2);
	}
#endif
#if defined(GPIOB) && defined(GPIOI)
	if (pinspack == SPI_PinsPack_4) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI2);
		GPIO_InitAlternate(GPIOI, GPIO_PIN_1, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI2);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI2, GPIO_AFx_SPI2);
	}
}
#endif

#ifdef SPI3
void SPI3_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Enable SPI pins */
#if defined(GPIOB)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI3);
	}
#endif
#if defined(GPIOC)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOC, GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI3);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI3, GPIO_AFx_SPI3);
	}
}
#endif

#ifdef SPI4
void SPI4_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOE)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOE, GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI4);
	}
#endif
#if defined(GPIOE)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOE, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI4);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI4, GPIO_AFx_SPI4);
	}
}
#endif

#ifdef SPI5
void SPI5_INT_InitPins(SPI_PinsPack_t pinspack) {
	/* Init SPI pins */
#if defined(GPIOF)
	if (pinspack == SPI_PinsPack_1) {
		GPIO_InitAlternate(GPIOF, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI5);
	}
#endif
#if defined(GPIOF) && defined(GPIOH)
	if (pinspack == SPI_PinsPack_2) {
		GPIO_InitAlternate(GPIOF, GPIO_PIN_11, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI5);
		GPIO_InitAlternate(GPIOH, GPIO_PIN_6 | GPIO_PIN_7, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI5);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI5, GPIO_AFx_SPI5);
	}
}
#endif

#ifdef SPI6
void SPI6_INT_InitPins(SPI_PinsPack_t pinspack) {
#if defined(GPIOG)
	if (pinspack == SPI_PinsPack_1) {
		/* Init SPI pins */
		GPIO_InitAlternate(GPIOG, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14, GPIO_OType_PP, GPIO_PuPd_NOPULL, GPIO_Speed_High, GPIO_AFx_SPI6);
	}
#endif
	if (pinspack == SPI_PinsPack_Custom) {
		/* Call user function */
		SPI_InitCustomPinsCallback(SPI6, GPIO_AFx_SPI6);
	}
}
#endif

