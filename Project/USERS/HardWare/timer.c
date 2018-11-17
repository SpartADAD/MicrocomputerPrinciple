/****************************timer.c********************************/

#include "timer.h"
#include "STC15F2K60S2.h"
#include "main.h"

/**
  * @brief  定时器0初始化函数 通过位与 位移操作求得lowValue 填入低位 highValue 填入高位的值 
  * @param  workMode: 工作模式，填入值宏定义  0-3              
  * @param  timerStartValue：   定时器装载值  
  * @retval None
  */
void TIM0_Init(uint16_t workMode,uint16_t timerStartValue)
{
		uint8_t lowValue =  0;
		uint8_t highValue =	0;
		switch(workMode)
		{
			case THIRTEEN_BIT_COUNT:  
				TMOD |= workMode;
				/*最大计数值0x1FFF*/
				timerStartValue&=0x1FFF;
				
				lowValue=timerStartValue&0x1F;
			  highValue=(timerStartValue>>5);
				TH0  = highValue;
				TL0  = lowValue;
				TR0=1;
			break;
			
			case SIXTEEN_BIT_COUNT:  
				TMOD |= workMode;
			  lowValue=timerStartValue&0xFF;
			  highValue=(timerStartValue>>8);
				TH0  = highValue;
				TL0  = lowValue;
				TR0=1;
			break;
			
			case EIGHT_BIT_AUTO_RELOUD_COUNT:  
				TMOD |= workMode;
				/*计数最大值*/
				timerStartValue&=0xFF;
			
				lowValue=timerStartValue;
			  highValue=timerStartValue;
				TH0  = highValue;
				TL0  = lowValue;
				TR0=1;
			break;
			
			case TWO_EIGHT_BIT_COUNT:  
				TMOD |= workMode;
				TH0  = highValue;
				TL0  = lowValue;
				TR0=1;
			break;
			
			default:
			
			break;
		}
}
/**
  * @brief  定时器1初始化函数 通过位与 位移操作求得lowValue 填入低位 highValue 填入高位的值 
  * @param  workMode: 工作模式，填入值宏定义  0-3              
  * @param  timerStartValue：   定时器装载值  
  * @retval None
  */
void TIM1_Init(uint16_t workMode,uint16_t timerStartValue)
{
		uint8_t lowValue =  0;
		uint8_t highValue =	0;
		switch(workMode)
		{
			case THIRTEEN_BIT_COUNT:  
				TMOD |= (workMode<<4);
				/*最大计数值0x1FFF*/
				timerStartValue&=0x1FFF;
				
				lowValue=timerStartValue&0x1F;
			  highValue=(timerStartValue>>5);
				TH1  = highValue;
				TL1  = lowValue;
				TR1=1;
			break;
			
			case SIXTEEN_BIT_COUNT:  
				TMOD |= (workMode<<4);
			  lowValue=timerStartValue&0xFF;
			  highValue=(timerStartValue>>8);
				TH1  = highValue;
				TL1  = lowValue;
				TR1=1;
			break;
			
			case EIGHT_BIT_AUTO_RELOUD_COUNT:  
				TMOD |= (workMode<<4);
				/*计数最大值*/
				timerStartValue&=0xFF;
				lowValue=timerStartValue;
			  highValue=timerStartValue;
				TH1  = highValue;
				TL1  = lowValue;
				TR1=1;
			break;
			
			default:
			break;
			
		}
}
/**
  * @brief  定时器0 1中断初使能函数
  * @param  timer: 选择定时器 0 或1              
  * @retval None
  */
void Timer_Interrupt(uint8_t timer)
{
	/*总开关中断*/
	EA=1;
	switch(timer)
	{
		case TIM0:
			ET0=1;
		break;
	
		case TIM1:
			ET1=1;
		break;
		
		default:
			
		break;
	}
}
