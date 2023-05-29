#ifndef __API_H
#define __API_H
#include "sys.h"


#define GPIO_Ver     1
#define UART_Ver     2

void Internal_System_Init(void);//系统内部初始化

void WM_433M_Init(u32 bound);//433M模块端口初始化函数
void WM_433M_SET(char *AT);//433M模块频段配置函数

void Sensor_BNO055_Init(u32 bound,u8 mode);//传感器BNO055端口初始化函数
void Sensor_BNO055_READ(u8 addr,u8 length);//传感器BNO055数据读取函数
void Sensor_BNO055_Write(u8 addr,u8 data);//传感器BNO055数据写入函数
u8 Sensor_BNO055_Response_Analysis(u8 *Res_data,u8 bit_num);//数据包首地址 第几位数据  类型
void Euler_Angle_Read(void);//传感器BNO055读取欧拉角数据(直接调用yaw、roll和pitch)


void TJQ_Init(void);//推进器端口初始化
void TJQ_Control(u8 t_num,u16 t_speed,u8 t_dir);//推进器控制函数
u16 TJQ_RateFB_Read(u8 t_num);//推进器测速函数 待补充
void TJQ_Speed_Control(u8 t_num,u16 target_v,u8 t_dir);


void Buzzer_Init(void);//蜂鸣器端口初始化

u8 Sensor_State_Analysis(u8 Sensor_num);//传感接口状态解析函数

//void RGB_Init(void);
//void RGB_Set(u8 R_color,u8 G_color,u8 B_color);
void Visual_Alarm_Light_Init(void);//灯光报警初始化              
void Visual_Alarm_Light(u8 green,u8 red,u8 blue);//灯光报警模块颜色设置：绿色，红色，蓝色；0~255/0x00~0xff            
void RGB_LED_Red(void);
void RGB_LED_Green(void);
void RGB_LED_Blue(void);//灯光报警显示蓝色  
void RGB_LED_Off(void);//灯光报警熄灭

void Sensor_HP20X_Init(void);//深度传感器初始化
float Sensor_HP20X_GetDepth(void);//深度传感器深度数据读取

void Searchlight_Init(u8 sl1,u8 sl2);//探照灯线性调光初始化
void Searchlight_1_Set(u16 vol);//探照灯线性调光设置
void Searchlight_2_Set(u16 vol);//探照灯线性调光设置

void Internal_Temp_And_Humi_Init(void);//内部温湿度传感器初始化
u8 Internal_Temp_Read(void);//内部温湿度传感器温度数据读取             
u8 Internal_Humi_Read(void);//内部温湿度传感器湿度数据读取 

void Bat_Vol_Det_Init(void);//电池电压检测初始化
float Battery_Voltage_Detection(void);

u8 Remote_Control(u8 button);//遥控按键动作判断

void SCC_TO_HUB_Init(u32 bound);


void Servo_Set(u8 port,u8 angle);

void Exti_Port_Init(u8 port);
void Exti_SET(u8 state);
u8 Sensor_State_Analysis(u8 Sensor_num);
              
#endif
