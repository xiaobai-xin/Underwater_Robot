/*
 * 
 * D2&D4口功能说明：
  * D2 1->0计数器加一 0保持
  * D4 使能端 高电平有效
   
 * 主控仓-Arduino接线说明：
   主控仓-浮力舱接口  Arduino
  * GPIO D8       D2
  * GPIO D9       D4
  * GND           GND
 
 * SYN6288语音模块-Arduino接线说明：(硬件串口模式）
   语音模块       Arduino
  * TXD          RX
  * RXD          TXD
  
 * LCD 1602接线说明：
    LCD 1602     Arduino
   * VSS         GND
   * VDD         5V
   * V0          对比度调节 接电位器
   * RS          D12
   * RW          GND
   * Enable      D11
   * D4          D9
   * D5          D8
   * D6          D7
   * D7          D6
   * A           5V(背光）
   * K           GND(背光）
   * 其余接口无需接线
   
   *2021/10/13-btx
*/
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial yySerial(10, 13);//定义语音模块(TXD ,RXD)(软串口）
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



LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
int count;
int CarryFlag;//进位标志 值为1时进位
void synout(byte yyd[] , int len)//读一段文字函数
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
    yySerial.write(yuyindata[i]);
    Serial.write(yuyindata[i]);
  }
 yySerial.write(yihuo);//输出校验码
  Serial.write(yihuo);
  delay(100);
}                                     
void speak_lyd(int num)//漏油点语音播报
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
    case 8:
     length = sizeof(text7) / sizeof(byte);
     synout(text8, length);  
     break;
  }
}
void lcd_ShowNum(int count)//屏幕显示计数
{
    lcd.setCursor(0, 1);
    lcd.print(count);
}

void setup() 
{
    count=0;//计数器初始化
    CarryFlag=0;//进位标志初始化
    Serial.begin(9600);
    yySerial.begin(9600);
    length = sizeof(text0) / sizeof(byte);
    synout(text0, length);  //播放内容：启动成功
    pinMode(2, INPUT); //信号输出 接下位机gpio8
    pinMode(4, INPUT); //信号输出 接下位机gpio9
    lcd.begin(16, 2);
    lcd.print("count");
    lcd_ShowNum(count);
}


void loop() 
{
  //GPIO9为计数器使能信号，高电平有效
    if(digitalRead(4) == LOW)//计数器未开启，计数器始终置0，直到主控仓寻管开始，计数器有效
    {
        count=0;
        CarryFlag=0;//进位标志
    }
    else//计数器有效
    {
        while (digitalRead(2) == HIGH) //计数器加一条件：D2==HIGH->LOW&D4=HIGH
          {
                delay(200);
                CarryFlag=1;//进位标志
                
          } 
        while (digitalRead(2) == LOW)
        {
                if(CarryFlag==1)
                {
                      CarryFlag=0;
                      count++; 
                      speak_lyd(count);
                      lcd_ShowNum(count);
                      delay(200);
                      break;
                }
       
        }
    }
}
