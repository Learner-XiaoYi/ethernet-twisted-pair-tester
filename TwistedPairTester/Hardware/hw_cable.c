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
uint32_t lin_connst = 0;
int HW_Length_GetCount(void)
{
	static uint8_t connt = 0; 
	static uint16_t temp = 0;
	static uint16_t tick_last = 0;
	static uint8_t cnt = 0;        //当前电平值
	static uint8_t cnt_last = 0;  //上次电平值
	
	tick_last = BSP_GetTick();
	if(lin_connst < 1000)
	{
		cnt = HW_Length_Task();
		if((cnt == 1) && (cnt_last == 0))
		{
			temp ++;
		}
		cnt_last = cnt;
		return -1;
	}
	else if(connt < 2)
	{
		connt ++;
//		lin_connst = 0;
		return -1;
	}
	else
	{
		connt = 0;
		lin_connst = 0;//清0
		return  temp;
	}
}

