#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 

#define adc_ch   ADC_Channel_15
 					
#define Low_Vol  10.8

void Adc_Init(void); 				//ADC通道初始化
u16  Get_Adc(void); 				//获得某个通道值 
u16 Get_Adc_Average(u8 times);//得到某个通道给定次数采样的平均值  

float Get_Bat_Vol(void);//获取电池电压数据
//低电压报警
void Low_Voltage_Alarm(void);
#endif 















