#ifndef __SRV_SHORT_H
#define __SRV_SHORT_H

#include "bsp_gpio.h"
#include "bsp_tim.h"
#include "drv_relay.h"
#include "bsp_adc.h"

typedef struct
{
    BSP_GPIO_t gpio;
    BSP_ADC_t  adc;
    uint8_t    relay_id;
} HW_ChannelMap_t;



#endif

