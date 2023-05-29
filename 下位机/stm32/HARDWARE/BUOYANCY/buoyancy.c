#include "buoyancy.h" 
 

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化
void Buoyancy_GPIO_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟

  //GPIOD8,D9,D10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	
  //GPIO_SetBits(GPIOD,GPIO_Pin_10);//高电平
	GPIO_WriteBit(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10,Bit_RESET);//低电平
}
//GPIO9为使能信号，初始值为LOW,GPIO9==HIGH时，计数器启动

void Buoyancy_GPIO_Control(u8 state)
{
  switch(state)
  {
    case Hold://计数器保持
    {
      GPIO_SetBits(GPIOD,GPIO_Pin_9);//high
      GPIO_WriteBit(GPIOD,GPIO_Pin_8,Bit_RESET);
      break;
    }
    case Come_up://计数器++
    {
			GPIO_SetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9);//high
      break;
    }
    case Dive://下潜状态
    {
       GPIO_SetBits(GPIOD,GPIO_Pin_9);
      break;
    }
		/*case Shangfu:
		{
			
		}*/
    default:break;
  }
}

