#include "bsp_tim.h"

extern TIM_HandleTypeDef htim2;


static volatile uint32_t ms_tick = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        ms_tick++;//计数
        /*按键标志位*/
        key_1ms_flag = 1; //1ms定时标志
        /*频率计数*/
        lin_connst ++;
    }
}

void BSP_Delay(uint16_t ms)
{
	HAL_Delay(ms);
}


void BSP_TIM_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim2);
}

uint32_t BSP_GetTick(void)
{
    return ms_tick;
}


