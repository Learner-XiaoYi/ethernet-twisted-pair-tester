#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "main.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
}BSP_GPIO_t;

void BSP_GPIO_Set(BSP_GPIO_t *gpio);
void BSP_GPIO_Reset(BSP_GPIO_t *gpio);
void BSP_GPIO_Toggle(BSP_GPIO_t *gpio);
GPIO_PinState BSP_GPIO_Read(BSP_GPIO_t *gpio);

#endif

