#include "drv_cable_test.h"

static BSP_GPIO_t tx_pin[8] =
{
    {GPIOC, GPIO_PIN_0},
    {GPIOC, GPIO_PIN_1},
    {GPIOC, GPIO_PIN_2},
    {GPIOC, GPIO_PIN_3},
    {GPIOC, GPIO_PIN_4},
    {GPIOC, GPIO_PIN_5},
    {GPIOC, GPIO_PIN_6},
    {GPIOC, GPIO_PIN_7},
};

static BSP_GPIO_t rx_pin[8] =
{
    {GPIOA, GPIO_PIN_1},
    {GPIOA, GPIO_PIN_2},
    {GPIOA, GPIO_PIN_3},
    {GPIOA, GPIO_PIN_4},
    {GPIOA, GPIO_PIN_5},
    {GPIOA, GPIO_PIN_6},
    {GPIOA, GPIO_PIN_7},
    {GPIOB, GPIO_PIN_0},
};

static BSP_GPIO_t shield_tx_pin[] = {GPIOB,GPIO_PIN_1};
static BSP_GPIO_t shield_rx_pin[] = {GPIOG,GPIO_PIN_9};

static uint8_t map[8];      //发送
static uint8_t rx_state[8]; //接收

void CableTest_Init(void)
{
    for(int i=0;i<8;i++)
    {
        map[i] = 0xFF;
        rx_state[i] = 0;
    }
}

static void CableTest_Send(uint8_t index)
{
    for(uint8_t i=0;i<8;i++)
    {
        BSP_GPIO_Write(&tx_pin[i],
                      (i == index) ? GPIO_HIGH : GPIO_LOW);
    }
}

static void CableTest_Read(void)
{
    for(uint8_t i=0;i<8;i++)
    {
        rx_state[i] = BSP_GPIO_Read(&rx_pin[i]);
    }
}

//类型判断
uint8_t CableType_Detect(void)
{
	BSP_GPIO_Write(shield_rx_pin,GPIO_LOW);
	BSP_GPIO_Write(shield_tx_pin,GPIO_HIGH);
	uint8_t text = BSP_GPIO_Reset(shield_rx_pin);
	if(text == 1) return 1; //  SFTP屏蔽
	else return 0; 					//非屏蔽UTP
}

//线序排查
uint8_t CableTest_RunOnce(void)
{
    uint8_t local_map[8];

    CableTest_Init();

    for(uint8_t tx=0; tx<8; tx++)
    {
			// 发送
        CableTest_Send(tx);

        // 稳定延时
        for(volatile int i=0;i<2000;i++);

        // 采样
        CableTest_Read();

        // 4. 找唯一响应
        uint8_t count = 0;
        uint8_t rx_j = 0xFF;

        for(uint8_t j=0;j<8;j++)
        {
            if(rx_state[j])
            {
                count++;
                rx_j = j;
            }
        }

        // 判断
        if(count == 1)
            local_map[tx] = rx_j;
        else
            local_map[tx] = 0xFE;
    }

    // 整体判断
    for(uint8_t i=0;i<8;i++)
    {
        if(local_map[i] != i)
        {
            return 1; // 错
        }
    }

    return 0; // 对
}

//开路检测
uint8_t CableTest_CheckOpen(void)
{
		// 发送全部置高
    for(uint8_t i=0;i<8;i++)
    {
        BSP_GPIO_Write(&tx_pin[i], GPIO_HIGH);
    }

    // 等待稳定
    for(volatile int i=0;i<2000;i++);

    // 读取接收信号
    CableTest_Read();

    // 检查是否有断线
    for(uint8_t i=0;i<8;i++)
    {
        if(rx_state[i] == 0)
        {
            return 1; // 开路
        }
    }

    return 0; // 正常
}



