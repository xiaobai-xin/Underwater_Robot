/*
 * 
 * D2&D4口功能说明：
   接口（A2(8)，A4(9)）： 00    01      10     11
   状态：        初始 90°清除  45°清除            半收起
   
 * 主控仓-Arduino接线说明：
   主控仓-浮力舱接口  Arduino
  * GPIO D8       D2
  * GPIO D9       D4
  * GND           GND

 * 主控仓-Arduino接线说明：
   舵机           Arduino
  * 舵机          D3
  * 爪子          D5
  * GND          GND
 
 * SYN6288语音模块-Arduino接线说明：
   语音模块       Arduino
  * TXD          RXD
  * RXD          TXD
  
 
 * 主控仓-继电器接线说明：
   主控仓-浮力舱接口  
  * GPIO D10         继电器 

   *2021/9/17-btx
*/
#include <Servo.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define clear_time 1500 //清除时间设置
#define start_time 2500//
//SoftwareSerial yySerial(10, 5);//定义语音模块TXD-->6 ,RXD-->7  0（RX）、1（TX）(软串口）
int length = 0;  //语音内容长度
byte text0[] = {0xC6,0xF4,0xB6,0xAF,0xB3,0xC9,0xB9,0xA6};//启动成功
byte text1[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xD2,0xBB,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到一个漏油点
byte text2[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xC1,0xBD,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到两个漏油点
byte text3[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xC8,0xFD,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到三个漏油点
byte text4[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xCB,0xC4,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到四个漏油点
byte text5[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xCE,0xE5,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到五个漏油点
byte text6[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xC1,0xF9,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到六个漏油点
byte text7[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xC6,0xDF,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到七个漏油点
byte text8[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xB0,0xCB,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到八个漏油点
byte text9[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xBE,0xC5,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到九个漏油点
byte text10[] = {0xBC,0xEC,0xB2,0xE2,0xB5,0xBD,0xCA,0xAE,0xB8,0xF6,0xC2,0xA9,0xD3,0xCD,0xB5,0xE3};//检测到十个漏油点

Servo duoji1, duoji2;
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
int count=0;
void setup() {
  count=0;
  Serial.begin(9600);
  //yySerial.begin(9600);
  length = sizeof(text0) / sizeof(byte);
  synout(text0, length);  //播放内容
  pinMode(2, INPUT); //收起&清除控制 gpio8
  pinMode(4, INPUT); //半收起控制gpio9
  duoji1.attach(3);//舵机
  duoji2.attach(5);//爪子
  lcd.begin(16, 2);
  lcd.print("count");
}
//读一段文字函数
void synout(byte yyd[] , int len)
{
  int i = 0;
  byte yuyindata[206];
  byte yihuo = 0;

  yuyindata[0] = 0xFD;   //yuyin组装前缀控制符
  yuyindata[1] = 0x00;
  yuyindata[2] = len + 3;
  yuyindata[3] = 0x01;
  yuyindata[4] = 0x01;

  for (int i = 0; i < len; i++)   //yuyin组装正文
  {
    yuyindata[i + 5] = yyd[i];
  }

  for (int i = 0; i < len + 5; i++)    //循环输出
  {
    yihuo = yihuo ^ yuyindata[i];
    //yySerial.write(yuyindata[i]);
    Serial.write(yuyindata[i]);
  }
 //yySerial.write(yihuo);//输出校验码
  Serial.write(yihuo);
  delay(100);
}                                     
void speak_lyd(int num)
{
  switch(num)
  {
    case 0:
     length = sizeof(text0) / sizeof(byte);
     synout(text0, length);  
     break;
    case 1:
     length = sizeof(text1) / sizeof(byte);
     synout(text1, length);  
     break;
    case 2:
     length = sizeof(text1) / sizeof(byte);
     synout(text2, length);  
     break;
    case 3:
     length = sizeof(text3) / sizeof(byte);
     synout(text3, length);  
     break;
     case 4:
     length = sizeof(text4) / sizeof(byte);
     synout(text4, length);  
     break;
     case 5:
     length = sizeof(text5) / sizeof(byte);
     synout(text5, length);  
     break;
     case 6:
     length = sizeof(text6) / sizeof(byte);
     synout(text6, length);  
     break;
     case 7:
     length = sizeof(text7) / sizeof(byte);
     synout(text7, length);  
     break;
  }
}
void loop() 
{
    if (digitalRead(2) == LOW && digitalRead(4) == LOW) //初始状态
    {
      delay(200);
      if (digitalRead(2) == LOW && digitalRead(4) == LOW) //初始状态
  {
    duoji2.write(160);
    delay(100);
    duoji1.write(180);
    count=0;
    
  }
    }
    
  if (digitalRead(2) == LOW && digitalRead(4) == HIGH) //90°清除状态
  {
    duoji1.write(0);
    delay(100);
    duoji2.write(120);
     delay(clear_time);//清除时间
    count++;
    speak_lyd(count);
    
  }
  if (digitalRead(2) == HIGH && digitalRead(4) == LOW) //45°清除
  {
    duoji1.write(80);
    delay(100);
    duoji2.write(120);
    delay(clear_time);//清除时间
    count++;
    speak_lyd(count);
  }
  if (digitalRead(2) == HIGH && digitalRead(4) == HIGH) //半收起状态
  {
    duoji1.write(40);
    delay(100);
    duoji2.write(120);
  }
    lcd.setCursor(0, 1);
    lcd.print(count);
}
