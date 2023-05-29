#ifndef __LED_H
#define __LED_H
#include "sys.h"	 

/*
灯光报警模块端口设置  4PIN接口->2
更换端口只需设置：RGB_PIN、RGB_GPIO和RGB_ClockCmd()对应的GPIO和PIN
*/

#define 	RGB_PIN 	     GPIO_Pin_11
#define   RGB_GPIO       GPIOA
#define		RGB_LED_HIGH	 GPIO_SetBits(RGB_GPIO,RGB_PIN)
#define 	RGB_LED_LOW		 GPIO_ResetBits(RGB_GPIO,RGB_PIN)
#define   RGB_ClockCmd()   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE)
 	
void RGB_LED_Init(void);
void RGB_LED_Write_Byte(u8 byte);
void RGB_LED_Write_24Bits(u8 green,u8 red,u8 blue);
void RGB_LED_Reset(void);

  
#endif
