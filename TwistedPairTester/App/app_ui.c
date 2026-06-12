#include "app_ui.h"

//界面
void app_ui(void)
{
    switch (g_app.page)
    {
        case APP_PAGE_CALIBRATION:
            /* 校准界面 */
            {
                switch (g_app.test)
                {
                    case APP_TEST_IDLE: //准备界面
                    {

                        break;
                    }

                    case APP_TEST_RUNNING: //桥准中界面
                    {

                        break;
                    }

                    case APP_TEST_FINISH: //桥准结束界面
                    {

                        break;
                    }
                        
                    
                    default:
                        break;
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

            }
            break;

        default:
            break;
    }
}
