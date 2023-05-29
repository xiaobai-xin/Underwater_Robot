#include "433m.h" 
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "api.h"
#include "stdio.h"


u8 setmode=0;
u32 checksum=0;
u8 Packet_433M[10];
static u8 State_433MRx=0;
static u8 i_433M=0;
u8 RX_STATE=0;
void ItRecvPrc(u8 data)/*包头*ID*DATA*DATA*LXdata*LYdata*RXdata*RYdata*Checksum*包尾  {0xaa,myid,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0xbb}     */
{
   Packet_433M[i_433M]=data;

   i_433M++;
   if(State_433MRx==0)
   {  
     if(Packet_433M[0]==0xaa){State_433MRx=1;}
     else {Packet_433M[0]=0;i_433M=0;}
   }
   else if(State_433MRx==1)
   {
     if(i_433M==10)   
     {
       if(Packet_433M[9]==0xbb)
       {
         RX_STATE=1;
         i_433M=0;
         State_433MRx=0;
        }
     }
    }
}

void SET433MPIN_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);//GPIOF9,F10设置高，灯灭
}

void SET_433M(char *AT)
{
  SET433MPIN=0;
  delay_ms(500);
	USART1_SendString(AT);
  delay_ms(500);
  SET433MPIN=1;
  delay_ms(1000); 
}


u8 Remote_Control_Button(u8 button)          //遥控器数据解析  /*包头*ID*DATA*DATA*LXdata*LYdata*RXdata*RYdata*Checksum*包尾*/
{
  if(Packet_433M[0]!=0xaa||Packet_433M[9]!=0xbb)//检查数据包包头包尾是否正确
  {
    return loosen;
  }
//	float data[3]=0;
  switch(button)
  {
    case BT_UP:     
    {
      if(Packet_433M[3]==GP_UP)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_DOWN:     
    {
      if(Packet_433M[3]==GP_DOWN)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_LEFT:     
    {
      if(Packet_433M[3]==GP_LEFT)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_RIGHT:     
    {
      if(Packet_433M[3]==GP_RIGHT)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_TRIANGLE:     
    {
      if(Packet_433M[2]==GP_TRIANGLE)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_CROSS:     
    {
      if(Packet_433M[2]==GP_CROSS)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_SQUARE:     
    {
      if(Packet_433M[2]==GP_SQUARE)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_CIRCLE:     
    {
      if(Packet_433M[2]==GP_CIRCLE)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_L1:     
    {
      if(Packet_433M[3]==GP_L1)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_L2:     
    {
      if(Packet_433M[3]==GP_L2)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_R1:     
    {
      if(Packet_433M[2]==GP_R1)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_R2:     
    {
      if(Packet_433M[2]==GP_R2)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_L3:     
    {
      if(Packet_433M[2]==GP_L3)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_R3:     
    {
      if(Packet_433M[2]==GP_R3)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_SELECT:     
    {
      if(Packet_433M[3]==GP_SELECT)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_START:     
    {
      if(Packet_433M[3]==GP_START)
      {
         return press;
      }
      else return loosen;
      break;
    }
    case BT_LX:     
    {
      return GP_LX;
      break;
    }
    case BT_LY:     
    {
      return GP_LY;
      break;
    }
    case BT_RX:     
    {
      return GP_RX;
      break;
    }
    case BT_RY:     
    {
      return GP_RY;
      break;
    }
    default:break;
  }
}






