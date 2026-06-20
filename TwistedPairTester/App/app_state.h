#ifndef __APP_STATE_H
#define __APP_STATE_H

#include "main.h"
#include "drv_key.h"
#include "drv_cable_test.h"
#include "srv_length.h"
#include "srv_short.h"
#include "ser_fft.h"


typedef enum
{
    APP_PAGE_CALIBRATION,    //校准界面
    APP_PAGE_DOUBLE,     //双端界面
    APP_PAGE_SINGLE,         //单端界面

}APP_Page_t;

typedef enum
{
    APP_TEST_IDLE,           //测量空闲
    APP_TEST_START,          //开始测试
    APP_TEST_RUNNING,        //测试中
    APP_TEST_FINISH,         //测试完成
    APP_TEST_TIMEOUT         //超时
}APP_TestState_t;

typedef enum
{

    APP_DOUBLE_IDLE,             //双端空闲
    APP_DOUBLE_L_SEQU,           //线序配查
    APP_DOUBLE_TYPE_CHECK,       //类型识别
    APP_DOUBLE_AC_ATTENUATION,   //交流衰减
    APP_DOUBLE_DC_RESISTANCE,    //直流阻值
    APP_DOUBLE_FINISH
}APP_DoubleState_t;

//typedef enum
//{
//    APP_SINGLE_IDLE,             //单端空闲
//    APP_SINGLE_LENGTH,           //长度测量
//    APP_SINGLE_SHORT_CHECK,      //短路检测
//    APP_SINGLE_SHORT_LOCATION,   //短路定位
//    APP_SINGLE_FINISH

//}APP_SingleState_t;

typedef struct
{
    APP_Page_t page;
    APP_TestState_t test;
    APP_DoubleState_t double_state;
//    APP_SingleState_t single_state;
}APP_State_t;


extern APP_State_t g_app;
extern float g_cable_length;
extern float g_short_location;
extern float g_dc_res;
extern float g_atten_val;

extern CableType_t g_cable_type;          //线缆类型
extern uint8_t g_line_sequence;        //线序
extern uint8_t g_line_k;           //开路检测
extern float g_attenuation_db;        //交流衰减(dB)
extern float g_dc_resistance;         //直流阻值(Ω)
extern float att;                      //衰减
/* 单端测试 */
extern float g_c;                     //电容
extern float g_cable_length;          //线缆长度(cm)
extern uint8_t g_short_exist;         //是否短路

extern float g_short_location;        //短路位置(cm)


void APP_State_Init(void);
void APP_State_Process(void);


#endif


