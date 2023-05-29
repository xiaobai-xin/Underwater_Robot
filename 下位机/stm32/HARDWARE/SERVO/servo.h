#ifndef _SERVO_H
#define _SERVO_H
#include "sys.h"

#define servo1   1
#define servo2   2
#define servo3   3
#define servo4   4
#define servo5   5
#define servo6   6
#define servo7   7
#define servo10  10
#define servo11  11

#define pwm_angle_0        1000       //0度PWM
#define angletopwm_mul     22.222222  //角度换算PWM倍数

//初始化舵机接口
//进行初始化：1，不进行初始化：0
void Servo_PWM_Init(u8 s1,u8 s3,u8 s4,u8 s5,u8 s6,u8 s7,u8 s10);

void Servo_Analysis(u8 port,u8 angle);
#endif
