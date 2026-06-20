#include "app.h"

//系统总入口


//系统初始化
void APP_Init(void)
{
	APP_State_Init();
}


//任务调度
void APP_Run(void)
{
	APP_State_Process();
    app_ui();
}


