#include "app_state.h"


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
    switch (g_app.page)
    {
    case APP_PAGE_CALIBRATION:
        /* 校准界面 */
        break;

    case APP_PAGE_SINGLE:
        /* 单端界面 */
        break;

    case APP_PAGE_DOUBLE:
        /* 双端界面 */
        break;

    default:
        break;
    }
}





