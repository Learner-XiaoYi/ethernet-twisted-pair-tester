#include "drv_relay.h"

static const uint8_t relay_num = 9;

/*
继电器
*/

static BSP_GPIO_t relay_pin[relay_num] =
{
    {GPIOF, GPIO_PIN_0},
    {GPIOF, GPIO_PIN_1},
    {GPIOF, GPIO_PIN_2},
    {GPIOF, GPIO_PIN_3},
    {GPIOF, GPIO_PIN_4},
    {GPIOF, GPIO_PIN_5},
    {GPIOF, GPIO_PIN_6},
    {GPIOF, GPIO_PIN_7},
	{GPIOF, GPIO_PIN_8},
};

//默认全部关闭
void HW_Relay_Init(void)
{
    uint8_t i;

    for(i = 0; i < relay_num; i++)
    {
        BSP_GPIO_Mode(relay_pin[i], BSP_GPIO_MODE_OUTPUT_PP);

        BSP_GPIO_Write(&relay_pin[i], BSP_GPIO_LOW);
    }
}

//同一时间只有一个吸合
void HW_Relay_Select(uint8_t ch)
{
    uint8_t i;

    for(i = 0; i < relay_num; i++)
    {
        BSP_GPIO_Write(&relay_pin[i], BSP_GPIO_LOW);
    }

    if(ch < relay_num)
    {
        BSP_GPIO_Write(&relay_pin[ch], BSP_GPIO_HIGH);
    }
}

//打开
void HW_Relay_On(uint8_t ch)
{
    if(ch >= relay_num)
    {
        return;
    }

    BSP_GPIO_Write(&relay_pin[ch], BSP_GPIO_HIGH);
}

//关闭
void HW_Relay_Off(uint8_t ch)
{
    if(ch >= relay_num)
    {
        return;
    }

    BSP_GPIO_Write(&relay_pin[ch], BSP_GPIO_LOW);
}

//全部关闭
void HW_Relay_AllOff(void)
{
    uint8_t i;

    for(i = 0; i < relay_num; i++)
    {
        BSP_GPIO_Write(&relay_pin[i], BSP_GPIO_LOW);
    }
}
