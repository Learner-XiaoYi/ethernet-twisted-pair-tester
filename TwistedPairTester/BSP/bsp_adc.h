#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f4xx_hal.h"   // 根据你的芯片型号修改
#include <stdint.h>
#include "main.h"
#include "adc.h"

#include "drv_adc_cable.h"

typedef struct
{
    ADC_HandleTypeDef *hadc;  // HAL ADC句柄
    uint32_t channel;          // ADC通道号
} BSP_ADC_t;

typedef enum
{
    BSP_ADC_SAMPLE_FAST,
    BSP_ADC_SAMPLE_MIDDLE,
    BSP_ADC_SAMPLE_SLOW

} BSP_ADC_SampleTime_t;


uint16_t BSP_ADC_Read(BSP_ADC_t *adc);

uint16_t BSP_ADC_ReadAvg(BSP_ADC_t *adc, uint8_t times);

HAL_StatusTypeDef BSP_ADC_StartDMA(ADC_HandleTypeDef *hadc,uint16_t *buf,uint32_t len);

HAL_StatusTypeDef BSP_ADC_StopDMA(ADC_HandleTypeDef *hadc);
void BSP_ADC_Config(BSP_ADC_t *adc,BSP_ADC_SampleTime_t sample);


#endif
