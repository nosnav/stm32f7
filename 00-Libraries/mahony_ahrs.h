#ifndef __MAHONY_AHRS_H
#define __MAHONY_AHRS_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <math.h>	 
extern volatile float twoKp;			// 2 * proportional gain (Kp)
extern volatile float twoKi;			// 2 * integral gain (Ki)
extern volatile float q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame

//---------------------------------------------------------------------------------------------------
// Function declarations

void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);



#ifdef __cplusplus
}
#endif

#endif /* __MAHONY_AHRS_H */
