#ifndef __SRV_LENGTH_H
#define __SRV_LENGTH_H

#include "hw_cable.h"
#include "drv_cable_test.h"


#define Res2 98928
#define Res1 51750

float Length_ConvertFreqToCap(int freq);
float Length_ConvertCapToMeter(float cap_total);

#endif

