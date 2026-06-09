#include "drv_adc_cable.h"

/*
    初始化时统一配置为模拟输入模式。
    当前默认1号线（PA1）作为采样输入通道。
    启动采样后，ADC连续转换模拟信号，DMA自动将转换结果搬运到 cable_buf[] 缓冲区。
    cable_buf[] 为 FFT 原始采样缓冲区，用于存储固定长度的 ADC 数据。
    DMA采样完成后回调函数调用停止DMA采样，并置位标志委，通知上层采样任务已经完成。
    上层可通过 查询采样状态，当返回值为 1 时表示缓冲区数据已全部采集完成。
    随后获取采样数据地址，获取采样点数
*/

static BSP_GPIO_t cable_adc_pin[8] =
{
    {GPIOA, GPIO_PIN_1},
    {GPIOA, GPIO_PIN_2},
    {GPIOA, GPIO_PIN_3},
    {GPIOA, GPIO_PIN_4},
    {GPIOA, GPIO_PIN_5},
    {GPIOA, GPIO_PIN_6},
    {GPIOA, GPIO_PIN_7},
    {GPIOB, GPIO_PIN_0},
};

static BSP_ADC_t cable_adc[8] =
{
    {&hadc1, ADC_CHANNEL_1},
    {&hadc1, ADC_CHANNEL_2},
    {&hadc1, ADC_CHANNEL_3},
    {&hadc1, ADC_CHANNEL_4},
    {&hadc1, ADC_CHANNEL_5},
    {&hadc1, ADC_CHANNEL_6},
    {&hadc1, ADC_CHANNEL_7},
    {&hadc1, ADC_CHANNEL_8},
};


//FFT采样缓冲区 
static uint16_t cable_buf[HAR_CABLE_FFT_SIZE];
//DMA采样完成标志
static volatile uint8_t sample_ready = 0;

//线缆采样模块初始化,初始化采样状态标志
void HAR_Cable_Init(void)
{
    uint8_t i;

    sample_ready = 0;

    //ADC引脚配置为模拟输入 
    for(i = 0; i < 8; i++)
    {
        BSP_GPIO_Mode(cable_adc_pin[i],BSP_GPIO_MODE_ANALOG);
    }

    //通道1
    BSP_ADC_Config(&cable_adc[0],BSP_ADC_SAMPLE_FAST);
}

//ADC DMA采样完成回调,由HAL_ADC_ConvCpltCallback调用
void HAR_Cable_DMACompleteCallback(void)
{
    BSP_ADC_StopDMA(cable_adc[0].hadc);
    sample_ready = 1;
}

//开始采集线缆波形数据,启动ADC DMA连续采样
void HAR_Cable_StartSample(void)
{
    sample_ready = 0;

    BSP_ADC_StartDMA(cable_adc[0].hadc,cable_buf,HAR_CABLE_FFT_SIZE);
}

//查询采样是否完成
//0：采样中
//1：采样完成
uint8_t HAR_Cable_IsReady(void)
{
    return sample_ready;
}

//获取采样缓冲区地址,ADC采样数据首地址
uint16_t* HAR_Cable_GetBuffer(void)
{
    return cable_buf;
}

//获取采样点数,FFT采样长度
uint32_t HAR_Cable_GetLength(void)
{
    return HAR_CABLE_FFT_SIZE;
}
