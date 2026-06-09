#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f4xx_hal.h"   // 根据你的芯片型号修改
#include <stdint.h>
#include "main.h"
#include "adc.h"

typedef struct
{
    ADC_HandleTypeDef *hadc;  // HAL ADC句柄
    uint32_t channel;          // ADC通道号
} BSP_ADC_t;


/**
 * @brief  读取ADC单次值
 * @param  adc: BSP_ADC_t指针
 * @retval ADC计数值 (例如 12bit: 0~4095)
 */
uint16_t BSP_ADC_Read(BSP_ADC_t *adc);

uint16_t BSP_ADC_ReadAvg(BSP_ADC_t *adc, uint8_t times);

HAL_StatusTypeDef BSP_ADC_StartDMA(ADC_HandleTypeDef *hadc,uint16_t *buf,uint32_t len);

HAL_StatusTypeDef BSP_ADC_StopDMA(ADC_HandleTypeDef *hadc);

#endif
