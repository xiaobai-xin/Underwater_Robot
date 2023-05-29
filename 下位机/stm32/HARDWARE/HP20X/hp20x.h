#ifndef __HP20X_H
#define __HP20X_H
#include "sys.h"



extern char F_VarIT_I2cAck;
extern unsigned long PressBuf;
extern long AltitudeBuf;
extern long TemperatureBuf;
extern float SensorData_P;
extern float SensorData_T;
extern float SensorData_A;
extern float __SENSOR_P__;
extern unsigned char Read_TPH;

/*****************************************************************************************************************/
/*
     HP20X 深度传感器接口定义
     根据实际接入的引脚对以下宏定义内容进行修改匹配
*/
#define HP20X_GPIO_CLOCK_Init()       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)

#define HP20X_I2C_PORT                GPIOB
#define HP20X_SCL_PIN                 GPIO_Pin_7
#define HP20X_SDA_PIN                 GPIO_Pin_6



//IO配置输入输出操作       {HP20X_I2C_PORT->MODER&=~(3<<(num*2));HP20X_I2C_PORT->MODER|=0<<num*2;}   num为对应SDA通讯线
#define HP20X_SDA_IN()                {HP20X_I2C_PORT->MODER&=~(3<<(6*2));HP20X_I2C_PORT->MODER|=0<<6*2;}	//PB11配置为输入模式
#define HP20X_SDA_OUT()               {HP20X_I2C_PORT->MODER&=~(3<<(6*2));HP20X_I2C_PORT->MODER|=1<<6*2;} //PB11配置为输出模式
//IO????????	 
#define SCL_OUT                       PBout(7) //SCL
#define SDA_OUT                       PBout(6) //SDA	 
#define SDA_IN                        PBin(6)  //SDA 

/*****************************************************************************************************************/
#define true 1
  
float HP20X_getDepth(void);
void HP20X_READ(void);
void HP20X_GPIO_Init(void);
void HP20X_Init(void);
void Hp20x_ReadPressureAndTemperature(void);
void Hp20x_ReadAltitude(void);
void Hp20x_ReadPressure(void);
void Hp20x_ReadTemperature(void);
void Hp20x_ReadAlt(void);

void Hp20X_WriteCmd(unsigned char uCmd);
void I2c_WriteByte(unsigned char databuf);
unsigned char I2c_ReadByte(unsigned char endbyte);
void I2c_Start(void);
void I2c_Stop(void);
void I2c_Error(void);
void I2c_Ack(void);
void I2c_NoAck(void);
				    
#endif
