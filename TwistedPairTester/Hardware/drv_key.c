#include "drv_key.h"


static BSP_GPIO_t key_table[2] =
{
    {GPIOE, GPIO_PIN_4},
    {GPIOE, GPIO_PIN_3}
};

static uint16_t key_cnt[2]; 						//分别记录两个按键的持续按下计时
static uint8_t key_state[2];						//分别记录两个按键的状态

static KEY_EVENT_t key_event = KEY_NONE;

uint8_t KEY_Read(uint8_t id)
{
    return BSP_GPIO_Read(&key_table[id]);
}

volatile uint8_t key_1ms_flag = 0; //1ms定时标志
void KEY_Scan(void)
{
		//每次扫描遍历按键
    for(uint8_t i=0;i<2;i++)  
    {
        if(KEY_Read(i) == 0) //读取按键 i 的当前电平低电平有效
        {
            key_cnt[i]++;

            // 短按 连续按下 20ms，并且该按键的状态为 0
            if(key_cnt[i] == 20 && key_state[i] == 0)
            {
                key_event = (i==0)?KEY1_CLICK:KEY2_CLICK;
                key_state[i] = 1;  //将状态置 1，该按键的短按事件已经产生
            }

            // 长按 判断是否达到长按条件
            if(key_cnt[i] == 1000 && key_state[i] < 2)
            {
                key_event = (i==0)?KEY1_LONG:KEY2_LONG;
                key_state[i] = 2;
            }
        }
        else
        {
            key_cnt[i] = 0;    //按键计数清0
            key_state[i] = 0;  //按键状态清0
        }
    }
}

KEY_EVENT_t KEY_GetEvent(void)
{
    KEY_EVENT_t tmp = key_event;
    key_event = KEY_NONE;
    return tmp;
}


