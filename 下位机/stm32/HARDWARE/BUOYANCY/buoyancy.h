#ifndef _BUOYANCY_H
#define _BUOYANCY_H
#include "sys.h"

#define Vent_Valve     PDout(10) //排气阀
#define Vacuum_Pump    PDout(9)  //真空泵
#define Inlet_Valve    PDout(8)  //进气阀

#define Hold           0         //保持状态
#define Come_up        1         //上浮状态
#define Dive           2         //下潜状态

void Buoyancy_GPIO_Init(void);
void Buoyancy_GPIO_Control(u8 state);
#endif
