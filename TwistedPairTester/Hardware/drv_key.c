#include "drv_key.h"

//下拉输入

const static uint8_t key_cont = 3;                 //按键数目

static BSP_GPIO_t key_table[key_cont] =
{
    {GPIOE, GPIO_PIN_4},
    {GPIOE, GPIO_PIN_3},
    {GPIOE, GPIO_PIN_2}
};

static uint16_t key_cnt[key_cont]; 						//分别记录按键的持续按下计时
static uint8_t key_state[key_cont];						//分别记录按键的状态

static KEY_EVENT_t key_event = KEY_NONE;

uint8_t KEY_Read(uint8_t id)
{
    return BSP_GPIO_Read(&key_table[id]);
}

volatile uint8_t key_1ms_flag = 0; //1ms定时标志
void KEY_Scan(void)
{
    for(uint8_t i = 0; i < key_cont; i++)
    {
        if(KEY_Read(i) == BSP_GPIO_LOW)   // 按下
        {
            if(key_cnt[i] < 1000)
                key_cnt[i]++;

            // 短按
            if(key_cnt[i] == 20 && key_state[i] == 0)
            {
                key_event = (i == 0) ? KEY1_CLICK : KEY2_CLICK;
                key_state[i] = 1;
            }

            // 长按
            if(key_cnt[i] == 1000 && key_state[i] < 2)
            {
                key_event = (i == 0) ? KEY1_LONG : KEY2_LONG;
                key_state[i] = 2;
            }
        }
        else  // 松开
        {
            key_cnt[i] = 0;
            key_state[i] = 0;
        }
    }
}

KEY_EVENT_t KEY_GetEvent(void)
{
    KEY_EVENT_t tmp = key_event;
    key_event = KEY_NONE;
    return tmp;
}


