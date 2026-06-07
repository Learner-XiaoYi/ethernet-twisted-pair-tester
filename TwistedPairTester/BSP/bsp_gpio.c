#include "bsp_gpio.h"

void BSP_GPIO_Init(void)
{
    MX_GPIO_Init();
}

void BSP_GPIO_Set(BSP_GPIO_t *gpio)
{
    HAL_GPIO_WritePin(gpio->port,
                      gpio->pin,
                      GPIO_PIN_SET);
}

void BSP_GPIO_Reset(BSP_GPIO_t *gpio)
{
    HAL_GPIO_WritePin(gpio->port,
                      gpio->pin,
                      GPIO_PIN_RESET);
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
