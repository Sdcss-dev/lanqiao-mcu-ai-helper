#include <STC15F2K60S2.H>

/*
 * 矩阵按键扫描示例
 * 适用于蓝桥杯单片机 STC15F2K60S2 学习
 *
 * 功能：
 * 1. 使用 P44 / P42 / P35 / P34 逐行扫描
 * 2. 使用 P32 / P33 读取按键状态
 * 3. 按键按下后返回对应键值
 * 4. 可用于界面切换、参数加减等功能
 */

unsigned char key_value = 0;
unsigned char view = 0;
unsigned char set_temp = 25;

void Delay(unsigned int t)
{
    unsigned int i;
    unsigned int j;

    for(i = 0; i < t; i++)
    {
        for(j = 0; j < 845; j++)
        {
        }
    }
}

unsigned char Key_Read(void)
{
    unsigned char key = 0;

    P44 = 0;
    P42 = 1;
    P35 = 1;
    P34 = 1;

    if(P32 == 0)
    {
        Delay(2);
        if(P32 == 0)
        {
            key = 4;
            while(P32 == 0);
        }
    }

    if(P33 == 0)
    {
        Delay(2);
        if(P33 == 0)
        {
            key = 5;
            while(P33 == 0);
        }
    }

    P44 = 1;
    P42 = 0;
    P35 = 1;
    P34 = 1;

    if(P32 == 0)
    {
        Delay(2);
        if(P32 == 0)
        {
            key = 8;
            while(P32 == 0);
        }
    }

    if(P33 == 0)
    {
        Delay(2);
        if(P33 == 0)
        {
            key = 9;
            while(P33 == 0);
        }
    }

    P44 = 1;
    P42 = 1;
    P35 = 0;
    P34 = 1;

    if(P32 == 0)
    {
        Delay(2);
        if(P32 == 0)
        {
            key = 12;
            while(P32 == 0);
        }
    }

    if(P33 == 0)
    {
        Delay(2);
        if(P33 == 0)
        {
            key = 13;
            while(P33 == 0);
        }
    }

    P44 = 1;
    P42 = 1;
    P35 = 1;
    P34 = 0;

    if(P32 == 0)
    {
        Delay(2);
        if(P32 == 0)
        {
            key = 16;
            while(P32 == 0);
        }
    }

    if(P33 == 0)
    {
        Delay(2);
        if(P33 == 0)
        {
            key = 17;
            while(P33 == 0);
        }
    }

    return key;
}

void Key_Process(void)
{
    key_value = Key_Read();

    if(key_value == 4)
    {
        view++;

        if(view >= 3)
        {
            view = 0;
        }
    }

    if(key_value == 5)
    {
        if(view == 2)
        {
            set_temp++;

            if(set_temp > 99)
            {
                set_temp = 99;
            }
        }
    }

    if(key_value == 8)
    {
        if(view == 2)
        {
            if(set_temp > 0)
            {
                set_temp--;
            }
        }
    }
}

void main(void)
{
    while(1)
    {
        Key_Process();

        /*
         * view == 0：环境界面
         * view == 1：运动界面
         * view == 2：参数设置界面
         *
         * set_temp 可作为温度参数设置值
         */
    }
}
