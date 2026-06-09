#include "ser_fft.h"

/*

DDS产生30MHz单频信号，通过线缆传输后由STM32F407 ADC采集。
 ADC采样率：
    Fs = 1.95MHz
折叠频率计算: f_alias = |f_in - n·Fs|  
n  接近(f_in/Fs)的整数

     f_in = 30MHz
    Fs   = 1.95MHz

    n = round(30MHz / 1.95MHz)
       = 15

     f_alias
     = |30MHz - 15×1.95MHz|
     = 750kHz

 ADC实际采集到的是30MHz信号在750kHz处的折叠频谱。
 后续通过FFT分析750kHz频点幅值，即可获得30MHz信号经过线缆后的
 幅度变化。

 衰减计算：

     Att(dB) = 20·log10(Vout / Vin)

 其中：

     Vin  = 参考线幅值     Vout = 被测线幅值

DDS输出：400mV
直流偏置：1.0V

*/

static float fft_in[SER_FFT_SIZE];
static float fft_out[SER_FFT_SIZE];
static float peak_freq = 0.0f;
static float peak_mag = 0.0f;
float ref_mag = 65000;

static arm_rfft_fast_instance_f32 fft_s;


void SER_FFT_Init(void)
{
    arm_rfft_fast_init_f32(&fft_s,SER_FFT_SIZE);
}

void SER_FFT_Run(void)
{
    uint32_t i;
    uint16_t *adc;
    uint32_t len;
    adc = HAR_Cable_GetBuffer();
    len = HAR_Cable_GetLength();

    // uint16 -> float
    for(i=0;i<len;i++)
    {
        fft_in[i] = (float)adc[i];
    }

    //FFT 
    arm_rfft_fast_f32(&fft_s,fft_in,fft_out,0);
    peak_mag = 0.0f;
    peak_freq = 0.0f;

    for(i=1;i<len/2;i++)
    {
        float re;
        float im;
        float mag;

        re = fft_out[2*i];
        im = fft_out[2*i+1];

        mag = sqrtf(re*re + im*im);

			
			//全频段搜索,感觉没必要
        if(mag > peak_mag)
        {
            peak_mag = mag;

            peak_freq =((float)i * 1950000.0f)/ SER_FFT_SIZE;
        }
    }
}

float SER_FFT_GetPeakFreq(void)
{
    return peak_freq;
}

float SER_FFT_GetPeakMag(void)
{
    return peak_mag;
}

float SER_FFT_CalcAttenuation(float test_mag)
{
    if(test_mag <= 0.0f)
    {
        return 0.0f;
    }

    return 20.0f * log10f(SER_REF_MAG / test_mag);
}


