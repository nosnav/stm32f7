#ifndef __MADGWICK_AHRS_H
#define __MADGWICK_AHRS_H
#ifdef __cplusplus
 extern "C" {
#endif
	 
#include <math.h>
	 
extern volatile float beta;				// algorithm gain
extern volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

//---------------------------------------------------------------------------------------------------
// Function declarations

void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);


#ifdef __cplusplus
}
#endif

#endif /* __MADGWICK_AHRS_H */
