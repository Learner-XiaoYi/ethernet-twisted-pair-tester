#ifndef __HW_CABLE_H
#define __HW_CABLE_H

#include "bsp_gpio.h"
#include "bsp_tim.h"

extern uint32_t lin_connst;//计数2s

void Length_Init(void);
int HW_Length_GetCount(void);

#endif

