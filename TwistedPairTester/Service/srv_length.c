#include "srv_length.h"


const float CnumTemp_SFTP = 53.0f;
const float CnumTemp_UTP = 65.0;


//频率转电容  Ctemp = (1 / (0.693147 * (Res1 + 2 * Res2) * FreqNum)) * 1000000000000;
//freq，校准频率
float Length_ConvertFreqToCap(int freq);
{
	int FreqNum = 0;
	float Ctemp = 0;
	FreqNum = HW_Length_GetCount();
	Ctemp = 1 / (0.693147 * (Res1 + 2 * Res2) * (FreqNum - freq)) * 1000000000000;
	return Ctemp;
}

//电容转长度  LongNum = (Ctemp - Cbegin) / result_float;
float Length_ConvertCapToMeter(float cap_total)
{
    float length = 0.0f;
    switch (cable)
    {
        case CABLE_UTP:
            length = (cap_total) / CnumTemp_UTP;
            break;
        case CABLE_SFTP:
            length = (cap_total) / CnumTemp_SFTP;
            break;
    }
    return length;
}

