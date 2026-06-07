#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "main.h"
#include "gpio.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
}BSP_GPIO_t;

typedef enum
{
    BSP_GPIO_LOW = 0,
    BSP_GPIO_HIGH
}BSP_GPIO_Level_t;

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} gpio_level_t;


void BSP_GPIO_Init(void);
void BSP_GPIO_Set(BSP_GPIO_t *gpio);
uint8_t BSP_GPIO_Reset(BSP_GPIO_t *gpio);
void BSP_GPIO_Write(BSP_GPIO_t *gpio, gpio_level_t level);
void BSP_GPIO_Toggle(BSP_GPIO_t *gpio);
BSP_GPIO_Level_t  BSP_GPIO_Read(BSP_GPIO_t *gpio);

#endif
