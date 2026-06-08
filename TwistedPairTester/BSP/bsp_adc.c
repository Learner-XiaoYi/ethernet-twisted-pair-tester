#include "bsp_adc.h"

// 单次读取
uint16_t BSP_ADC_Read(BSP_ADC_t *adc)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    // 配置通道
    sConfig.Channel = adc->channel;
    sConfig.Rank = 1; // 对应 ADC_REGULAR_RANK_1，
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES; // 对应 HAL 宏，确保HAL版本支持


    HAL_ADC_ConfigChannel(adc->hadc, &sConfig);

    // 启动ADC
    HAL_ADC_Start(adc->hadc);

    // 等待转换完成，超时100ms
    HAL_ADC_PollForConversion(adc->hadc, 100);

    // 获取值
    return HAL_ADC_GetValue(adc->hadc);
}

// 多次采样平均
uint16_t BSP_ADC_ReadAvg(BSP_ADC_t *adc, uint8_t times)
{
    uint32_t sum = 0;

    for(uint8_t i = 0; i < times; i++)
    {
        sum += BSP_ADC_Read(adc);
    }

    return (uint16_t)(sum / times);
}

