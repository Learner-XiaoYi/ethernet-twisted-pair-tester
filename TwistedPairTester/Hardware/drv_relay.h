#ifndef __DRV_RELAY_H
#define __DRV_RELAY_H

#include "bsp_gpio.h"

void HW_Relay_Init(void);

//同一时间只有一个吸合
void HW_Relay_Select(uint8_t ch);

//打开
void HW_Relay_On(uint8_t ch);
//关闭
void HW_Relay_Off(uint8_t ch);
//全部关闭
void HW_Relay_AllOff(void);


#endif

