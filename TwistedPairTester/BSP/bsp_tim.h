#ifndef __BSP_TIM_H
#define __BSP_TIM_H

#include "main.h"
#include "tim.h"

#include "drv_key.h"
#include "hw_cable.h"

void BSP_TIM_Init(void);

uint32_t BSP_GetTick(void);
void BSP_Delay(uint16_t ms);

#endif
