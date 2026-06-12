#ifndef __SER_FFT_H
#define __SER_FFT_H

#include "main.h"
#include "math.h"
#include "arm_math.h"
#include "drv_adc_cable.h"

#define SER_FFT_SIZE    4096
//空载测量
#define SER_REF_MAG     58238.0f   

void SER_FFT_Init(void);
void SER_FFT_Run(void);
float SER_FFT_GetPeakFreq(void);
float SER_FFT_GetPeakMag(void);
float SER_FFT_CalcAttenuation(float test_mag);


#endif

