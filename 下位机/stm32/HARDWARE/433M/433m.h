#ifndef __433M_H
#define __433M_H
#include "sys.h"



/*****************************
Ò£¿ØÆ÷½âÎöº¯Êý
//key  			value	 msg   action
//·½¿é  0			fe		2	
//²æ²æ  1			fd		2
//Ô²È¦  2     fb		2 	 
//Èý½Ç  3			f7		2	   
//R1    4			ef		2		 
//R2    5			df		2		 
//ÓÒÒ¡¸Ë6			-    X4Y5  
//×óÒ¡¸Ë7			-    X6Y7	 
//L2    8			fe		3    
//L1    9			fd		3    
//ÉÏ°´¼ü10			fb		3    
//×ó°´¼ü11			f7		3	
//ÏÂ°´¼ü12 		ef		3
//ÓÒ°´¼ü13			df		3
//SELECT14		bf		3
//START 15		7f		3
*****************************/
/****************************************/
/*¼üÖµ
 *
 */
#define GP_UP            0xfb //3
#define GP_DOWN          0xef //3
#define GP_LEFT          0xf7 //3
#define GP_RIGHT         0xdf //3

#define GP_TRIANGLE      0xf7 //2
#define GP_CROSS         0xfd //2
#define GP_SQUARE        0xfe //2
#define GP_CIRCLE        0xfb //2

#define GP_L1            0xfd //3
#define GP_L2            0xfe //3
#define GP_R1            0xef //2
#define GP_R2            0xdf //2
#define GP_L3            0x7f //2
#define GP_R3            0xbf //2

#define GP_SELECT        0xbf //3
#define GP_START         0x7f //3

#define GP_LX 4
#define GP_LY 5
#define GP_RX 6
#define GP_RY 7
/*****************************************/

/*****************************************/
/*±êÖ¾
 *
 */
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


#define press             1
#define loosen            0









#define SET433MPIN  PAout(8)

//typedef struct KAPI_433Core KAPI_433Core;
void ItRecvPrc(u8 data);
void Proc433Msg(u8 *msg);
void SET433MPIN_Init(void);
void SET_433M(char *AT);
u8 Remote_Control_Button(u8 button);//Ò£¿ØÆ÷°´¼ü¶¯×÷ÅÐ¶Ïº¯Êý
 				    
#endif
