#include <STC15F2K60S2.H>

/*
 * 数码管动态扫描示例
 * 适用于蓝桥杯单片机 STC15F2K60S2 学习
 *
 * 功能：
 * 1. 使用显示缓冲区 Disp_Buf[8]
 * 2. 通过定时器中断周期性刷新数码管
 * 3. 展示 8 位数码管动态扫描的基本结构
 */

unsigned char code Seg_Table[] =
{
    0xC0,  // 0
    0xF9,  // 1
    0xA4,  // 2
    0xB0,  // 3
    0x99,  // 4
    0x92,  // 5
    0x82,  // 6
    0xF8,  // 7
    0x80,  // 8
    0x90,  // 9
    0xFF   // 10: 熄灭
};

unsigned char code COM_Table[] =
{
    0x01,  // 第1位
    0x02,  // 第2位
    0x04,  // 第3位
    0x08,  // 第4位
    0x10,  // 第5位
    0x20,  // 第6位
    0x40,  // 第7位
    0x80   // 第8位
};

unsigned char Disp_Buf[8] = {1, 2, 3, 4, 5, 6, 7, 8};

void SelectHC573(unsigned char channel)
{
    switch(channel)
    {
        case 4:
            P2 = 0x80;
            break;
        case 6:
            P2 = 0xC0;
            break;
        case 7:
            P2 = 0xE0;
            break;
        default:
            P2 = 0x00;
            break;
    }
}

void Display_Scan(void)
{
    static unsigned char i = 0;

    SelectHC573(7);
    P0 = 0xFF;
    SelectHC573(0);

    SelectHC573(6);
    P0 = COM_Table[i];
    SelectHC573(0);

    SelectHC573(7);
    P0 = Seg_Table[Disp_Buf[i]];
    SelectHC573(0);

    i++;
    if(i >= 8)
    {
        i = 0;
    }
}

void Timer0Init(void)
{
    AUXR &= 0x7F;
    TMOD &= 0xF0;
    TL0 = 0x18;
    TH0 = 0xFC;
    TF0 = 0;
    TR0 = 1;
    ET0 = 1;
    EA = 1;
}

void Timer0_ISR(void) interrupt 1
{
    TL0 = 0x18;
    TH0 = 0xFC;

    Display_Scan();
}

void System_Init(void)
{
    SelectHC573(4);
    P0 = 0xFF;
    SelectHC573(0);

    SelectHC573(5);
    P0 = 0x00;
    SelectHC573(0);
}

void main(void)
{
    System_Init();
    Timer0Init();

    while(1)
    {
        // 主循环中暂时不处理任务
        // 数码管刷新由定时器中断完
    }
}
