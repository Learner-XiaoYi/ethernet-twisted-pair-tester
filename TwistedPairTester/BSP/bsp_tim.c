#include "bsp_tim.h"

extern TIM_HandleTypeDef htim2;


static volatile uint32_t ms_tick = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        ms_tick++;
    }
}


void BSP_TIM_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim2);
}

uint32_t BSP_GetTick(void)
{
    return ms_tick;
}
