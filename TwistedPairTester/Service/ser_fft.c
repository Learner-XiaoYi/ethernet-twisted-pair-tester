#include "ser_fft.h"

float32_t test_in[4] = {1.0f, 2.0f, 3.0f, 4.0f};
float32_t test_out[4];

void DSP_Test(void)
{
    arm_copy_f32(test_in, test_out, 4); // 向量复制，最简单的DSP函数
}

