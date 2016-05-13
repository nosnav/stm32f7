#include "stm32f7_touch_ft5336.h"

/* Status register */
#define FT5336_STATUS_REG        0x02

/* Start locations for reading pressed touches */
static uint8_t FT5336_DataRegs[] = {0x03, 0x09, 0x0F, 0x15, 0x1B};

/* Delay function */
static void FT_Delay(__IO uint32_t d) {
	while (d--);
}

uint8_t TOUCH_FT5336_Init(TOUCH_t* TS) {
	uint8_t deviceID;
	
	/* Set max values */
	TS->MaxX = 479;
	TS->MaxY = 271;
	
	/* Init I2C */
	I2C_Init(TOUCH_FT5336_I2C, TOUCH_FT5336_I2C_PP, 100000);
	
	/* Delay */
	FT_Delay(0xFFFFF);
	
	/* Check if device is connected */
	if (I2C_IsDeviceConnected(TOUCH_FT5336_I2C, TOUCH_FT5336_I2C_DEV) != I2C_Result_Ok) {
		/* Device is not connected */
		return 1;
	}
	
	/* Check device ID */
	I2C_Read(TOUCH_FT5336_I2C, TOUCH_FT5336_I2C_DEV, 0xA8, &deviceID);
	
	/* Check if OK */
	if (deviceID != 0x51) {
		/* Connected device is not FT5336 */
		return 2;
	}
	
	/* Return 0 = OK */
	return 0;
}

uint8_t TOUCH_FT5336_Read(TOUCH_t* TS) {
	uint8_t status;
	uint8_t i;
	uint8_t DataRead[4];
	
	/* Reset */
	TS->NumPresses = 0;
	
	/* Check status */
	I2C_Read(TOUCH_FT5336_I2C, TOUCH_FT5336_I2C_DEV, FT5336_STATUS_REG, &status);
	
	/* Mask status register */
	status &= 0x0F;
	
	/* Check if max detected more than max number of contacts */
	if (status > 5) {
		/* Return ERROR */
		return 1;
	}
	
	/* Save number of touches detected */
	TS->NumPresses = status;
	
	/* Read all positions */
	for (i = 0; i < TS->NumPresses; i++) {
		/* Read 4 bytes in a row */
		I2C_ReadMulti(TOUCH_FT5336_I2C, TOUCH_FT5336_I2C_DEV, FT5336_DataRegs[i], DataRead, 4);
		
		/* Format touches */
		TS->Y[i] = (DataRead[1]) | ((DataRead[0] & 0x0F) << 8);
		TS->X[i] = (DataRead[3]) | ((DataRead[2] & 0x0F) << 8);
	}
	
	/* Return OK */
	return 0;
}
