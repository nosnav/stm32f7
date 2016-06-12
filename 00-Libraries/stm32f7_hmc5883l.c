#include "stm32f7_hmc5883l.h"

/* Private functions */
static uint8_t HMC5883_DataReady = 0;
static float HMC5883L_mGPerDigit;

HMC5883L_Result_t HMC5883L_Init(HMC5883L_t* HMC5883L, HMC5883L_Gain_t Gain, HMC5883L_OutputRate_t OutputRate) {
	uint8_t data[3];
	
	/* Init I2C */
	I2C_Init(HMC5883L_I2C, HMC5883L_I2C_PINSPACK, HMC5883L_I2C_CLOCK);
	
	/* Check if device is connected */
	if (!I2C_IsDeviceConnected(HMC5883L_I2C, HMC5883L_I2C_ADDR)) {
		/* Return error */
		return HMC5883L_Result_DeviceNotConnected;
	}
	
	/* Attach data ready pin to interrupt */
	if (EXTI_Attach(HMC5883L_DRDY_PORT, HMC5883L_DRDY_PIN, EXTI_Trigger_Falling) != EXTI_Result_Ok) {
		/* Return error */
		return HMC5883L_Result_Error;
	}
	
	/* Configure device */
	
	/* Register A */
	data[0] = 0x30 | (uint8_t) OutputRate;
	
	/* Register B */
	data[1] = (uint8_t) Gain;
	
	/* Mode register */
	data[2] = 0;
	
	/* Write data to device */
	I2C_WriteMulti(HMC5883L_I2C, HMC5883L_I2C_ADDR, HMC5883L_CONFA, data, 3);
	
	/* Read identification register */
	I2C_ReadMulti(HMC5883L_I2C, HMC5883L_I2C_ADDR, HMC5883L_IDA, HMC5883L->ID, 3);
	
	/* Store LSB value */
	switch (Gain) {
		case HMC5883L_Gain_0_88:
			HMC5883L_mGPerDigit = 0.073;
			break;
		case HMC5883L_Gain_1_3:
			HMC5883L_mGPerDigit = 0.92;
			break;
		case HMC5883L_Gain_1_9:
			HMC5883L_mGPerDigit = 1.22;
			break;
		case HMC5883L_Gain_2_5:
			HMC5883L_mGPerDigit = 1.52;
			break;
		case HMC5883L_Gain_4_0:
			HMC5883L_mGPerDigit = 2.27;
			break;
		case HMC5883L_Gain_4_7:
			HMC5883L_mGPerDigit = 2.56;
			break;
		case HMC5883L_Gain_5_6:
			HMC5883L_mGPerDigit = 3.03;
			break;
		case HMC5883L_Gain_8_1:
			HMC5883L_mGPerDigit = 4.35;
			break;
		default:
			HMC5883L_mGPerDigit = 1;
	}
	
	/* Return OK */
	return HMC5883L_Result_Ok;
}

HMC5883L_Result_t HMC5883L_DataReady(HMC5883L_t* HMC5883L) {
	/* Check data ready flag */
	if (HMC5883_DataReady) {
		/* Data ready */
		return HMC5883L_Result_Ok;
	}
	
	/* Data not ready */
	return HMC5883L_Result_Error;
}

HMC5883L_Result_t HMC5883L_Read(HMC5883L_t* HMC5883L) {
	uint8_t data[6];
	
	/* Check data ready flag */
	if (!HMC5883_DataReady) {
		/* Data not ready */
		return HMC5883L_Result_Error;
	}
	
	/* Read multi registers */
	I2C_ReadMulti(HMC5883L_I2C, HMC5883L_I2C_ADDR, HMC5883L_DATAXM, data, 6);
	
	/* Format data */
	HMC5883L->X = (int16_t)((uint8_t)data[0] << 8 | (uint8_t)data[1]);
	HMC5883L->Z = (int16_t)((uint8_t)data[2] << 8 | (uint8_t)data[3]);
	HMC5883L->Y = (int16_t)((uint8_t)data[4] << 8 | (uint8_t)data[5]);
	
	/* Calculate */
	HMC5883L->X = HMC5883L->X * ((float)HMC5883L_mGPerDigit);
	HMC5883L->Z = HMC5883L->Z * ((float)HMC5883L_mGPerDigit);
	HMC5883L->Y = HMC5883L->Y * ((float)HMC5883L_mGPerDigit);
	
	/* Clear data ready flag */
	HMC5883_DataReady = 0;
	
	/* Return OK */
	return HMC5883L_Result_Ok;
}

HMC5883L_Result_t HMC5883L_ProcessInterrupt(HMC5883L_t* HMC5883L) {
	/* Set data ready flag */
	HMC5883_DataReady = 1;
	
	/* Return OK */
	return HMC5883L_Result_Ok;
}
