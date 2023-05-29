#ifndef __TIMER_H
#define __TIMER_H	 
#include "sys.h"

extern u16 T1_Speed;
extern u16 T2_Speed;
extern u16 T3_Speed;
extern u16 T4_Speed;
extern u16 T5_Speed;
extern u16 T6_Speed;
extern u16 T7_Speed;
extern u16 T8_Speed;


//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_Cap_Init(u32 arr,u16 psc);
//定时器4通道1-4输入捕获配置
//arr：自动重装值(TIM4是16位的)
//psc：时钟预分频数
void TIM4_Cap_Init(u16 arr,u16 psc);

void TIM7_Int_Init(u16 arr,u16 psc);

u16 TJQ_FB_Read(u8 t_num);
#endif


