#include <STC15F2K60S2.H>
#include "onewire.h"

/*
 * DS18B20 温度读取示例
 * 适用于蓝桥杯单片机 STC15F2K60S2 学习
 *
 * 功能：
 * 1. 启动 DS18B20 温度转换
 * 2. 读取 DS18B20 温度数据
 * 3. 将原始数据转换为整数温度
 *
 * 说明：
 * 本文件依赖蓝桥杯官方提供的 onewire.h / onewire.c。
 * 常用于温度显示、温度参数比较、LED 联动等题目。
 */

unsigned int now_temp = 0;

void Delay_750ms(void)
{
    unsigned int i;
    unsigned int j;

    for(i = 0; i < 750; i++)
    {
        for(j = 0; j < 845; j++)
        {
        }
    }
}

void Temp_Start(void)
{
    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0x44);
}

unsigned int Temp_Read(void)
{
    unsigned char low;
    unsigned char high;
    unsigned int temp;

    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0xBE);

    low = Read_DS18B20();
    high = Read_DS18B20();

    temp = high;
    temp = temp << 8;
    temp = temp + low;

    temp = temp >> 4;

    return temp;
}

void main(void)
{
    Temp_Start();
    Delay_750ms();

    while(1)
    {
        now_temp = Temp_Read();

        Temp_Start();
        Delay_750ms();

        /*
         * now_temp 表示当前整数温度
         *
         * 示例：
         * now_temp == 25 表示当前温度约为 25℃
         *
         * 后续可以和数码管显示、参数设置、LED 控制结合：
         * 1. 数码管显示温度
         * 2. 按键设置温度阈值
         * 3. 温度超过阈值后点亮 LED
         */
    }
}
