#include "bsp_gpio.h"

//单次
void BSP_GPIO_Init(void)
{
    MX_GPIO_Init();
}

//重复
void BSP_GPIO_Mode(BSP_GPIO_t gpio, BSP_GPIO_Mode_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = gpio.pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    switch(mode)
    {
        case BSP_GPIO_MODE_INPUT:   					//浮空输入
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;

        case BSP_GPIO_MODE_INPUT_PULLUP:     //上拉输入
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            break;

        case BSP_GPIO_MODE_INPUT_PULLDOWN:   //下拉输入
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = GPIO_PULLDOWN;
            break;

        case BSP_GPIO_MODE_OUTPUT_PP:         //推挽输出
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;

        case BSP_GPIO_MODE_OUTPUT_OD:         //开漏输出
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;
				
				case BSP_GPIO_MODE_ANALOG:           //模拟输入
						GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
						GPIO_InitStruct.Pull = GPIO_NOPULL;
						break;

        default:
            return;
    }

    HAL_GPIO_Init(gpio.port, &GPIO_InitStruct);
}


void BSP_GPIO_Set(BSP_GPIO_t *gpio)
{
    HAL_GPIO_WritePin(gpio->port,
                      gpio->pin,
                      GPIO_PIN_SET);
}

uint8_t BSP_GPIO_Reset(BSP_GPIO_t *gpio)
{
    HAL_GPIO_WritePin(gpio->port,
                      gpio->pin,
                      GPIO_PIN_RESET);
}

void BSP_GPIO_Write(BSP_GPIO_t *gpio, BSP_GPIO_Level_t level)
{
    HAL_GPIO_WritePin(
        gpio->port,
        gpio->pin,
        (level == BSP_GPIO_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET
    );
}

void BSP_GPIO_Toggle(BSP_GPIO_t *gpio)
{
    HAL_GPIO_TogglePin(gpio->port,
                       gpio->pin);
}

BSP_GPIO_Level_t BSP_GPIO_Read(BSP_GPIO_t *gpio)
{
    if(HAL_GPIO_ReadPin(gpio->port, gpio->pin) == GPIO_PIN_SET)
        return BSP_GPIO_HIGH;
    else
        return BSP_GPIO_LOW;
}
