/*
	T4×óÇ°  T1ÓÒÇ°
	T3×óºó  T2ÓÒºó
	2021/7/26 zxq
*/
#include "external.h" 
#include "api.h"
#include "propeller.h"
#include "servo.h" 
#include "buoyancy.h" 
#include "sys.h"

//USBÍ¨Ñ¶¿ØÖÆ±à³Ì½çÃæ
int jsq=0;//¼ÆÊıÆ÷±äÁ¿
int yuan=0;//¼ÆÊıÆ÷±äÁ¿
int fang=0;//¼ÆÊıÆ÷±äÁ¿
int cha=0;//²îÖµ±äÁ¿
//³õÊ¼ÔË¶¯ËÙ¶È
float one=50;//1¼¶Æ«ÒÆ·ù¶Èµ÷Õû×ËÌ¬³õÊ¼ËÙ¶È
float two=40;//2¼¶Æ«ÒÆ·ù¶Èµ÷Õû×ËÌ¬³õÊ¼ËÙ¶È
float three=30;//3¼¶Æ«ÒÆ·ù¶Èµ÷Õû×Ë³õÊ¼ËÙ¶È
float four=20;//4¼¶Æ«ÒÆ·ù¶Èµ÷Õû×ËÌ¬³õÊ¼ËÙ¶È
float mind=50;//Ç°½ø³õÊ¼ËÙ¶È



	void URAT8_DATA_Analysis(u8 data)
{
	switch(data)
	{
		case 'A' :
		{//×ó×ªone×ªËÙ
     jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,one,1);
	  TJQ_Control(T3,0,1);
    TJQ_Control(T4,one,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);	
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'S' :
		{//×ó×ª230
      //Ö´ĞĞÓï¾ä
     jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,two,1);
	  TJQ_Control(T3,0,0);
    TJQ_Control(T4,two,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'D' :
		{//×ó×ª100
			//Ö´ĞĞÓï¾ä
    jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,three,1);
	  TJQ_Control(T3,0,0);
    TJQ_Control(T4,three,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'F' :
		{//×ó×ª50
			//Ö´ĞĞÓï¾ä
		jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Buoyancy_GPIO_Control(Hold);//LOW
		}
	  TJQ_Control(T1,0,0);
    TJQ_Control(T2,four,1);
	  TJQ_Control(T3,0,0);
    TJQ_Control(T4,four,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		Servo_Set(1,0); 
		Servo_Set(3,90); 
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'G' :
		{
			//Ö´ĞĞÓï¾ä
    jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		 Buoyancy_GPIO_Control(Hold);//LOW
		}
		TJQ_Control(T1,0,0);
    TJQ_Control(T2,mind+2,1);//ÓÒºó
	  TJQ_Control(T3,mind,0);//×óºó
    TJQ_Control(T4,0,0);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		Servo_Set(1,0); 
		Servo_Set(3,0);
	//	Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'H' :
		{//ÓÒ×ª50ËÙ¶È
			//Ö´ĞĞÓï¾ä
		jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		 Buoyancy_GPIO_Control(Hold);//LOW
		}
		TJQ_Control(T1,four,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,four,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		Servo_Set(1,0); 
		Servo_Set(3,90);
	//	Buoyancy_GPIO_Control(Hold);//LOW
		
			break;
		}
		case 'J' :
		{//ÓÒ×ª100ËÙ¶È
			//Ö´ĞĞÓï¾ä
		jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,three,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,three,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'K' :
		{//ÓÒ×ª200ËÙ¶È
			//Ö´ĞĞÓï¾ä
    jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
			Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,two,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,two,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
		case 'L' :
		{//ÓÒ×ª400ËÙ¶È
			//Ö´ĞĞÓï¾ä
	   jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
		if(jsq<=0)
		{
		Visual_Alarm_Light(0,0,0);
		Buoyancy_GPIO_Control(Hold);//LOW
		Servo_Set(1,0); 
		Servo_Set(3,180); 
		}
		TJQ_Control(T1,one,1);
    TJQ_Control(T2,0,1);
	  TJQ_Control(T3,one,0);
    TJQ_Control(T4,0,1);
    TJQ_Control(T6,0,0);
    TJQ_Control(T7,0,1);
		//Buoyancy_GPIO_Control(Hold);//LOW
			break;
		}
			case 'q' :
		{//¼ì²âµ½·½¿é-À¶µÆµãÁÁ
			//Ö´ĞĞÓï¾ä
			if(jsq<=0)
			{
					
			Visual_Alarm_Light(0,255,0);//G R 
				
				jsq=15;//ÓÃÀ´ÉèÖÃµÆµãÁÁµÄÊ±¼
			Buoyancy_GPIO_Control(Come_up);//ÊÕ¼¯
		  
			Buoyancy_GPIO_Control(Come_up);//++
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
			}
			break;
		}
		case 'y' :
		{//¼ì²âµ½Ô²ĞÎ-ºìµÆµãÁÁ
			//Ö´ĞĞÓï¾ä
			if(jsq<=0)
			{
			Visual_Alarm_Light(0,255,0);
			jsq=15;//ÓÃÀ´ÉèÖÃµÆµãÁÁµÄÊ±¼ä
			Buoyancy_GPIO_Control(Come_up);//++
			Servo_Set(1,90); 
			Servo_Set(3,90); 
			}
			else
			{
			 jsq=jsq-1;//ÓÃÀ´¿ØÖÆµÆÏ¨ÃğµÄÊ±¼ä
			}
			break;
		}
		case 'z' :
		{//¼ì²âµ½w
			//Ö´ĞĞÓï¾ä
			mind=mind+1;
			break;
		}
		case 'x' :
		{//¼ì²âµ½w
			//Ö´ĞĞÓï¾ä
			mind=mind-1;
			break;
		}
		case 'w' :
		{//¼ì²âµ½w
			//Ö´ĞĞÓï¾ä
			one=one-1;
			break;
		}
		case 'e' :
		{//¼ì²âµ½e
			//Ö´ĞĞÓï¾ä
			two=two-1;
			break;
		}
	  case 'r' :
		{//¼ì²âµ½r
			//Ö´ĞĞÓï¾ä
			three=three-1;
			break;
		}
		case 't' :
		{//¼ì²âµ½t
			//Ö´ĞĞÓï¾ä
			four=four-1;
			break;
		}
		case 'p' :
		{//¼ì²âµ½p
			//Ö´ĞĞÓï¾ä
			one=50;//1¼¶Æ«ÒÆ·ù¶Èµ÷Õû×ËÌ¬×î´óËÙ¶È
      two=40;//2¼¶Æ«ÒÆ·ù¶Èµ÷Õû×ËÌ¬×î´óËÙ¶È
      three=30;//3¼¶Æ«ÒÆ·ù¶Èµ÷Õû×ËÌ¬×î´óËÙ¶È
      four=50;//4¼¶Æ«ÒÆ·ù¶Èµ÷Õû×ËÌ¬×î´óËÙ¶È
      mind=50;////Ç°½ø×î´óËÙ¶È;//ËÙ¶È¸´Î»
			break;
		}
		case 'V'://Í£Ö¹
		{
    TJQ_Control(T1,0,0);//×óºó
    TJQ_Control(T2,0,1);//×óÇ°
	  TJQ_Control(T3,0,1);//ÓÒÇ°
    TJQ_Control(T4,0,1);//ÓÒºó
    TJQ_Control(T6,0,0);//×óÖĞ
    TJQ_Control(T7,0,1);//ÓÒÖĞ
		Buoyancy_GPIO_Control(Hold);//LOW
		}
		case 'M':
		{
			Buoyancy_GPIO_Control(Hold);//LOW
		}
		case 'N':
		{
			Buoyancy_GPIO_Control(Come_up);//++ HIGH
		}
		default:
		{
			//Ö´ĞĞÓï¾ä
			
			break;
		}
	}
}
