#ifndef __DRV_ADC_CABLE_H
#define __DRV_ADC_CABLE_H

#include "main.h"
#include "bsp_gpio.h"
#include "bsp_adc.h"

#define HAR_CABLE_FFT_SIZE    4096

void DRV_ADC_Cable_Init(void);
void HAR_Cable_StartSample(void);
uint8_t HAR_Cable_IsReady(void);
uint16_t *HAR_Cable_GetBuffer(void);
uint32_t HAR_Cable_GetLength(void);
void HAR_Cable_DMACompleteCallback(void);

#endif

