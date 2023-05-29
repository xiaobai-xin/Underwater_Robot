#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
	

void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM8_PWM_Init(u32 arr,u32 psc);

void TIM1_PWM_Init(u8 s4,u8 s5,u8 s6,u8 s10);//传感执行4，传感执行5，传感执行6，传感执行10
void TIM9_PWM_Init(u8 s3,u8 s7);//传感执行3，传感执行7
void TIM11_PWM_Init(u8 s1);//传感执行1
void TIM2_PWM_Init(u8 s11);//传感执行11
void TIM4_PWM_Init(u8 s2);//传感执行2

#endif
