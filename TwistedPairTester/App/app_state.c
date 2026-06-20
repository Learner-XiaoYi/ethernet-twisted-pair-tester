#include "app_state.h"


/* 双端测试 */
CableType_t g_cable_type;          //线缆类型
uint8_t g_line_sequence = 2;        //线序
uint8_t g_line_k = 2;           //开路检测
float g_attenuation_db;        //交流衰减(dB)
float g_dc_resistance;         //直流阻值(Ω)
float att;                      //衰减
/* 单端测试 */
float g_c;                     //电容
float g_cable_length;          //线缆长度(cm)
uint8_t g_short_exist = 0;         //是否短路

float g_short_location;        //短路位置(cm)

static int temp_frep;          //空载(cm)
static int frep;               //实际频率


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
//    // 单端子状态：空闲
//    g_app.single_state = APP_SINGLE_IDLE;
}
void APP_State_Process(void)
{
    g_app.test = APP_TEST_IDLE;     //测量空闲
    KEY_EVENT_t event = KEY_NONE;
    if (key_1ms_flag)               //按键1ms标志
    {
        key_1ms_flag = 0;           // 清除标志
        KEY_Scan();
         event = KEY_GetEvent();               // 执行一次扫描
    }
    static int i = 0;
    if (event == KEY2_CLICK)        // 按键2短按
    {
        i = (i++ % 3);
        if(i == 0) g_app.page = APP_PAGE_CALIBRATION;
        if(i == 1) g_app.page = APP_PAGE_DOUBLE;
        if(i == 2) g_app.page = APP_PAGE_SINGLE;
    }


    switch (g_app.page)
    {
    case APP_PAGE_CALIBRATION:
        /* 校准界面 */
        {
            g_app.test = APP_TEST_IDLE;     //测量空闲
            if (key_1ms_flag)               //按键1ms标志
            {
                key_1ms_flag = 0;           // 清除标志
                KEY_Scan();
                event = KEY_GetEvent();               // 执行一次扫描
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
                temp_frep = HW_Length_GetCount();  //空载测量
                g_app.test = APP_TEST_FINISH;  //更新标签，校准完成
            }
        }
        break;

    case APP_PAGE_SINGLE:
        /* 单端界面 */
        {
            g_app.test = APP_TEST_IDLE; //测量空闲
            g_app.test = APP_TEST_IDLE;     //测量空闲
            if (key_1ms_flag)               //按键1ms标志
            {
                key_1ms_flag = 0;           // 清除标志
                KEY_Scan();
                event = KEY_GetEvent();               // 执行一次扫描
            }
            if (event == KEY1_CLICK)        // 按键1短按
            {
                g_app.test = APP_TEST_RUNNING; //更新标签测量中
            }
            switch (g_app.test)
            {
                case APP_TEST_RUNNING:
                {
                    //长度测量
                    temp_frep = HW_Length_GetCount();
                    if(temp_frep == -1)
                    {
                        g_app.test = APP_TEST_RUNNING; //更新标签测量中
                    }
                    else
                    {
                        frep = Length_ConvertFreqToCap(temp_frep); //实际频率
                        g_c = Length_ConvertCapToMeter(frep); //频率转电容
                        g_cable_length = Length_ConvertCapToMeter(g_cable_length); //电容转长度
                    }

                    //短路引脚判断
                    uint8_t short_ch = 0xFF;
                    HW_ShortResult_t short_result;
                    HW_Short_Test(&short_result);

                    for(uint8_t i = 0; i < 8; i++)
                    {
                        uint8_t bmp = short_result.map[i];

                        for(uint8_t j = 0; j < 8; j++)
                        {
                            if(i != j && (bmp & (1 << j)))
                            {
                                short_ch = i;   
                                goto FOUND;
                            }
                        }
                    }
                    FOUND:
                    if(short_ch != 0xFF)  //确实有短路
                    {
                        g_short_exist = 1;                                 //短路
                        g_short_location = (HW_Short_GetPosition(short_ch) / 2);
                    }
                    break;
                }
            }
            

            g_app.test = APP_TEST_FINISH;  //更新标签，校准完成

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
            HW_Cable_Init();                //线缆引脚初始化
            //判断线缆类型.
            CableType_Detect();
            //判断线序是否正常
            g_line_sequence = CableTest_RunOnce();
            //计算衰减
            HAR_Cable_Init();//模拟输入初始化
            HAR_Cable_StartSample();        //开始采集数据
            while(!HAR_Cable_IsReady()); // 等待DMA完成
            SER_FFT_Init(); //初始化FFT
            float f = SER_FFT_GetPeakFreq();
            float mag = SER_FFT_GetPeakMag();
            att = SER_FFT_CalcAttenuation(mag); //衰减
            g_app.test = APP_TEST_FINISH;  //更新标签，测量完成
        }
        
        break;

    default:
        break;
    }
}





