#include <STC15F2K60S2.H>
#include "iic.h"

/*
 * PCF8591 IIC 读写示例
 * 适用于蓝桥杯单片机 STC15F2K60S2 学习
 *
 * 功能：
 * 1. 读取 PCF8591 ADC 通道数据
 * 2. 向 PCF8591 DAC 输出数据
 *
 * 说明：
 * 本文件依赖蓝桥杯官方提供的 iic.h / iic.c。
 * 常用于电压采集、光敏电阻采集、电位器采集、DAC 输出等题目。
 */

unsigned char adc_value = 0;
unsigned char dac_value = 0;

/*
 * 读取 PCF8591 ADC 数据
 *
 * 常见通道控制字：
 * 0x00：AIN0
 * 0x01：AIN1
 * 0x02：AIN2
 * 0x03：AIN3
 */
unsigned char PCF8591_Read_ADC(unsigned char channel)
{
    unsigned char value;

    IIC_Start();
    IIC_SendByte(0x90);
    IIC_WaitAck();

    IIC_SendByte(channel);
    IIC_WaitAck();

    IIC_Start();
    IIC_SendByte(0x91);
    IIC_WaitAck();

    value = IIC_RecByte();
    IIC_SendAck(1);

    IIC_Stop();

    return value;
}

/*
 * PCF8591 DAC 输出
 *
 * control = 0x40 表示开启 DAC 输出
 * dat 范围：0 ~ 255
 */
void PCF8591_Write_DAC(unsigned char dat)
{
    IIC_Start();
    IIC_SendByte(0x90);
    IIC_WaitAck();

    IIC_SendByte(0x40);
    IIC_WaitAck();

    IIC_SendByte(dat);
    IIC_WaitAck();

    IIC_Stop();
}

void main(void)
{
    while(1)
    {
        /*
         * 示例：读取 AIN1 通道
         * 实际比赛中通道号要根据题目要求决定
         */
        adc_value = PCF8591_Read_ADC(0x01);

        /*
         * 示例：把 ADC 读取值直接输出到 DAC
         * 实际题目中通常需要按比例换算
         */
        dac_value = adc_value;
        PCF8591_Write_DAC(dac_value);
    }
}
