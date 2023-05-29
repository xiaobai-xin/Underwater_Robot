#include "sys.h"
#include "stdio.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "propeller.h"
#include "beep.h" 
#include "433m.h" 
#include "bno055.h" 
#include "dac.h"
#include "hp20x.h"
#include "api.h" 
#include "timer.h"
#include "adc.h"
#include "exti.h"
#include "servo.h" 


extern u8 RX_STATE;
extern u8 Packet_433M[10];
extern u8 gyr_state;
extern u8 GYR_Response[8];
extern u8 RecU5;

#include "sys.h"
#include "stdio.h"
#include "delay.h"
#include "api.h" 
#include "external.h" 
#include "api.h"
#include "propeller.h"


/**

    螺旋桨接口   螺旋桨T2【正】     螺旋桨T3【反】

                 螺旋桨T6【反】     螺旋桨T7【正】

                 螺旋桨T1【反】     螺旋桨T4【正】
								  左舵机【1端口】 右舵机【3端口】
								  深度传感器【2】端口
									树莓派USB接端盖ROV接口
									摄像头连接树莓派或主控仓摄像头接口
									注意：树莓派串口发送指令需要将AMA0改成USB0，然后连接主控仓运行即可
								顺时针桨叶旋转为正浆，逆时针旋转推水为反浆**/
								
void Forward(int sudu1,int sudu4)//前进
{   
    TJQ_Control(T1,sudu1,0);//左后
    TJQ_Control(T2,0,1);//左前
    TJQ_Control(T3,0,1);//右前
    TJQ_Control(T4,sudu4,1);//右后 


}

void TurnLeft(int sudu2,int sudu4)//左转
{
    TJQ_Control(T1,0,1);//左后
    TJQ_Control(T2,sudu2,1);//左前
    TJQ_Control(T3,0,1);//右前
    TJQ_Control(T4,sudu4,1);//右后 

}


void TurnRight(int sudu1,int sudu3)//右转
{
    TJQ_Control(T1,sudu1,0);//左后
    TJQ_Control(T2,0,1);//左前
    TJQ_Control(T3,sudu3,0);//右前
    TJQ_Control(T4,0,1);//右后 

}
void Downwater(float sudu5,float sudu6)//下潜
{
//    TJQ_Control(T1,0,0);//左后
//    TJQ_Control(T2,0,1);//左前
//	  TJQ_Control(T3,0,0);//右前
//    TJQ_Control(T4,0,1);//右后
    TJQ_Control(T6,sudu5,0);//左中
    TJQ_Control(T7,sudu6,1);//右中
}
void LeftPY(int sudu7,int sudu8)//左平移
{
   
    TJQ_Control(T1,sudu7,0);//左后
    TJQ_Control(T2,sudu8,1);//左前
	  TJQ_Control(T3,0,0);//右前
    TJQ_Control(T4,0,1);//右后
}
void RightPY(int sudu9,int sudu10)//右平移
{
    TJQ_Control(T1,0,0);//左后
    TJQ_Control(T2,0,1);//左前
    TJQ_Control(T3,sudu9,0);//右前
    TJQ_Control(T4,sudu10,1);//右后
}

void Stop()//停止
{
    TJQ_Control(T1,0,1);//左后
    TJQ_Control(T2,0,1);//左前
    TJQ_Control(T3,0,1);//右前
    TJQ_Control(T4,0,1);//右后 
    TJQ_Control(T6,0,1);//左中
    TJQ_Control(T7,0,1);//右中
}
void clear()//清除
{
  Servo_Set(1,60); //中间舵机
}

void collect()//收集
{
  Servo_Set(2,90); //左舵机
	Servo_Set(3,180); //右舵机
}
void duojichushihua()//初始化舵机
{
 Servo_Set(1,140); //中间舵机
	Servo_Set(2,180); //左舵机
	Servo_Set(3,90); //右舵机
	Visual_Alarm_Light(0,0,0);
}

int main(void)

{ 
	
	float sudu5=0;
  float sudu6=0;
	int yaw1=0;
	int ycha=0;
	int jishutt=50;
	delay_init(180);		    //初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
  SCC_TO_HUB_Init(9600);//单片机与USB HUB通讯端口初始化
	Internal_System_Init();//初始化程序，可以在api。c文件中找到
  Sensor_HP20X_Init();//深度传感器初始化
	Servo_Set(1,0); //舵机初始角度
	Servo_Set(3,180); //舵机初始角度
  //delay_ms(100);          //延时100ms
	while(jishutt>0)//方向角循环获取
	{
	jishutt=jishutt-1;
	Euler_Angle_Read();//方向角获取
	yaw1=yaw;//读取开机方向角
	}
	while(1)
	{  
		Euler_Angle_Read();//方向角获取
		ycha=yaw-yaw1;//当前位置与初始位置的差值
		if(ycha<=80&&ycha>=-20)//浅水区
		{
		Downwater(0,0); //下潜推进器停止
		}
		else if(ycha<=170&&ycha>80)//渐变区
		{
		Downwater(70,70); //下潜
		}
		else if(ycha<=360&&ycha>170)//深水区
		{
    if(Sensor_HP20X_GetDepth()<100)
		{// 深度小于10厘米
		  Downwater(90,90); //快速下潜
		 }
		 else if(Sensor_HP20X_GetDepth()<150)
		{// 深度小于15厘米
		  Downwater(70,70); //下潜推进器70%pwm推进
		 }
		 else if(Sensor_HP20X_GetDepth()<350)
		{// 深度小于35厘米
		  Downwater(60,60);
		} 
			else if(Sensor_HP20X_GetDepth()<450)
		{// 深度小于45厘米
		  Downwater(50,50); 
		 }
		else
		 {
		  Downwater(0,0); //下潜推进器停止
		 }				
		}	
	}
}		 
			 







