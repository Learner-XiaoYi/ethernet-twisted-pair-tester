#ifndef __DRV_LED_H
#define __DRV_LED_H

#include "bsp_gpio.h"
#include <stdint.h>

#define LED_NUM 2

#define LED1_On()   DRV_LED_On(0)
#define LED1_Off()  DRV_LED_Off(0)

#define LED2_On()   DRV_LED_On(1)
#define LED2_Off()  DRV_LED_Off(1)

void DRV_LED_Init(void);

void DRV_LED_On(uint8_t id);
void DRV_LED_Off(uint8_t id);
void DRV_LED_Toggle(uint8_t id);

#endif

