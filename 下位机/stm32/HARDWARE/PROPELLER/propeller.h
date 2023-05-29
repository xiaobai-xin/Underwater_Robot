#ifndef _PROPELLER_H
#define _PROPELLER_H
#include "sys.h"

#define T1_DIR  PCout(0)
#define T2_DIR  PCout(1)
#define T3_DIR  PBout(15)
#define T4_DIR  PBout(14)
#define T5_DIR  PCout(2)
#define T6_DIR  PCout(3)
#define T7_DIR  PBout(13)
#define T8_DIR  PBout(12)


#define T1 1
#define T2 2
#define T3 3
#define T4 4
#define T5 5
#define T6 6
#define T7 7
#define T8 8

#define CW   0
#define CCW  1

#define TD1 PCout(0)
#define TD2 PCout(1)
#define TD3 PBout(15)
#define TD4 PBout(14)
#define TD5 PCout(2)
#define TD6 PCout(3)
#define TD7 PBout(13)
#define TD8 PBout(12)

void T_DIR_Init(void);
void Propeller_Set(u8 t_num,u16 t_speed,u8 t_dir);

u16 PWM_Calculate(u16 target_v,u16 current_v);

#endif
