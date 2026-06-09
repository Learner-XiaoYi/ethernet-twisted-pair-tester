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
    BSP_GPIO_MODE_INPUT ,
    BSP_GPIO_MODE_INPUT_PULLUP,
    BSP_GPIO_MODE_INPUT_PULLDOWN,

    BSP_GPIO_MODE_OUTPUT_PP,
    BSP_GPIO_MODE_OUTPUT_OD,
	
		BSP_GPIO_MODE_ANALOG,

} BSP_GPIO_Mode_t;

typedef enum
{
    BSP_GPIO_LOW,
    BSP_GPIO_HIGH
}BSP_GPIO_Level_t;



void BSP_GPIO_Init(void);
void BSP_GPIO_Mode(BSP_GPIO_t gpio, BSP_GPIO_Mode_t mode);
void BSP_GPIO_Set(BSP_GPIO_t *gpio);
uint8_t BSP_GPIO_Reset(BSP_GPIO_t *gpio);
void BSP_GPIO_Write(BSP_GPIO_t *gpio, BSP_GPIO_Level_t level);
void BSP_GPIO_Toggle(BSP_GPIO_t *gpio);
BSP_GPIO_Level_t  BSP_GPIO_Read(BSP_GPIO_t *gpio);

#endif
