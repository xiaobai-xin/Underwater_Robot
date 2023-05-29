#include "sys.h"
#include "usart.h"	
#include "433m.h" 
#include "bno055.h" 
#include "stdio.h"
#include "external.h"
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
  
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((UART8->SR&0X40)==0);//循环发送,直到发送完毕   
	UART8->DR = (u8) ch;      
	return ch;
}
#endif
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
#if EN_USART1_RX	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断
	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
#endif
   while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};//等待发送结束 
}


void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0xbb结尾)
	{
		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		ItRecvPrc(Res);
		  
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);    
  } 
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
} 
#endif	

/**************************串口5*******************************/
 #if EN_UART5_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 UART5_RX_BUF[UART5_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 UART5_RX_STA=0;       //接收状态标记	

//初始化IO 串口1 
//bound:波特率
void uart5_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
    
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
       
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource12,GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource2,GPIO_AF_UART5);
        
    USART_DeInit(UART5);
        
    USART_InitStructure.USART_BaudRate=bound;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init(UART5,&USART_InitStructure);
    
     NVIC_InitStructure.NVIC_IRQChannel=UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
    USART_Cmd(UART5,ENABLE);
	
	   
//	USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_UART5_RX	
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif
  while(USART_GetFlagStatus(UART5,USART_FLAG_TC)!=SET){};//等待发送结束
	
}
u8 RecU5=0;
void UART5_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0xbb结尾)
	{
		Res =USART_ReceiveData(UART5);//(USART1->DR);	//读取接收到的数据
    BNO055_Response_Receive(Res);
    USART_ClearITPendingBit(UART5, USART_IT_RXNE);
       
  } 
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
} 
#endif	

/**************************串口5*******************************/




/**************************串口8*******************************/
 #if EN_UART8_RX   //如果使能了接收
//串口8中断服务程序  	
u8 UART8_RX_BUF[UART8_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 UART8_RX_STA=0;       //接收状态标记	

//初始化IO 串口8
//bound:波特率
void uart8_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE); //使能GPIOE时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,ENABLE); //使能UART8时钟
 
	//串口8对应引脚复用映射
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource0,GPIO_AF_UART8); //GPIOE0复用为UART0
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_UART8); //GPIOE1复用为UART1
	
	//UART8端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //GPIOE0与GPIOE1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化PE0，PE1

   //UART8 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART8, &USART_InitStructure); //初始化串口8
	
  USART_Cmd(UART8, ENABLE);  //使能串口1 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
#if EN_UART8_RX	
	USART_ITConfig(UART8, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

#endif
	while(USART_GetFlagStatus(UART8,USART_FLAG_TC)!=SET){};//等待发送结束 
}

void UART8_IRQHandler(void)                	//串口8中断服务程序
{
	u8 Res;
//	#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//		OSIntEnter();    
//	#endif
	if(USART_GetITStatus(UART8, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res =USART_ReceiveData(UART8);//读取接收到的数据
		URAT8_DATA_Analysis(Res);
    USART_ClearITPendingBit(UART8, USART_IT_RXNE);  
  } 
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
} 
#endif	
/**************************串口8*******************************/



/**************************串口4*******************************/
 #if EN_UART4_RX   //如果使能了接收
//串口4中断服务程序
u8 UART4_RX_BUF[UART4_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

u16 UART4_RX_STA=0;       //接收状态标记	

//初始化IO 串口4 
//bound:波特率
void uart4_init(u32 bound){
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
    

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
    GPIO_Init(GPIOC,&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
       
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource10,GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_UART4);
        
    USART_DeInit(UART4);
        
    USART_InitStructure.USART_BaudRate=bound;
    USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_InitStructure.USART_Parity=USART_Parity_No;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init(UART4,&USART_InitStructure);
    
     NVIC_InitStructure.NVIC_IRQChannel=UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
    NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
    USART_Cmd(UART4,ENABLE);
	
//	USART_ClearFlag(UART4, USART_FLAG_TC);
	
#if EN_UART4_RX	
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启相关中断

	//Uart4 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;//串口4中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

#endif
	  while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET){};//等待发送结束 
}
u8 RecU4=0;
void UART4_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0xbb结尾)
	{
		Res =USART_ReceiveData(UART4);//(USART1->DR);	//读取接收到的数据
//    USART_SendData(USART1, Res);         //向串口1发送数据
//    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};
    USART_ClearITPendingBit(UART4, USART_IT_RXNE);
       
  } 
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
} 
#endif	

/**************************串口4*******************************/

void USART1_SendChar(u16 DataToSend)
{
	USART_SendData(USART1,DataToSend);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}	

void USART1_SendString(char *str)
{
	while(*str)
	{
			USART1_SendChar(*str);
			str++;
	}
}

void UART4_SendChar(u16 DataToSend)
{
	USART_SendData(USART1,DataToSend);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}	

void UART4_SendString(char *str)
{
	while(*str)
	{
			USART1_SendChar(*str);
			str++;
	}
}

void UART8_SendChar(u16 DataToSend)
{
	USART_SendData(USART1,DataToSend);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
}	

void UART8_SendString(char *str)
{
	while(*str)
	{
			USART1_SendChar(*str);
			str++;
	}
}
