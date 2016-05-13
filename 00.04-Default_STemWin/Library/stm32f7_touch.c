#include "stm32f7_touch.h"
#include "string.h"
#include "stm32f7_touch_ft5336.h"

/* Static driver structure */
static TOUCH_DRIVER_t TouchDriver;

TOUCH_Result_t TOUCH_Init(TOUCH_DRIVER_t* Driver, TOUCH_t* TS) {
	/* Set memory to zero */
	memset((uint8_t *)&TouchDriver, 0, sizeof(TOUCH_DRIVER_t));

	/* Check for default driver */
	if (Driver != NULL) {
		TouchDriver.Init = Driver->Init;
		TouchDriver.Read = Driver->Read;
	} else {
		/* Set default values */
		TouchDriver.Init = TOUCH_FT5336_Init;
		TouchDriver.Read = TOUCH_FT5336_Read;
	}
	
	/* Try to INIT */
	if (TouchDriver.Init(TS) == 0) {
		/* Return OK */
		return TOUCH_Result_Ok;
	}
	
	/* Return ERROR */
	return TOUCH_Result_Error;
}

uint8_t TOUCH_Read(TOUCH_t* TS) {
	uint8_t status, i;
	uint16_t tmp;
	
	/* Read touch values from sensor */
	status = TouchDriver.Read(TS);
	
	/* Return touch status */
	if (status) {
		return status;
	}
	
	/* Check for orientations */
	if (TS->Orientation == 0) {
		/* Rotate all X and Y values */
		for (i = 0; i < TS->NumPresses; i++) {
			TS->X[i] = TS->MaxX - TS->X[i];
			TS->Y[i] = TS->MaxY - TS->Y[i];
		}
	}
	if (TS->Orientation == 2) {
		/* Rotate all X and Y values */
		for (i = 0; i < TS->NumPresses; i++) {
			tmp = TS->X[i];
			TS->X[i] = TS->MaxY - TS->Y[i];
			TS->Y[i] = tmp;
		}
	}
	if (TS->Orientation == 3) {
		/* Rotate all X and Y values */
		for (i = 0; i < TS->NumPresses; i++) {
			tmp = TS->X[i];
			TS->X[i] = TS->Y[i];
			TS->Y[i] = TS->MaxX - tmp;
		}
	}
	
	/* Return OK */
	return 0;
}
