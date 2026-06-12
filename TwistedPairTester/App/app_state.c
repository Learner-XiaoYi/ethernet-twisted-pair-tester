#include "app_state.h"


/* 双端测试 */
CableType_t g_cable_type;          //线缆类型
float g_attenuation_db;        //交流衰减(dB)
float g_dc_resistance;         //直流阻值(Ω)

/* 单端测试 */

float g_cable_length;          //线缆长度(cm)
uint8_t g_short_exist;         //是否短路
float g_short_location;        //短路位置(cm)

static float temp_frep;          //空载(cm)


APP_State_t g_app;

//状态机

void APP_State_Init(void)
{
    // 页面：初始单端界面
    g_app.page = APP_PAGE_CALIBRATION;
    // 整体测试状态：空闲
    g_app.test = APP_TEST_IDLE;
    // 双端子状态：空闲
    g_app.double_state = APP_DOUBLE_IDLE;
    // 单端子状态：空闲
    g_app.single_state = APP_SINGLE_IDLE;
}
void APP_State_Process(void)
{
    g_app.test = APP_TEST_IDLE;     //测量空闲
    switch (g_app.page)
    {
    case APP_PAGE_CALIBRATION:
        /* 校准界面 */
        {
            g_app.test = APP_TEST_IDLE;     //测量空闲
            if (key_1ms_flag)               //按键1ms标志
            {
                key_1ms_flag = 0;           // 清除标志
                KEY_Scan();                 // 执行一次扫描
            }
            if (event == KEY1_CLICK)        // 按键1短按
            {
                g_app.test = APP_TEST_RUNNING; //更新标签测量中
            }
            temp_frep = HW_Length_GetCount();
            if(temp_frep == -1)
            {
                g_app.test = APP_TEST_RUNNING; //更新标签测量中
            }
            else
            {
                g_cable_length = HW_Length_GetCount();
                g_app.test = APP_TEST_FINISH;  //更新标签，校准完成
            }
        }
        break;

    case APP_PAGE_SINGLE:
        /* 单端界面 */
        {

        }
        break;

    case APP_PAGE_DOUBLE:
        /* 双端界面 */
        {
            g_app.test = APP_TEST_IDLE;     //测量空闲
            if (key_1ms_flag)               //按键1ms标志
            {
                key_1ms_flag = 0;           // 清除标志
                KEY_Scan();                 // 执行一次扫描
            }
            if (event == KEY1_CLICK)        // 按键1短按
            {
                g_app.test = APP_TEST_RUNNING; //更新标签测量中
            }
        }
        break;

    default:
        break;
    }
}





