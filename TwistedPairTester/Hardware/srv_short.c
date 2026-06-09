#include "srv_short.h"

/*----
第一次使用这种方式，大家可以看看有什么问题
短路检测思路总结
	pin[8] 数组映射8路检测引脚。
	HW_Short_Init() 将所有引脚配置为输入下拉，保证初始状态干净。
	HW_Short_SetChannel(ch) 将第 ch 路引脚设置为输出高电平，其余为输入下拉，启动检测。
	HW_Short_ReadBitmap() 扫描8路引脚电平，把检测到的高电平用 位图 存储在一个字节中，每一位对应一个引脚的状态。
	HW_Short_Test() 循环8次，将每一路依次设置输出高，然后读取8路状态，保存到 HW_ShortResult_t.map[i] 中。
	这样得到一个 8×8矩阵，每一行表示某一路输出高时，哪些引脚检测到高电平，从而判断短路情况。
	结果：
	每个字节对应一行8个引脚状态，用二进制表示“导通/未导通”便于解析和显示。
	判断短路，例如 if(result.map[i] != (1 << i)) 即表示第 i 路输出存在短路。
-----*/


static BSP_GPIO_t pin[8] =
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

typedef struct
{
    uint8_t map[8];
} HW_ShortResult_t;


void HW_Short_Init(void)
{
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        BSP_GPIO_Mode(pin[i], BSP_GPIO_MODE_INPUT_PULLDOWN);
    }
}

//开始启动检测！！！
static void HW_Short_SetChannel(uint8_t ch)
{
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        BSP_GPIO_Mode(pin[i], BSP_GPIO_MODE_INPUT_PULLDOWN);
    }

    BSP_GPIO_Mode(pin[ch], BSP_GPIO_MODE_OUTPUT_PP);

    BSP_GPIO_Write(&pin[ch], BSP_GPIO_HIGH);
}


//读取位图
static uint8_t HW_Short_ReadBitmap(void)
{
    uint8_t i;
    uint8_t bitmap = 0;

    for(i = 0; i < 8; i++)
    {
        if(BSP_GPIO_Read(&pin[i]))
        {
            bitmap |= (1 << i);
        }
    }

    return bitmap;
}

//扫描位图
void HW_Short_Test(HW_ShortResult_t *result)
{
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
				HW_Short_SetChannel(i);	
			
        BSP_Delay(1);

        result->map[i] = HW_Short_ReadBitmap();
    }

    HW_Short_Init();
}

/*----
	短路位置判断思路
	将矩阵中每一行的异常位提取出来，可以得到短路的“连接对”或“连接链路”。
	例如当 result.map[i] 中第 j 位被置位（且 j ≠ i），说明 i 通道与 j 通道之间存在电气连通，从而可构建短路关系。
	在此基础上进行位置估计时，利用 ADC 测量结果作为辅助定位依据。
	对参与短路的通道进行 ADC 采样，当某一短路链路形成时，电压会沿线缆阻抗产生衰减。
	通过比较不同通道的 ADC 数值大小规律，可以推断短路点在链路中的相对位置。
-----*/


static HW_ChannelMap_t hw_map[8] =
{
    { {GPIOA, GPIO_PIN_1}, {&hadc1, ADC_CHANNEL_1}, 0 },
    { {GPIOA, GPIO_PIN_2}, {&hadc1, ADC_CHANNEL_2}, 1 },
    { {GPIOA, GPIO_PIN_3}, {&hadc1, ADC_CHANNEL_3}, 2 },
    { {GPIOA, GPIO_PIN_4}, {&hadc1, ADC_CHANNEL_4}, 3 },
    { {GPIOA, GPIO_PIN_5}, {&hadc1, ADC_CHANNEL_5}, 4 },
    { {GPIOA, GPIO_PIN_6}, {&hadc1, ADC_CHANNEL_6}, 5 },
    { {GPIOA, GPIO_PIN_7}, {&hadc1, ADC_CHANNEL_7}, 6 },
    { {GPIOB, GPIO_PIN_0}, {&hadc1, ADC_CHANNEL_8}, 7 },
};


//读取ADC
uint16_t HW_ADC_Read(uint8_t ch)
{
    return BSP_ADC_Read(&hw_map[ch].adc);
}

float ADC_To_Length(uint16_t adc)
{
    // 转换长度
    return (float)adc * 0.01f;
}



float HW_Short_GetPosition(uint8_t ch)
{
    uint16_t adc;
    float len;

    // 切换继电器到电桥
    HW_Relay_On(ch);

    // GPIO切模拟输入
    BSP_GPIO_Mode(hw_map[ch].gpio, BSP_GPIO_MODE_ANALOG);

    BSP_Delay(10); // 稳定时间

    adc = HW_ADC_Read(ch);

    // 关闭继电器
    HW_Relay_On(0xFF);

    // 换算长度
    len = ADC_To_Length(adc);

    return len;
}







