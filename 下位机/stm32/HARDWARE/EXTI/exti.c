#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "beep.h"
#include "stdio.h"

 u16 Sensor_State_All=0x0FFF;           //定义整体传感状态变量


//传感状态置1函数
void Senser_State_Set(u8 Sensor_num)
{
  Sensor_State_All |=(0x0001<<(Sensor_num-1)); 
}

//传感状态置0函数
void Sensor_State_Reset(u8 Sensor_num)
{
  Sensor_State_All &=~(0x0001<<(Sensor_num-1)); 
}



//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//消抖Sensor_1
/******************************传感1******************************/   
	if(Sensor_State_1)	  
	{
		Senser_State_Set(Sensor_1);  
	}		 
  else
  {   
    Sensor_State_Reset(Sensor_1);
  }
	 EXTI_ClearITPendingBit(EXTI_Line_Sensor_1); //清除LINE2上的中断标志位 
/****************************************************************/   
}	
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
/******************************传感3******************************/   
	if(Sensor_State_3)	  
	{
		Senser_State_Set(Sensor_3);  
	}		 
  else 
  {
    Sensor_State_Reset(Sensor_3);
  }
	 EXTI_ClearITPendingBit(EXTI_Line_Sensor_3);//清除LINE4上的中断标志位  
/****************************************************************/   
}

//外部中断0服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
/******************************传感9******************************/ 
	if(Sensor_State_9)	  
	{
		Senser_State_Set(Sensor_9);  
	}		 
  else 
  {
    Sensor_State_Reset(Sensor_9);
  }
	 EXTI_ClearITPendingBit(EXTI_Line_Sensor_9); //清除LINE0上的中断标志位 
/****************************************************************/ 
}	

//外部中断4服务程序
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//消抖
/******************************传感8******************************/ 
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_8))  
  {
    if(Sensor_State_8)	  
    {
      Senser_State_Set(Sensor_8);    
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_8);//清除LINE4上的中断标志位    
    }		 
    else if(!Sensor_State_8)
    {
       Sensor_State_Reset(Sensor_8);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_8);//清除LINE4上的中断标志位
    }
  }
/****************************************************************/    
/******************************传感2******************************/   
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_2))  
  {
    if(Sensor_State_2)	  
    {
      Senser_State_Set(Sensor_2);  
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_2);//清除LINE4上的中断标志位  
    }		 
    else if(!Sensor_State_2)
    {
       Sensor_State_Reset(Sensor_2); 
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_2);//清除LINE4上的中断标志位      
    }
  }
  
/****************************************************************/    
/******************************传感11******************************/   
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_11))  
  {
    if(Sensor_State_11)	  
    {
      Senser_State_Set(Sensor_11); 
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_11);//清除LINE4上的中断标志位    
    }		 
    else if(!Sensor_State_11)
    {
       Sensor_State_Reset(Sensor_11);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_11);//清除LINE4上的中断标志位
    }
  }
     
/****************************************************************/    
/******************************传感10******************************/  
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_10))  
  {  
    if(Sensor_State_10)	  
    {
      Senser_State_Set(Sensor_10); 
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_10);//清除LINE4上的中断标志位     
    }		 
    else if(!Sensor_State_10)
    {
       Sensor_State_Reset(Sensor_10);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_10);//清除LINE4上的中断标志位 
    }
  }    
/****************************************************************/    
}
//外部中断0服务程序
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);	//消抖
/******************************传感5******************************/ 
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_5))
  {
    if(Sensor_State_5)	  
    {
      Senser_State_Set(Sensor_5);  
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_5);//清除LINE5上的中断标志位 
    }		 
    else if(!Sensor_State_5)
    {
       Sensor_State_Reset(Sensor_5);	    
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_5);//清除LINE5上的中断标志位 
    }
  }
/****************************************************************/    
/******************************传感6******************************/ 
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_6))  
  {
    if(Sensor_State_6)	  
    {
      Senser_State_Set(Sensor_6);  
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_6);//清除LINE4上的中断标志位
    }		 
    else if(!Sensor_State_6)
    {
       Sensor_State_Reset(Sensor_6);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_6);//清除LINE4上的中断标志位
    }
  }
/****************************************************************/    
/******************************传感7******************************/   
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_7))  
  {
    if(Sensor_State_7)	  
    {
      Senser_State_Set(Sensor_7); 
      EXTI_ClearITPendingBit(EXTI_Line_Sensor_7);//清除LINE4上的中断标志位    
    }		 
    else if(!Sensor_State_7)
    {
       Sensor_State_Reset(Sensor_7);  
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_7);//清除LINE4上的中断标志位
    }
 } 
/****************************************************************/    
/******************************传感4******************************/    
  if(EXTI_GetFlagStatus(EXTI_Line_Sensor_4))  
  {
    if(Sensor_State_4)	  
    {
      Senser_State_Set(Sensor_4);    
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_4);//清除LINE4上的中断标志位    
    }		 
    else if(!Sensor_State_4)
    {
       Sensor_State_Reset(Sensor_4);
       EXTI_ClearITPendingBit(EXTI_Line_Sensor_4);//清除LINE4上的中断标志位 
    }
  }
/****************************************************************/
}	


//外部中断初始化程序
void EXTIX_Indepent_Init(u8 port)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟

  switch(port)
  {
    case Sensor_1:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2
        
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2); //PE2   连接到中断线2   传感1
        /* 配置EXTI_Line0 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line2;//LINE2
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE2
      EXTI_Init(&EXTI_InitStructure);//配置
  
      
      NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
      
      if(!Sensor_State_1)
      {
        Sensor_State_Reset(Sensor_1);
      }
      
      break;
    }
    case Sensor_2:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB6
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource6); //PB6   连接到中断线6   传感2
      	/* 配置EXTI_Line4 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line6;//LINE6
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
      EXTI_Init(&EXTI_InitStructure);//配置
      
//      #ifndef  __EXTI9_5_IRQn
//      #define  __EXTI9_5_IRQn
     	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断6
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
//      #endif
       
      if(!Sensor_State_2)
      {
        Sensor_State_Reset(Sensor_2);
      } 
       
      break;
    }
    case Sensor_3:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE3
      
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3); //PE3   连接到中断线3   传感3
      
        	/* 配置EXTI_Line0 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line3;//LINE3
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE3
      EXTI_Init(&EXTI_InitStructure);//配置
      
     	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
      
      if(!Sensor_State_3)
      {
        Sensor_State_Reset(Sensor_3);
      }
      
      break;
    }  
    case Sensor_4:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE15
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);//PE15  连接到中断线15  传感4
      
      	/* 配置EXTI_Line4 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line15;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
      EXTI_Init(&EXTI_InitStructure);//配置
      
//      #ifndef __EXTI15_10_IRQn
//      #define __EXTI15_10_IRQn      
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断15
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
//      #endif      
      if(!Sensor_State_4)
      {
        Sensor_State_Reset(Sensor_4);
      }      
      break;
    }  
    case Sensor_5:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输入模式
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE12
			GPIO_SetBits(GPIOE,GPIO_Pin_12);
           
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource12);//PE12  连接到中断线12  传感5          
        	/* 配置EXTI_Line12 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line12;//LINE12
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE12
      EXTI_Init(&EXTI_InitStructure);//配置
        
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断12
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
 
      if(!Sensor_State_5)
      {
        Sensor_State_Reset(Sensor_5);
      }  
      break;     
    }
    case Sensor_6:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE10
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource10);//PE10  连接到中断线10  传感6      
      	/* 配置EXTI_Line10 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line10;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
      EXTI_Init(&EXTI_InitStructure);//配置
          
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断10
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
      
      if(!Sensor_State_6)
      {
        Sensor_State_Reset(Sensor_6);
      }
      break;           
    }
    case Sensor_7:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC13
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);//PC13  连接到中断线13  传感7
      
        	/* 配置EXTI_Line13 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line13;//LINE13
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE13
      EXTI_Init(&EXTI_InitStructure);//配置
          
      NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断13
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
      
      if(!Sensor_State_7)
      {
        Sensor_State_Reset(Sensor_7);
      }
      break; 
    }
    case Sensor_8:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIOD5
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5); //PD5   连接到中断线5   传感8
    
        /* 配置EXTI_Line5 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line5;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
      EXTI_Init(&EXTI_InitStructure);//配置
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断5
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
    
     if(!Sensor_State_8)
     {
       Sensor_State_Reset(Sensor_8);
     }
     
      break;      
    }
    case Sensor_9:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC4
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource4); //PC4   连接到中断线4   传感9
      
        /* 配置EXTI_Line4 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE4
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发 
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE4
      EXTI_Init(&EXTI_InitStructure);//配置
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断4
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
    
      if(!Sensor_State_9)
      {
        Sensor_State_Reset(Sensor_9);
      }
      break;     
    }
    case Sensor_10:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE8
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8); //PE8   连接到中断线8   传感10
    
        /* 配置EXTI_Line8 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line8;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
      EXTI_Init(&EXTI_InitStructure);//配置
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断8
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置

      if(!Sensor_State_10)
      {
        Sensor_State_Reset(Sensor_10);
      }
      break;      
    }
    case Sensor_11:
    {
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // 对应引脚
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;//上拉
      GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE7
      
      SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource7); //PE7   连接到中断线7   传感11
    
        /* 配置EXTI_Line7 */
      EXTI_InitStructure.EXTI_Line = EXTI_Line7;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升沿/下降沿触发
      EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
      EXTI_Init(&EXTI_InitStructure);//配置
    
      NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断7
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
      NVIC_Init(&NVIC_InitStructure);//配置
     
     if(!Sensor_State_11)
     {
       Sensor_State_Reset(Sensor_11);
     }
      break;
    }
    default:break;  
  }

}


