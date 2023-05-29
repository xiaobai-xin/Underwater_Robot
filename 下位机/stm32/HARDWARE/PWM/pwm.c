#include "pwm.h"
#include "led.h"
#include "usart.h"
 

//TIM3 PWM初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u32 arr,u32 psc)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTB时钟	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOA6复用为定时器3
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOA7复用为定时器3
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3); //GPIOB0复用为定时器3
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3); //GPIOB1复用为定时器3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //初始化PA6.7
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PB0.1
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器3
	
	//初始化TIM3 Channel1-4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
  
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC1
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC2
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC3
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC4

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
 
										  
}  

//TIM8 PWM初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM8_PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);   	//TIM8时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能PORTC时钟	
  
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8); //GPIOC6复用为定时器8
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8); //GPIOC7复用为定时器8
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8); //GPIOC8复用为定时器8
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8); //GPIOC9复用为定时器8
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PC6.7.8.9
  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseStructure);//初始化定时器8
	
	//初始化TIM8 Channel1-4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset ;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
  
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC1
  TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC2
  TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC3
  TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC4

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
  TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
  TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
  TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器
 
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
  TIM_ARRPreloadConfig(TIM8,ENABLE);//ARPE使能 
	TIM_Cmd(TIM8, ENABLE);  //使能TIM8								  
}  

void TIM1_PWM_Init(u8 s4,u8 s5,u8 s6,u8 s10)//传感执行4，传感执行5，传感执行6，传感执行10
{		 					 
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

		if(s4+s5+s6+s10)
		{
			TIM_Cmd(TIM1, DISABLE);  //失能TIM1
			
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1时钟使能    
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTE时钟	
			
			if(s10)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOE9复用为定时器1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOE9
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //初始化
			}
			if(s4)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_TIM1); //GPIOE14复用为定时器1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOE14
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //初始化
			}
			if(s5)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); //GPIOE13复用为定时器1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;           //GPIOE13
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //初始化
			}
			if(s6)
			{
				GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); //GPIOE11复用为定时器1
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;           //GPIOE11
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
				GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
				GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
				GPIO_Init(GPIOE,&GPIO_InitStructure);               //初始化
			}
			
			TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //定时器分频
			TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
			TIM_TimeBaseStructure.TIM_Period=40000-1;   //自动重装载值
			TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
			
			TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化定时器1
			
			//初始化TIM1 Channel1-4 PWM模式	 
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
			TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
			
			if(s10)
			{
				TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1OC1
				TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器
			}
			if(s6)
			{
				 TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1OC2
				 TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器
			}
			if(s5)
			{
				TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1OC3
				TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器
			}
			if(s4)
			{
				TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1OC4
				TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR4上的预装载寄存器
			}    
			 
			TIM_CtrlPWMOutputs(TIM1, ENABLE);
			TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE使能 
			
			TIM_Cmd(TIM1, ENABLE);  //使能TIM1
		} 										  
}  
void TIM9_PWM_Init(u8 s3,u8 s7)//传感执行3，传感执行7
{		 		
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(s3+s7)
  {
    TIM_Cmd(TIM9, DISABLE);  //失能TIM9
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);  	//TIM9时钟使能    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTE时钟	
    
    if(s3)
    {
      GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9); //GPIOE5复用为定时器9
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOE5
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
      GPIO_Init(GPIOE,&GPIO_InitStructure);               //初始化
    }
    if(s7)
    {
      GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9); //GPIOE6复用为定时器9
      
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;           //GPIOE6
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
      GPIO_Init(GPIOE,&GPIO_InitStructure);               //初始化
    }
    TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//初始化定时器9
    
    //初始化TIM9 Channel1-4 PWM模式	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
    
    if(s3)
    {
      TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM9OC1
      TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);  //使能TIM9在CCR1上的预装载寄存器
    }
    if(s7)
    {
       TIM_OC2Init(TIM9, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM9OC2
       TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  //使能TIM9在CCR1上的预装载寄存器
    }  	
    TIM_ARRPreloadConfig(TIM9,ENABLE);//ARPE使能 
    
    TIM_Cmd(TIM9, ENABLE);  //使能TIM9
  }										  
}  
void TIM11_PWM_Init(u8 s1)//传感执行1
{		 					  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  if(s1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  	//TIM11时钟使能    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTB时钟	
    
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11); //GPIOB9复用为定时器11
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOB9
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
    GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PB9
      
    TIM_TimeBaseStructure.TIM_Prescaler=90-1;  //定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);//初始化定时器11
    
    //初始化TIM11 Channel1-4 PWM模式	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
    
    TIM_OC1Init(TIM11, &TIM_OCInitStructure);   //根据T指定的参数初始化外设TIM11OC1

    TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);  //使能TIM11在CCR1上的预装载寄存器

    TIM_ARRPreloadConfig(TIM11,ENABLE);//ARPE使能
     
     TIM_Cmd(TIM11, ENABLE);  //使能TIM11
 }
 
}  

void TIM2_PWM_Init(u8 s11)//传感执行11
{		 				
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	if(s11)
  {       
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2时钟使能    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
    
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2); //GPIOA5复用为定时器2
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //GPIOA5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
    GPIO_Init(GPIOA,&GPIO_InitStructure);               //初始化
    
    TIM_TimeBaseStructure.TIM_Prescaler=45-1;  //定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//初始化定时器2
    
    //初始化TIM2 Channel1-4 PWM模式	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
    
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2OC1
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
      
    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPE使能 
    
    TIM_Cmd(TIM2, ENABLE);  //使能TIM2
  }   
} 
void TIM4_PWM_Init(u8 s2)//传感执行2
{		 				
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  if(s2)
  {
    TIM_Cmd(TIM4, DISABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4时钟使能    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//使能PORTB时钟	
    
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); //GPIOB7复用为定时器3
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;           //GPIOB7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
    GPIO_Init(GPIOB,&GPIO_InitStructure);              //初始化PB7
      
    TIM_TimeBaseStructure.TIM_Prescaler=45-1;  //定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
    TIM_TimeBaseStructure.TIM_Period=40000-1;   //自动重装载值
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//初始化定时器4
    
    //初始化TIM4 Channel1-4 PWM模式	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
    
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3OC1

    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM14在CCR1上的预装载寄存器

    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能 
    
    TIM_Cmd(TIM4, ENABLE);  //使能TIM4  
  }
}   
