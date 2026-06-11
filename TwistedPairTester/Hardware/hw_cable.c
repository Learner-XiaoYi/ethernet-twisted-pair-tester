#include "hw_cable.h"

/*
	长度测量，采用1s计数，取第二秒	
*/

//PD0
static BSP_GPIO_t length_meas_pin[] = {GPIOD, GPIO_PIN_1}; //长度测量线

//长度测量初始化
void Length_Init(void)
{
	BSP_GPIO_Mode(length_meas_pin[0],BSP_GPIO_MODE_INPUT_PULLDOWN);
}

uint8_t HW_Length_Task(void)
{
	uint8_t temp = 0;
	temp = BSP_GPIO_Read(length_meas_pin);
	return temp;
}

//1s计数
uint16_t HW_Length_GetCount(void)
{
	uint16_t temp = 0;
	uint16_t tick_last = 0;
	uint8_t cnt = 0;
	uint8_t cnt_last = 0;
	
	tick_last = BSP_GetTick();
	while(BSP_GetTick() - tick_last< 1000)
	{
		cnt = HW_Length_Task();
		if((cnt == 1) && (cnt_last == 0))
		{
			temp ++;
		}
		cnt_last = cnt;
	}
	return temp;
}

