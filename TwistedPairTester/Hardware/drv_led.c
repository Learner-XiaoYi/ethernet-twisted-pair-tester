#include "drv_led.h"


static BSP_GPIO_t led_table[LED_NUM] =
{
    {GPIOF, GPIO_PIN_9},   // LED1
    {GPIOF, GPIO_PIN_10}   // LED2
};


void DRV_LED_Init(void)
{
	DRV_LED_Off(0);
	DRV_LED_Off(1);
}

void DRV_LED_On(uint8_t id)
{
	BSP_GPIO_Set(&led_table[id]);
}

void DRV_LED_Off(uint8_t id)
{
  BSP_GPIO_Reset(&led_table[id]);
}

void DRV_LED_Toggle(uint8_t id)
{
  BSP_GPIO_Toggle(&led_table[id]);
}

