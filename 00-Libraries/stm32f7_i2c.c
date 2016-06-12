#include "stm32f7_i2c.h"

/* Timeout value */
#define I2C_TIMEOUT_VALUE              1000

/* Handle values for I2C */
#ifdef I2C1
static I2C_HandleTypeDef I2C1Handle = {I2C1};
#endif
#ifdef I2C2
static I2C_HandleTypeDef I2C2Handle = {I2C2};
#endif
#ifdef I2C3
static I2C_HandleTypeDef I2C3Handle = {I2C3};
#endif
#ifdef I2C4
static I2C_HandleTypeDef I2C4Handle = {I2C4};
#endif

/* Private functions */
#ifdef I2C1
static void I2C1_INT_InitPins(I2C_PinsPack_t pinspack);
#endif
#ifdef I2C2
static void I2C2_INT_InitPins(I2C_PinsPack_t pinspack);
#endif
#ifdef I2C3
static void I2C3_INT_InitPins(I2C_PinsPack_t pinspack);
#endif
#ifdef I2C4
static void I2C4_INT_InitPins(I2C_PinsPack_t pinspack);
#endif

I2C_HandleTypeDef* I2C_GetHandle(I2C_TypeDef* I2Cx) {
#ifdef I2C1
	if (I2Cx == I2C1) {
		return &I2C1Handle;
	}
#endif
#ifdef I2C2
	if (I2Cx == I2C2) {
		return &I2C2Handle;
	}
#endif
#ifdef I2C3
	if (I2Cx == I2C3) {
		return &I2C3Handle;
	}
#endif
#ifdef I2C4
	if (I2Cx == I2C4) {
		return &I2C4Handle;
	}
#endif
	
	/* Return invalid */
	return 0;
}

static void I2C_FillSettings(I2C_HandleTypeDef* Handle, uint32_t clockSpeed) {
	uint32_t I2C_Timing;
	
	/* Future */
	if (clockSpeed >= 3400000) {
		/* 100kHz @ 50MHz APB clock */
		I2C_Timing = 0x40912732;
	} else if (clockSpeed >= 1000000) {
		/* 100kHz @ 50MHz APB clock */
		I2C_Timing = 0x40912732;
	} else if (clockSpeed >= 400000) {
		/* 100kHz @ 50MHz APB clock */
		I2C_Timing = 0x40912732;
	} else {	
		/* 100kHz @ 50MHz APB clock */
		I2C_Timing = 0x40912732;
	}

	/* Fill settings */
	Handle->Init.OwnAddress2 = 0x00;
	Handle->Init.OwnAddress1 = 0x00;
	Handle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	Handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	Handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	Handle->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	Handle->Init.Timing = I2C_Timing;
}

I2C_Result_t I2C_Init(I2C_TypeDef* I2Cx, I2C_PinsPack_t pinspack, uint32_t clockSpeed) {	
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Fill instance value */
	Handle->Instance = I2Cx;
	
#ifdef I2C1
	if (I2Cx == I2C1) {
		/* Enable clock */
		__HAL_RCC_I2C1_CLK_ENABLE();
		
		/* Enable pins */
		I2C1_INT_InitPins(pinspack);
	}
#endif
#ifdef I2C2	
	if (I2Cx == I2C2) {
		/* Enable clock */
		__HAL_RCC_I2C2_CLK_ENABLE();
		
		/* Enable pins */
		I2C2_INT_InitPins(pinspack);
	} 
#endif
#ifdef I2C3
	if (I2Cx == I2C3) {
		/* Enable clock */
		__HAL_RCC_I2C3_CLK_ENABLE();
		
		/* Enable pins */
		I2C3_INT_InitPins(pinspack);
	}
#endif
#ifdef I2C4
	if (I2Cx == I2C4) {
		/* Enable clock */
		__HAL_RCC_I2C4_CLK_ENABLE();
		
		/* Enable pins */
		I2C4_INT_InitPins(pinspack);
	}
#endif
	
	/* Fill settings */
	I2C_FillSettings(Handle, clockSpeed);
	
	/* Initialize I2C */
	HAL_I2C_Init(Handle);
		
	/* Enable analog filter */
#if defined(I2C_ANALOGFILTER_ENABLE)
	HAL_I2CEx_ConfigAnalogFilter(Handle, I2C_ANALOGFILTER_ENABLE);
#endif
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_Read(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t* data) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Send address */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, &register_address, 1, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Receive multiple byte */
	if (HAL_I2C_Master_Receive(Handle, device_address, data, 1, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_ReadMulti(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t* data, uint16_t count) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Send register address */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, &register_address, 1, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Receive multiple byte */
	if (HAL_I2C_Master_Receive(Handle, device_address, data, count, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_ReadNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t* data) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);

	/* Receive single byte without specifying  */
	if (HAL_I2C_Master_Receive(Handle, (uint16_t)device_address, data, 1, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_ReadMultiNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t* data, uint16_t count) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);

	/* Receive multi bytes without specifying  */
	if (HAL_I2C_Master_Receive(Handle, (uint16_t)device_address, data, count, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_Write(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t register_address, uint8_t data) {
	uint8_t d[2];
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
		
	/* Format array to send */
	d[0] = register_address;
	d[1] = data;
	
	/* Try to transmit via I2C */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, (uint8_t *)d, 2, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	} 
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_WriteMulti(I2C_TypeDef* I2Cx, uint8_t device_address, uint16_t register_address, uint8_t* data, uint16_t count) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);

	/* Try to transmit via I2C */
	if (HAL_I2C_Mem_Write(Handle, device_address, register_address, register_address > 0xFF ? I2C_MEMADD_SIZE_16BIT : I2C_MEMADD_SIZE_8BIT, data, count, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_WriteNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t data) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Try to transmit via I2C */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, &data, 1, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	} 
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_WriteMultiNoRegister(I2C_TypeDef* I2Cx, uint8_t device_address, uint8_t* data, uint16_t count) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Try to transmit via I2C */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, data, count, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	} 
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_Write16(I2C_TypeDef* I2Cx, uint8_t device_address, uint16_t register_address, uint8_t data) {
	uint8_t d[3];
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
		
	/* Format array to send */
	d[0] = (register_address >> 8) & 0xFF; /* High byte */
	d[1] = (register_address) & 0xFF;      /* Low byte */
	d[2] = data;                           /* Data byte */
	
	/* Try to transmit via I2C */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, (uint8_t *)d, 3, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	} 
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_Read16(I2C_TypeDef* I2Cx, uint8_t device_address, uint16_t register_address, uint8_t* data) {
	uint8_t adr[2];
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Format I2C address */
	adr[0] = (register_address >> 8) & 0xFF; /* High byte */
	adr[1] = (register_address) & 0xFF;      /* Low byte */
	
	/* Send address */
	if (HAL_I2C_Master_Transmit(Handle, (uint16_t)device_address, adr, 2, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Receive multiple byte */
	if (HAL_I2C_Master_Receive(Handle, device_address, data, 1, 1000) != HAL_OK) {
		/* Check error */
		if (HAL_I2C_GetError(Handle) != HAL_I2C_ERROR_AF) {
			
		}
		
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_IsDeviceConnected(I2C_TypeDef* I2Cx, uint8_t device_address) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Check if device is ready for communication */
	if (HAL_I2C_IsDeviceReady(Handle, device_address, 2, 5) != HAL_OK) {
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

I2C_Result_t I2C_WriteReadRepeatedStart(
	I2C_TypeDef* I2Cx,
	uint8_t device_address, 
	uint8_t write_register_address, 
	uint8_t* write_data,
	uint16_t write_count, 
	uint8_t read_register_address, 
	uint8_t* read_data,
	uint16_t read_count
) {
	I2C_HandleTypeDef* Handle = I2C_GetHandle(I2Cx);
	
	/* Write command to device */
	if (HAL_I2C_Mem_Write(Handle, device_address, write_register_address, I2C_MEMADD_SIZE_8BIT, write_data, write_count, 1000) != HAL_OK) {
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Read data from controller */
	if (HAL_I2C_Mem_Read(Handle, device_address, read_register_address, I2C_MEMADD_SIZE_8BIT, read_data, read_count, 1000) != HAL_OK) {
		/* Return error */
		return I2C_Result_Error;
	}
	
	/* Return OK */
	return I2C_Result_Ok;
}

__weak void I2C_InitCustomPinsCallback(I2C_TypeDef* I2Cx, uint16_t AlternateFunction) {
	/* Custom user function. */
	/* In case user needs functionality for custom pins, this function should be declared outside this library */
}

/* Private functions */
#ifdef I2C1
static void I2C1_INT_InitPins(I2C_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOB)
	if (pinspack == I2C_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_6 | GPIO_PIN_7, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C1);
	}
#endif
#if defined(GPIOB)
	if (pinspack == I2C_PinsPack_2) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_8 | GPIO_PIN_9, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C1);
	}
#endif
#if defined(GPIOB)
	if (pinspack == I2C_PinsPack_3) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_6 | GPIO_PIN_9, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C1);
	}
#endif
	if (pinspack == I2C_PinsPack_Custom) {
		/* Init custom pins, callback function */
		I2C_InitCustomPinsCallback(I2C1, GPIO_AF4_I2C1);
	}
}
#endif
#ifdef I2C2
static void I2C2_INT_InitPins(I2C_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOB)
	if (pinspack == I2C_PinsPack_1) {
		GPIO_InitAlternate(GPIOB, GPIO_PIN_10 | GPIO_PIN_11, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C2);
	}
#endif
#if defined(GPIOF)
	if (pinspack == I2C_PinsPack_2) {
		GPIO_InitAlternate(GPIOF, GPIO_PIN_0 | GPIO_PIN_1, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C2);
	}
#endif
#if defined(GPIOH)
	if (pinspack == I2C_PinsPack_3) {
		GPIO_InitAlternate(GPIOH, GPIO_PIN_4 | GPIO_PIN_5, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C2);
	}
#endif
	if (pinspack == I2C_PinsPack_Custom) {
		/* Init custom pins, callback function */
		I2C_InitCustomPinsCallback(I2C2, GPIO_AF4_I2C2);
	}
}
#endif
#ifdef I2C3
static void I2C3_INT_InitPins(I2C_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOA) && defined(GPIOC)
	if (pinspack == I2C_PinsPack_1) {
		GPIO_InitAlternate(GPIOA, GPIO_PIN_8, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C3);
		GPIO_InitAlternate(GPIOC, GPIO_PIN_9, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C3);
	}
#endif
#if defined(GPIOH)
	if (pinspack == I2C_PinsPack_2) {
		GPIO_InitAlternate(GPIOH, GPIO_PIN_7 | GPIO_PIN_8, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C3);
	}
#endif
	if (pinspack == I2C_PinsPack_Custom) {
		/* Init custom pins, callback function */
		I2C_InitCustomPinsCallback(I2C3, GPIO_AF4_I2C3);
	}
}
#endif
#ifdef I2C4
static void I2C4_INT_InitPins(I2C_PinsPack_t pinspack) {
	/* Init pins */
#if defined(GPIOD)
	if (pinspack == I2C_PinsPack_1) {
		GPIO_InitAlternate(GPIOD, GPIO_PIN_12 | GPIO_PIN_13, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C4);
	}
#endif
#if defined(GPIOF)
	if (pinspack == I2C_PinsPack_2) {
		GPIO_InitAlternate(GPIOF, GPIO_PIN_1 | GPIO_PIN_0, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C4);
	}
	if (pinspack == I2C_PinsPack_3) {
		GPIO_InitAlternate(GPIOF, GPIO_PIN_14 | GPIO_PIN_15, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C4);
	}
#endif
#if defined(GPIOH)
	if (pinspack == I2C_PinsPack_4) {
		GPIO_InitAlternate(GPIOH, GPIO_PIN_11 | GPIO_PIN_12, GPIO_OType_OD, GPIO_PuPd_UP, GPIO_Speed_Medium, GPIO_AF4_I2C4);
	}
#endif
	/* Init pins */
	if (pinspack == I2C_PinsPack_Custom) {
		/* Init custom pins, callback function */
		I2C_InitCustomPinsCallback(I2C3, GPIO_AF4_I2C4);
	}
}
#endif
