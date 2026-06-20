#include "app_ui.h"

//界面
void app_ui(void)
{
	char text[20] = {0};
    switch (g_app.page)
    {
        case APP_PAGE_CALIBRATION:
            /* 校准界面 */
            {
                switch (g_app.test)
                {
                    case APP_TEST_IDLE: //准备界面
                    {
                        OLED_ShowCN(1, 1, 28, 0);  //开
                        OLED_ShowCN(1, 2, 29, 0);  //始
                        OLED_ShowCN(1, 3, 30, 0);  //校
                        OLED_ShowCN(1, 4, 31, 0);  //准

                        break;
                    }
                    case APP_TEST_RUNNING: //桥准中界面
                    {
                        OLED_ShowCN(1, 1, 30, 0);  //校
                        OLED_ShowCN(1, 2, 31, 0);  //准
                        OLED_ShowCN(1, 3, 27, 0);  //中
                        OLED_ShowCN(1, 4, 32, 0);  //NULL
                        break;
                    }
                    case APP_TEST_FINISH: //桥准结束界面
                    {
                        // 第1行
                        OLED_ShowCN(2, 1, 30, 0);  //校
                        OLED_ShowCN(2, 2, 31, 0);  //准
                        OLED_ShowCN(2, 3, 2,  0);  //完
                        OLED_ShowCN(2, 4, 3,  0);  //成
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
                switch (g_app.test)
                {
                    case APP_TEST_IDLE: //准备界面
                    {
                        OLED_ShowCN(1, 1, 28, 0);  // 开
                        OLED_ShowCN(1, 2, 29, 0);  // 始
                        OLED_ShowCN(1, 3, 0,  0);  // 测
                        OLED_ShowCN(1, 4, 1,  0);  // 量

                        break;
                    }
                    case APP_TEST_RUNNING: //桥准中界面
                    {
                        OLED_ShowCN(1, 1, 0,  0);  // 测
                        OLED_ShowCN(1, 2, 1,  0);  // 量
                        OLED_ShowCN(1, 3, 27, 0);  // 中  
                        OLED_ShowCN(1, 4, 32, 0);  //NULL
                        break;
                    }
                    case APP_TEST_FINISH: //桥准结束界面
                    {
                        // 第1行
                        OLED_ShowCN(1, 1, 16, 0);  //单
                        OLED_ShowCN(1, 2, 5,  0);  //端
                        OLED_ShowCN(1, 3, 6,  0);  //界
                        OLED_ShowCN(1, 4, 7,  0);  //面

                        //
                        OLED_ShowCN(2, 1, 8,  0);  // 线
                        OLED_ShowCN(2, 2, 9,  0);  // 缆
                        OLED_ShowCN(2, 3, 10, 0);  // 类
                        OLED_ShowCN(2, 4, 11, 0);  // 型

                        if(cable == CABLE_SFTP)
                        {
                            OLED_ShowString(1,6,"SFTP");
                        } else OLED_ShowString(1,6,"UTP");
                        //
                        OLED_ShowCN(3, 1, 8,  0);  // 线
                        OLED_ShowCN(3, 2, 9,  0);  // 缆
                        OLED_ShowCN(3, 3, 21, 0);  // 长
                        OLED_ShowCN(3, 4, 22, 0);  // 度

                        sprintf(text,"%.1f cm",g_cable_length);
                        OLED_ShowString(3,6,text);

                        // 短路位置
                        OLED_ShowCN(4, 1, 23, 0);  // 短
                        OLED_ShowCN(4, 2, 24, 0);  // 路
                        OLED_ShowCN(4, 3, 25, 0);  // 位
                        OLED_ShowCN(4, 4, 26, 0);  // 置

                        sprintf(text,"%.1f cm",g_short_location);
                        OLED_ShowString(4,6,text);
                        break;
                    }
                    default:
                        break;
                }
            }
            break;

        case APP_PAGE_DOUBLE:
            /* 双端界面 */
            {
                 switch (g_app.test)
                {
                    case APP_TEST_IDLE: //准备界面
                    {
                        OLED_ShowCN(1, 1, 28, 0);  // 开
                        OLED_ShowCN(1, 2, 29, 0);  // 始
                        OLED_ShowCN(1, 3, 0,  0);  // 测
                        OLED_ShowCN(1, 4, 1,  0);  // 量

                        break;
                    }
                    case APP_TEST_RUNNING: //桥准中界面
                    {
                        OLED_ShowCN(1, 1, 0,  0);  // 测
                        OLED_ShowCN(1, 2, 1,  0);  // 量
                        OLED_ShowCN(1, 3, 27, 0);  // 中  
                        OLED_ShowCN(1, 4, 32, 0);  //NULL
                        break;
                    }
                    case APP_TEST_FINISH: //桥准结束界面
                    {
                        // 第1行
                        OLED_ShowCN(1, 1, 4,  0);  //双
                        OLED_ShowCN(1, 2, 5,  0);  //端
                        OLED_ShowCN(1, 3, 6,  0);  //界
                        OLED_ShowCN(1, 4, 7,  0);  //面

                        //
                        OLED_ShowCN(2, 1, 8,  0);  // 线
                        OLED_ShowCN(2, 2, 9,  0);  // 缆
                        OLED_ShowCN(2, 3, 10, 0);  // 类
                        OLED_ShowCN(2, 4, 11, 0);  // 型

                        if(cable == CABLE_SFTP)
                        {
                            OLED_ShowString(2,6,"SFTP");
                        } else OLED_ShowString(2,6,"UTP");

                        //
                        OLED_ShowCN(3, 1, 12, 0);  //交
                        OLED_ShowCN(3, 2, 13, 0);  //流
                        OLED_ShowCN(3, 3, 14, 0);  //衰
                        OLED_ShowCN(3, 4, 15, 0);  //减

                        sprintf(text,"%.1f db",att);
                        OLED_ShowString(3,6,text);

                        OLED_ShowCN(4, 1, 18, 0);  //直
                        OLED_ShowCN(4, 2, 19, 0);  //阻
                        OLED_ShowCN(4, 3, 20, 0);  //值
                        OLED_ShowCN(4, 4, 32, 0);  //值




                        break;

												}
												break;

										default:
												break;
								}
					}
			}
}


