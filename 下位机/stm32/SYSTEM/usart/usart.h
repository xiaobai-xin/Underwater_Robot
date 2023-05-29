#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 



#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define UART5_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_UART5_RX	  	  1

#define UART8_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_UART8_RX	  	  1

#define UART4_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_UART4_RX	  	  1

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern u8  UART5_RX_BUF[UART5_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 UART5_RX_STA; 
extern u8  UART8_RX_BUF[UART8_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 UART8_RX_STA; 

extern u8  UART4_RX_BUF[UART4_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 UART4_RX_STA;


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void uart5_init(u32 bound);
void uart8_init(u32 bound);
void uart4_init(u32 bound);

void USART1_SendChar(u16 DataToSend);
void USART1_SendString(char *str);

void UART4_SendChar(u16 DataToSend);
void UART4_SendString(char *str);

void UART8_SendChar(u16 DataToSend);
void UART8_SendString(char *str);



#endif


