#ifndef __DRV_KEY_H
#define __DRV_KEY_H

#include "bsp_gpio.h"
#include "bsp_tim.h"

typedef enum
{
    KEY_NONE = 0,

    KEY1_CLICK,
    KEY2_CLICK,

    KEY1_LONG,
    KEY2_LONG

}KEY_EVENT_t;

extern volatile uint8_t key_1ms_flag; //1ms定时标志
KEY_EVENT_t KEY_GetEvent(void);


#endif

