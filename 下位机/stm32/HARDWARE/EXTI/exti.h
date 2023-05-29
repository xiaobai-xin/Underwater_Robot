#ifndef __EXTI_H
#define __EXTI_H	 
#include "sys.h"  	

extern  u16 Sensor_State_All;

#define       Sensor_State_1                     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define       Sensor_State_2                     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define       Sensor_State_3                     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define       Sensor_State_4                     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)
#define       Sensor_State_5                     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)
#define       Sensor_State_6                     GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)
#define       Sensor_State_7                     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
#define       Sensor_State_8                     GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)
#define       Sensor_State_9                     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)
#define       Sensor_State_10                    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)
#define       Sensor_State_11                    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)

#define       Sensor_1                           1
#define       Sensor_2                           2
#define       Sensor_3                           3
#define       Sensor_4                           4
#define       Sensor_5                           5
#define       Sensor_6                           6
#define       Sensor_7                           7
#define       Sensor_8                           8
#define       Sensor_9                           9
#define       Sensor_10                          10
#define       Sensor_11                          11

#define       EXTI_Line_Sensor_1                  EXTI_Line2
#define       EXTI_Line_Sensor_2                  EXTI_Line6
#define       EXTI_Line_Sensor_3                  EXTI_Line3
#define       EXTI_Line_Sensor_4                  EXTI_Line15
#define       EXTI_Line_Sensor_5                  EXTI_Line12
#define       EXTI_Line_Sensor_6                  EXTI_Line10
#define       EXTI_Line_Sensor_7                  EXTI_Line13
#define       EXTI_Line_Sensor_8                  EXTI_Line5
#define       EXTI_Line_Sensor_9                  EXTI_Line4
#define       EXTI_Line_Sensor_10                 EXTI_Line8
#define       EXTI_Line_Sensor_11                 EXTI_Line7

#define       EXTI_1_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_1)   //关闭了指定的外部中断
#define       EXTI_1_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_1      //开启指定的外部中断

#define       EXTI_2_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_2)   //关闭了指定的外部中断
#define       EXTI_2_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_2      //开启指定的外部中断

#define       EXTI_3_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_3)   //关闭了指定的外部中断
#define       EXTI_3_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_3      //开启指定的外部中断

#define       EXTI_4_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_4)   //关闭了指定的外部中断
#define       EXTI_4_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_4      //开启指定的外部中断

#define       EXTI_5_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_5)   //关闭了指定的外部中断
#define       EXTI_5_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_5      //开启指定的外部中断

#define       EXTI_6_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_6)   //关闭了指定的外部中断
#define       EXTI_6_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_6      //开启指定的外部中断

#define       EXTI_7_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_7)   //关闭了指定的外部中断
#define       EXTI_7_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_7      //开启指定的外部中断

#define       EXTI_8_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_8)   //关闭了指定的外部中断
#define       EXTI_8_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_8      //开启指定的外部中断

#define       EXTI_9_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_9)   //关闭了指定的外部中断
#define       EXTI_9_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_9      //开启指定的外部中断

#define       EXTI_10_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_10) //关闭了指定的外部中断
#define       EXTI_10_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_10    //开启指定的外部中断

#define       EXTI_11_DISABLE        EXTI->IMR &= ~(EXTI_Line_Sensor_11) //关闭了指定的外部中断
#define       EXTI_11_ENABLE         EXTI->IMR |= EXTI_Line_Sensor_11    //开启指定的外部中断



void Senser_State_Set(u8 Sensor_num);
void Sensor_State_Reset(u8 Sensor_num);	
void EXTIX_Indepent_Init(u8 port);//外部中断独立初始化



#endif




