#include "api.h" 
#include "pwm.h"
#include "exti.h"
#include "led.h"
#include "propeller.h"
#include "433m.h" 
#include "usart.h"	
#include "bno055.h" 
#include "beep.h" 
#include "delay.h" 
#include "hp20x.h"
#include "dac.h"
#include "timer.h"
#include "adc.h"
#include "buoyancy.h" 
#include "servo.h"


/** NO.0001
   *系统内部初始化函数
   */
void Internal_System_Init(void)
{
	//Exti_Port_Init(11);
  //433M设置
  WM_433M_Init(9600);//遥控器433模块初始化
  WM_433M_SET("AT+C012");//遥控器433模块通讯ID号
  //姿态传感器设置
  Sensor_BNO055_Init(115200,OPERATION_MODE_NDOF);
  //推进器初始化
  TJQ_Init();
  //蜂鸣器初始化
  Buzzer_Init();
  //电池电压检测初始化
  Bat_Vol_Det_Init();
  //灯光报警模块初始化
  Visual_Alarm_Light_Init();
  //灯光报警模块显示白光
  Visual_Alarm_Light(255,255,255);
	Buoyancy_GPIO_Init();
	
	Exti_Port_Init(1);
  //初始化完成蜂鸣器响声提示
  BEEP=1;
  delay_ms(100);
  BEEP=0;
  delay_ms(100);
  BEEP=1;
  delay_ms(100);
  BEEP=0;
  delay_ms(100);  
  BEEP=1;
  delay_ms(100);
  BEEP=0;
  delay_ms(100);   
}
/*********************************基础区*********************************/
/**
 *使用时统一初始化，用户可调用应用函数实现功能
 *
 */
/** NO.0002
   *433M模块端口初始化函数
   */
void WM_433M_Init(u32 bound)
{
   SET433MPIN_Init();   //433M设置引脚配置 高电平透传模式/低电平设置模式
   uart_init(bound);     //433M   串口1通讯初始化
}
/** NO.0003
   *433M模块频段配置函数
   */
void WM_433M_SET(char *AT)
{
	SET_433M(AT);
}

/** NO.0004
   *传感器BNO055端口初始化函数
   */
void Sensor_BNO055_Init(u32 bound,u8 mode)
{
	u8 BNO055_Init_Result=3;
	
	uart5_init(bound);    //BNO055 串口5通讯初始化
	
	delay_ms(1000);
  while(BNO055_Init_Result != Init_Successful)
  {
      BNO055_Init_Result=BNO055_Init(mode);//BNO055初始化配置
    
    USART_SendData(USART1, BNO055_Init_Result);         //向串口1发送数据
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET){};
  }
}
/** NO.0005
   *传感器BNO055数据读取函数
   */
void Sensor_BNO055_READ(u8 addr,u8 length)
{
	BNO055_READ(addr,length);
}
/** NO.0006
   *传感器BNO055数据写入函数
   */
void Sensor_BNO055_Write(u8 addr,u8 data)
{
	BNO055_WRITE(addr,data);
}

/** NO.0007
   *传感器BNO055数据解析函数
   */
u8 Sensor_BNO055_Response_Analysis(u8 *Res_data,u8 bit_num)//数据包首地址 第几位数据  类型
{
   BNO055_Response_Analysis(Res_data,bit_num);//数据包首地址 第几位数据  类型
}

/** NO.0008
   *传感器BNO055读取欧拉角数据(直接调用yaw、roll和pitch)
   */
void Euler_Angle_Read(void)
{
   BNO055_Euler_Angle_Read(BNO055_Response);
}

/** NO.0009
   *推进器端口初始化
   */
void TJQ_Init(void)
{
//方向引脚初始化  
  T_DIR_Init();
//速度引脚初始化  
  TIM3_PWM_Init(100-1,45-1);	//90M/90=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz
  TIM8_PWM_Init(100-1,45-1);  
//反馈引脚初始化  
  TIM4_Cap_Init(65536-1,90-1);   //以1Mhz的频率计数
  TIM5_Cap_Init(0XFFFFFFFF,90-1);//以1Mhz的频率计数
//定时器初始化  
  TIM7_Int_Init(5000-1,9000-1);	//定时器时钟90M，分频系数9000，所以90M/9000=10Khz的计数频率，计数5000次为500ms   
}
/** NO.0010
   *推进器控制       ：参数3   序号     速度     方向
   *参数范围         ：        1-8     0-499    0-1
   */
void TJQ_Control(u8 t_num,u16 t_speed,u8 t_dir)
{
  Propeller_Set(t_num,t_speed,t_dir);
}
/** NO.0011
   *推进器测速       ：参数1   序号         
   *参数范围         ：        1-8       
   */
u16 TJQ_RateFB_Read(u8 t_num)
{
  return TJQ_FB_Read(t_num);
}
/** NO.0012
   *推进器速度控制   ：参数3   序号     转速     方向
   *参数范围         ：        1-8     0-5000    0-1
   */
void TJQ_Speed_Control(u8 t_num,u16 target_v,u8 t_dir)
{
   Propeller_Set(t_num,PWM_Calculate(target_v,TJQ_RateFB_Read(t_num)),t_dir);
}
/** NO.0013
   *蜂鸣器端口初始化
   */
void Buzzer_Init(void)
{
   BEEP_Init();
}
/** NO.0014
   *蜂鸣器响
   */
void Buzzer_Ring(void)
{
   BEEP=1;
}
/** NO.0015
   *蜂鸣器不响
   */
void Buzzer_No_Ring(void)
{
   BEEP=0;
}
/** NO.0016
   *灯光报警初始化   
   */
void Visual_Alarm_Light_Init(void)
{
  RGB_LED_Init();
}
/** NO.0017
   *灯光报警设置     ：参数3   绿光     红光    蓝光
   *参数范围         ：        0~255    0~255   0~255
   */
void Visual_Alarm_Light(u8 green,u8 red,u8 blue)
{
	RGB_LED_Write_24Bits(green,red,blue);
}
//亮灯颜色设定，其他颜色以此类推
/** NO.0018
   *灯光报警红光
   */
void RGB_LED_Red(void)//红光
{ 
	RGB_LED_Write_24Bits(0, 0xff, 0);
}
/** NO.0019
   *灯光报警绿光
   */
void RGB_LED_Green(void)//绿光
{
	RGB_LED_Write_24Bits(0xff, 0, 0);
}
/** NO.0020
   *灯光报警蓝光
   */
void RGB_LED_Blue(void)//蓝光
{
	RGB_LED_Write_24Bits(0, 0, 0xff);
}
/** NO.0021
   *灯光报警熄灭
   */
void RGB_LED_Off(void)//熄灭
{
	RGB_LED_Write_24Bits(0, 0, 0);
}
/** NO.0022
   *电池电压读取初始化            
   */
void Bat_Vol_Det_Init(void)
{
   Adc_Init();
}
/** NO.0023
   *电池电压数据读取             
   */
float Battery_Voltage_Detection(void)
{
  return Get_Bat_Vol();
}
/** NO.0024
   *遥控按键动作判断   ：参数1   1~20 
   *返回值：1~16返回 1（按下） 0（松开）；17~20 返回遥杆数值   
   */
/*
#define BT_UP            1
#define BT_DOWN          2
#define BT_LEFT          3
#define BT_RIGHT         4

#define BT_TRIANGLE      5
#define BT_CROSS         6
#define BT_SQUARE        7
#define BT_CIRCLE        8

#define BT_L1            9
#define BT_L2            10
#define BT_R1            11
#define BT_R2            12
#define BT_L3            13
#define BT_R3            14

#define BT_SELECT        15
#define BT_START         16

#define BT_LX            17
#define BT_LY            18
#define BT_RX            19
#define BT_RY            20

*/
u8 Remote_Control(u8 button)
{
  return Remote_Control_Button(button);
}
/** NO.0025
   *单片机与USB HUB通讯端口初始化             
   */
void SCC_TO_HUB_Init(u32 bound)
{
	uart8_init(bound);          
}
/************************************************************************/
/*********************************扩展区*********************************/
/**用户可根据提供的函数进行应用，也可根据自己的需求定义其他功能
 *
 *
 */

/** NO.1001
   *浮力舱接口初始化             
   */

void Buoyancy_Init(u8 type)//新旧版本选择
{
  switch(type)
  {
    case GPIO_Ver:
    {
      Buoyancy_GPIO_Init();
      break;
    }
    case UART_Ver:
    {
      //待补充
      break;
    }   
    default:break;
  }
}
/** NO.1002
   *浮力舱状态设置             
   */  
void Buoyancy_Control(u8 state)
{
  Buoyancy_GPIO_Control(state);
}  
/** NO.1003
   *舵机角度设置             
   */
void Servo_Set(u8 port,u8 angle)
{
  Servo_Analysis(port,angle);
}
/** NO.1004
   *外部中断独立初始化     ：参数1   port             
   *参数范围              ：        Sensor_1~Sensor_11(1~11)      
   */
void Exti_Port_Init(u8 port)
{
   EXTIX_Indepent_Init(port);
}
/** NO.1005
	 * 传感器检测       :字节4 红外传感器状态，检测到，状态为0
	 * 字节位          :  bit15   bit14   bit13   bit12   bit11   bit10   bit9   bit8   bit7   bit6   bit5   bit4   bit3   bit2   bit1   bit0    
	 * <接口>
	 *      S1        :   -       -       -       -       -       0       0      0      0      0      0      0      0      0      0      1     
	 *      S2        :   -       -       -       -       -       0       0      0      0      0      0      0      0      0      1      0
	 *      S3        :   -       -       -       -       -       0       0      0      0      0      0      0      0      1      0      0
	 *      S4        :   -       -       -       -       -       0       0      0      0      0      0      0      1      0      0      0
	 *      S5        :   -       -       -       -       -       0       0      0      0      0      0      1      0      0      0      0
	 *      S6        :   -       -       -       -       -       0       0      0      0      0      1      0      0      0      0      0     
	 *      S7        :   -       -       -       -       -       0       0      0      0      1      0      0      0      0      0      0
	 *      S8        :   -       -       -       -       -       0       0      0      1      0      0      0      0      0      0      0
	 *      S9        :   -       -       -       -       -       0       0      1      0      0      0      0      0      0      0      0
	 *      S10       :   -       -       -       -       -       0       1      0      0      0      0      0      0      0      0      0
	 *      S11       :   -       -       -       -       -       1       0      0      0      0      0      0      0      0      0      0
	 */

u8 Sensor_State_Analysis(u8 Sensor_num)
{
	u8 turn_place=0;
  u8 Sensor_State_Check=0;    
  u16 Sensor_State_analy=0;
	
	turn_place=Sensor_num-1;
  Sensor_State_analy=Sensor_State_All&(0x0001<<turn_place);
	Sensor_State_analy=Sensor_State_analy>>turn_place;
  Sensor_State_Check=(u8)Sensor_State_analy;
  return Sensor_State_Check;
}
/** NO.1006
   *深度传感器初始化
   */
void Sensor_HP20X_Init(void)
{
  HP20X_GPIO_Init();
	HP20X_Init();
}
/** NO.1007
   *深度传感器深度数据读取
   */
float Sensor_HP20X_GetDepth(void)
{
    float Depth_Value;
    Depth_Value=HP20X_getDepth();
		return Depth_Value;
}
/** NO.1008
   *探照灯线性调光初始化      ：参数2   sl1      sl2    
   *参数范围                  ：        0~1      0~1   
   */
void Searchlight_Init(u8 sl1,u8 sl2)
{
	if(sl1==1)
	{
		Dac1_Init();//探照灯接口1初始化
	}
	if(sl2==1)
	{
		Dac2_Init();//探照灯接口2初始化 
	}
}
/** NO.1009
   *探照灯线性调光设置      ：参数1   vol             
   *参数范围                ：        300~2800        
   */
void Searchlight_1_Set(u16 vol)
{	
	if(vol>2800)
	{
	  vol=2800;
	}
	Dac1_Set_Vol(vol);
}
/** NO.1010
   *探照灯线性调光设置      ：参数1   vol             
   *参数范围               ：        300~2800      
   */
void Searchlight_2_Set(u16 vol)
{	
	if(vol>2800)
	{
	  vol=2800;
	}
	Dac2_Set_Vol(vol);
}
/************************************************************************/
