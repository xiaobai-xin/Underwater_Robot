#include "led.h" 
#include "delay.h"
//定义RGB数值数组 
u8 g_ledDataBuffer[24];
//RGB端口初始化
void RGB_LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RGB_ClockCmd();            //使能RGB GPIO时钟

  GPIO_InitStructure.GPIO_Pin = RGB_PIN;//初始化RGB_PIN
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(RGB_GPIO, &GPIO_InitStructure);//初始化GPIO
	
  RGB_LED_LOW;                           //RGB控制管脚设置低		 
}

/********************************************************/
//
/********************************************************/
//RGB写入数值0
void RGB_LED_Write0(void)
{
	RGB_LED_HIGH;
  __nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
  
  	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
  
  	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
}

/********************************************************/
//
/********************************************************/
//RGB写入数值1
void RGB_LED_Write1(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();  
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
  	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 

	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop(); 
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();   
}
//RGB复位
void RGB_LED_Reset(void)
{
	RGB_LED_LOW;
	delay_us(20);
}
//RGB写入1个字节数据
void RGB_LED_Write_Byte(u8 byte)
{
	u8 i;

	for(i=0;i<8;i++)
		{
			if(byte&0x80)
				{
					RGB_LED_Write1();
			}
			else
				{
					RGB_LED_Write0();
			}
		byte <<= 1;
	}
}
//单个RGB设置颜色
void RGB_LED_Write_24Bits(u8 green,u8 red,u8 blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);

  
}

