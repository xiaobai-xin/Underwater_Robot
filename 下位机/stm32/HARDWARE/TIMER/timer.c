#include "timer.h" 
#include "stdio.h"
#include "delay.h" 
#include "propeller.h"
#include "adc.h"

u8 NUM[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
u8 speed[]={0x00,0x00,0x00,0x00};

u8 sp[4]={0x00,0x40,0x06,0x6D}; //SP-X

u8 di[4]={0X00,0X40,0X06,0X5E}; //DI-X
u8 fx[2]={0x71,0x37};
int i=0,j_num=0,z_num=0,tempnum=0;
float TEMP=0;



TIM_ICInitTypeDef  TIM5_ICInitStructure;
//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0复用位定时器5
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); //PA1复用位定时器5
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5); //PA2复用位定时器5
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); //PA3复用位定时器5
  
	 //TIM_DeInit(TIM5);  
  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
  
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
  
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
  
  TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	
}

TIM_ICInitTypeDef  TIM4_ICInitStructure;
//定时器4通道1-4输入捕获配置
//arr：自动重装值(TIM4是16位的)
//psc：时钟预分频数
void TIM4_Cap_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //GPIOD
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //下拉
	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PD

	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //PA12复用位定时器5
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4); //PA13复用位定时器5
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4); //PA14复用位定时器5
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4); //PA15复用位定时器5
  
	 //TIM_DeInit(TIM4);  
  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	

	//初始化TIM4输入捕获参数
	TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
  
  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
  
  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
  
  TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM4_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM4, &TIM4_ICInitStructure);
		
	TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM4,ENABLE ); 	//使能定时器4

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	
}

static int32_t TIM5IC_ReadValue1_ch1, TIM5IC_ReadValue2_ch1;  //记录通道的捕获值
static int32_t TIM5CaptureNumber_ch1 = 0;    //记录捕获次数
static int64_t TIM5Capture_ch1 = 0;         //最终捕获计算差值
static int32_t TIM5Cnt_ch1 = 0;   
int64_t TIM5TotalCapture_ch1 = 0;   

static int32_t TIM5IC_ReadValue1_ch2, TIM5IC_ReadValue2_ch2;  //记录通道的捕获值
static int32_t TIM5CaptureNumber_ch2 = 0;    //记录捕获次数
static int64_t TIM5Capture_ch2 = 0;         //最终捕获计算差值
static int32_t TIM5Cnt_ch2 = 0;   
int64_t TIM5TotalCapture_ch2 = 0;   

static int32_t TIM5IC_ReadValue1_ch3, TIM5IC_ReadValue2_ch3;  //记录通道的捕获值
static int32_t TIM5CaptureNumber_ch3 = 0;    //记录捕获次数
static int64_t TIM5Capture_ch3 = 0;         //最终捕获计算差值
static int32_t TIM5Cnt_ch3 = 0;   
int64_t TIM5TotalCapture_ch3 = 0;   

static int32_t TIM5IC_ReadValue1_ch4, TIM5IC_ReadValue2_ch4;  //记录通道的捕获值
static int32_t TIM5CaptureNumber_ch4 = 0;    //记录捕获次数
static int64_t TIM5Capture_ch4 = 0;         //最终捕获计算差值
static int32_t TIM5Cnt_ch4 = 0;   
int64_t TIM5TotalCapture_ch4 = 0;   
  
/*
********************************************************************************
** 函数名称 ： void TIM5_IRQHandler(void)
** 函数功能 ： 输入捕获
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void TIM5_IRQHandler(void)
{
	
	//处理接收到的数据
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC1)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);
		
			if(TIM5CaptureNumber_ch1==0)
			{
					TIM5IC_ReadValue1_ch1 = TIM_GetCapture1(TIM5);
					TIM5CaptureNumber_ch1 = 1;
			}
			else if(TIM5CaptureNumber_ch1==1)
			{
					TIM5IC_ReadValue2_ch1 = TIM_GetCapture1(TIM5);
				
				  if(TIM5IC_ReadValue2_ch1 > TIM5IC_ReadValue1_ch1)
					{
							TIM5Capture_ch1 += (TIM5IC_ReadValue2_ch1 - TIM5IC_ReadValue1_ch1);	
					}
					else
					{
							TIM5Capture_ch1 += ((0xFFFF - TIM5IC_ReadValue1_ch1) + TIM5IC_ReadValue2_ch1);
					}
					
					if(++TIM5Cnt_ch1 == 6)
					{
						TIM5TotalCapture_ch1 = TIM5Capture_ch1 ;
						TIM5Capture_ch1 		 = 0;
						TIM5Cnt_ch1					 = 0;
					}
					
					TIM5CaptureNumber_ch1 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC2)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);
		
			if(TIM5CaptureNumber_ch2==0)
			{
					TIM5IC_ReadValue1_ch2 = TIM_GetCapture2(TIM5);
					TIM5CaptureNumber_ch2 = 1;
			}
			else if(TIM5CaptureNumber_ch2==1)
			{
					TIM5IC_ReadValue2_ch2 = TIM_GetCapture2(TIM5);
				
				  if(TIM5IC_ReadValue2_ch2 > TIM5IC_ReadValue1_ch2)
					{
							TIM5Capture_ch2 += (TIM5IC_ReadValue2_ch2 - TIM5IC_ReadValue1_ch2);	
					}
					else
					{
							TIM5Capture_ch2 += ((0xFFFF - TIM5IC_ReadValue1_ch2) + TIM5IC_ReadValue2_ch2);
					}
					
					if(++TIM5Cnt_ch2 == 60)
					{
						TIM5TotalCapture_ch2 = TIM5Capture_ch2 / 10;
						TIM5Capture_ch2 		 = 0;
						TIM5Cnt_ch2					 = 0;
					}
					
					TIM5CaptureNumber_ch2 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC3)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);
		
			if(TIM5CaptureNumber_ch3==0)
			{
					TIM5IC_ReadValue1_ch3 = TIM_GetCapture3(TIM5);
					TIM5CaptureNumber_ch3 = 1;
			}
			else if(TIM5CaptureNumber_ch3==1)
			{
					TIM5IC_ReadValue2_ch3 = TIM_GetCapture3(TIM5);
				
				  if(TIM5IC_ReadValue2_ch3 > TIM5IC_ReadValue1_ch3)
					{
							TIM5Capture_ch3 += (TIM5IC_ReadValue2_ch3 - TIM5IC_ReadValue1_ch3);	
					}
					else
					{
							TIM5Capture_ch3 += ((0xFFFF - TIM5IC_ReadValue1_ch3) + TIM5IC_ReadValue2_ch3);
					}
					
					if(++TIM5Cnt_ch3 == 60)
					{
						TIM5TotalCapture_ch3 = TIM5Capture_ch3 / 10;
						TIM5Capture_ch3 		 = 0;
						TIM5Cnt_ch3					 = 0;
					}
					
					TIM5CaptureNumber_ch3 = 0;
			}
	}
  else if(TIM_GetITStatus(TIM5, TIM_IT_CC4)==SET)
	{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);
		
			if(TIM5CaptureNumber_ch4==0)
			{
					TIM5IC_ReadValue1_ch4 = TIM_GetCapture4(TIM5);
					TIM5CaptureNumber_ch4 = 1;
			}
			else if(TIM5CaptureNumber_ch4==1)
			{
					TIM5IC_ReadValue2_ch4 = TIM_GetCapture4(TIM5);
				
				  if(TIM5IC_ReadValue2_ch4 > TIM5IC_ReadValue1_ch4)
					{
							TIM5Capture_ch4 += (TIM5IC_ReadValue2_ch4 - TIM5IC_ReadValue1_ch4);	
					}
					else
					{
							TIM5Capture_ch4 += ((0xFFFF - TIM5IC_ReadValue1_ch4) + TIM5IC_ReadValue2_ch4);
					}
					
					if(++TIM5Cnt_ch4 == 60)
					{
						TIM5TotalCapture_ch4 = TIM5Capture_ch4 / 10;
						TIM5Capture_ch4 		 = 0;
						TIM5Cnt_ch4					 = 0;
					}
					
					TIM5CaptureNumber_ch4 = 0;
			}
	}
	  	
}

static int32_t TIM4IC_ReadValue1_ch1, TIM4IC_ReadValue2_ch1;  //记录通道的捕获值
static int32_t TIM4CaptureNumber_ch1 = 0;    //记录捕获次数
static int64_t TIM4Capture_ch1 = 0;         //最终捕获计算差值
static int32_t TIM4Cnt_ch1 = 0;   
int64_t TIM4TotalCapture_ch1 = 0;   

static int32_t TIM4IC_ReadValue1_ch2, TIM4IC_ReadValue2_ch2;  //记录通道的捕获值
static int32_t TIM4CaptureNumber_ch2 = 0;    //记录捕获次数
static int64_t TIM4Capture_ch2 = 0;         //最终捕获计算差值
static int32_t TIM4Cnt_ch2 = 0;   
int64_t TIM4TotalCapture_ch2 = 0;   

static int32_t TIM4IC_ReadValue1_ch3, TIM4IC_ReadValue2_ch3;  //记录通道的捕获值
static int32_t TIM4CaptureNumber_ch3 = 0;    //记录捕获次数
static int64_t TIM4Capture_ch3 = 0;         //最终捕获计算差值
static int32_t TIM4Cnt_ch3 = 0;   
int64_t TIM4TotalCapture_ch3 = 0;   

static int32_t TIM4IC_ReadValue1_ch4, TIM4IC_ReadValue2_ch4;  //记录通道的捕获值
static int32_t TIM4CaptureNumber_ch4 = 0;    //记录捕获次数
static int64_t TIM4Capture_ch4 = 0;         //最终捕获计算差值
static int32_t TIM4Cnt_ch4 = 0;   
int64_t TIM4TotalCapture_ch4 = 0;   

/*
********************************************************************************
** 函数名称 ： void TIM4_IRQHandler(void)
** 函数功能 ： 定时器中断
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void TIM4_IRQHandler(void)
{
	
	//处理接收到的数据
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC1)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
		
			if(TIM4CaptureNumber_ch1==0)
			{
					TIM4IC_ReadValue1_ch1 = TIM_GetCapture1(TIM4);
					TIM4CaptureNumber_ch1 = 1;
			}
			else if(TIM4CaptureNumber_ch1==1)
			{
					TIM4IC_ReadValue2_ch1 = TIM_GetCapture1(TIM4);
				
				  if(TIM4IC_ReadValue2_ch1 > TIM4IC_ReadValue1_ch1)
					{
							TIM4Capture_ch1 += (TIM4IC_ReadValue2_ch1 - TIM4IC_ReadValue1_ch1);	
					}
					else
					{
							TIM4Capture_ch1 += ((0xFFFF - TIM4IC_ReadValue1_ch1) + TIM4IC_ReadValue2_ch1);
					}
					
					if(++TIM4Cnt_ch1 == 60)
					{
						TIM4TotalCapture_ch1 = TIM4Capture_ch1 / 10;
						TIM4Capture_ch1 		 = 0;
						TIM4Cnt_ch1					 = 0;
					}
					
					TIM4CaptureNumber_ch1 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC2)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
		
			if(TIM4CaptureNumber_ch2==0)
			{
					TIM4IC_ReadValue1_ch2 = TIM_GetCapture2(TIM4);
					TIM4CaptureNumber_ch2 = 1;
			}
			else if(TIM4CaptureNumber_ch2==1)
			{
					TIM4IC_ReadValue2_ch2 = TIM_GetCapture2(TIM4);
				
				  if(TIM4IC_ReadValue2_ch2 > TIM4IC_ReadValue1_ch2)
					{
							TIM4Capture_ch2 += (TIM4IC_ReadValue2_ch2 - TIM4IC_ReadValue1_ch2);	
					}
					else
					{
							TIM4Capture_ch2 += ((0xFFFF - TIM4IC_ReadValue1_ch2) + TIM4IC_ReadValue2_ch2);
					}
					
					if(++TIM4Cnt_ch2 == 60)
					{
						TIM4TotalCapture_ch2 = TIM4Capture_ch2 / 10;
						TIM4Capture_ch2 		 = 0;
						TIM4Cnt_ch2					 = 0;
					}
					
					TIM4CaptureNumber_ch2 = 0;
			}
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC3)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);
		
			if(TIM4CaptureNumber_ch3==0)
			{
					TIM4IC_ReadValue1_ch3 = TIM_GetCapture3(TIM4);
					TIM4CaptureNumber_ch3 = 1;
			}
			else if(TIM4CaptureNumber_ch3==1)
			{
					TIM4IC_ReadValue2_ch3 = TIM_GetCapture3(TIM4);
				
				  if(TIM4IC_ReadValue2_ch3 > TIM4IC_ReadValue1_ch3)
					{
							TIM4Capture_ch3 += (TIM4IC_ReadValue2_ch3 - TIM4IC_ReadValue1_ch3);	
					}
					else
					{
							TIM4Capture_ch3 += ((0xFFFF - TIM4IC_ReadValue1_ch3) + TIM4IC_ReadValue2_ch3);
					}
					
					if(++TIM4Cnt_ch3 == 60)
					{
						TIM4TotalCapture_ch3 = TIM4Capture_ch3/10 ;
						TIM4Capture_ch3 		 = 0;
						TIM4Cnt_ch3					 = 0;
					}
					
					TIM4CaptureNumber_ch3 = 0;
			}
	}
  else if(TIM_GetITStatus(TIM4, TIM_IT_CC4)==SET)
	{
			TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);
		
			if(TIM4CaptureNumber_ch4==0)
			{
					TIM4IC_ReadValue1_ch4 = TIM_GetCapture4(TIM4);
					TIM4CaptureNumber_ch4 = 1;
			}
			else if(TIM4CaptureNumber_ch4==1)
			{
					TIM4IC_ReadValue2_ch4 = TIM_GetCapture4(TIM4);
				
				  if(TIM4IC_ReadValue2_ch4 > TIM4IC_ReadValue1_ch4)
					{
							TIM4Capture_ch4 += (TIM4IC_ReadValue2_ch4 - TIM4IC_ReadValue1_ch4);	
					}
					else
					{
							TIM4Capture_ch4 += ((0xFFFF - TIM4IC_ReadValue1_ch4) + TIM4IC_ReadValue2_ch4);
					}
					
					if(++TIM4Cnt_ch4 == 60)
					{
						TIM4TotalCapture_ch4 = TIM4Capture_ch4 / 10;
						TIM4Capture_ch4 		 = 0;
						TIM4Cnt_ch4					 = 0;
					}
					
					TIM4CaptureNumber_ch4 = 0;
			}
	}
	  	
}


void TIM7_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能
	
	//定时器TIM7初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM7, ENABLE);  //使能TIMx					 
}

u16 T1_Speed=0;
u16 T2_Speed=0;
u16 T3_Speed=0;
u16 T4_Speed=0;
u16 T5_Speed=0;
u16 T6_Speed=0;
u16 T7_Speed=0;
u16 T8_Speed=0;

//定时器7中断服务程序
void TIM7_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
      TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIMx更新中断标志     

 
      T1_Speed= 1000000 / TIM5TotalCapture_ch1 * 60;
      T2_Speed= 1000000 / TIM5TotalCapture_ch2 * 60;
      T3_Speed= 1000000 / TIM4TotalCapture_ch4 * 60;
      T4_Speed= 1000000 / TIM4TotalCapture_ch3 * 60;
      T5_Speed= 1000000 / TIM5TotalCapture_ch3 * 60;
      T6_Speed= 1000000 / TIM5TotalCapture_ch4 * 60;
      T7_Speed= 1000000 / TIM4TotalCapture_ch2 * 60;
      T8_Speed= 1000000 / TIM4TotalCapture_ch1 * 60;
      
      
//      printf("T1:%d\t",T1_Speed);
//      printf("T2:%d\t",T2_Speed);
//      printf("T3:%d\t",T3_Speed);
//      printf("T4:%d\t",T4_Speed);
//      printf("T5:%d\t",T5_Speed);
//      printf("T6:%d\t",T6_Speed);
//      printf("T7:%d\t",T7_Speed);
//      printf("T8:%d\t\n\n",T8_Speed);
      
      TIM5TotalCapture_ch1=0 ;
      TIM5TotalCapture_ch2=0 ;
      TIM5TotalCapture_ch3=0 ;
      TIM5TotalCapture_ch4=0 ;
      TIM4TotalCapture_ch1=0 ;
      TIM4TotalCapture_ch2=0 ;
      TIM4TotalCapture_ch3=0 ;
      TIM4TotalCapture_ch4=0 ;

		}
}

u16 TJQ_FB_Read(u8 t_num)
{
     switch(t_num)
     {
       case T1:
       {
          return T1_Speed;
 //         break;
       }
       case T2:
       {
          return T2_Speed;
 //         break;
       }
       case T3:
       {
          return T3_Speed;
 //         break;
       }
       case T4:
       {
          return T4_Speed;
 //         break;
       }
       case T5:
       {
          return T5_Speed;
 //         break;
       }
       case T6:
       {
          return T6_Speed;
 //         break;
       }
       case T7:
       {
          return T7_Speed;
 //         break;
       }
       case T8:
       {
          return T8_Speed;
 //         break;
       }
       default:
       {
        return 0;
         break;
       }
     }
}  


