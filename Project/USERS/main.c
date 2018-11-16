
/*******************************main.c***********************************/

#include "STC15F2K60S2.h"
#include "gpio.h"
#include "motor.h"
#include "timer.h"
#include "interrupt.h"
#include "usart.h"
#include "delay.h"
#include "main.h"
#include "HD7279.h"
gParam_t gParam={0};
void HardWareInit(void)
{
	/*设置串口中断高优先级*/
	Interrupt_Priority(0x10);

	/*定义5ms运行周期*/
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM0
			TIM0_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,256-ONE_INTTEUPT_TIME);
	#elif  RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM1
			TIM1_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,256-ONE_INTTEUPT_TIME);
	#endif
	USART_Init(USART_MODE_1,0,9600,1);
	EXHandlerInit(EX_INTERRUPT0,EX_INTERRUPT_BY_EDGE);
	
	/*HD7279初始化*/
	HD7279SendByte(CMD_RESET);
}
void main(void)
{
//	P1=0xF0;
	uint8_t da=1;
	HardWareInit();
	while(1)
	{
		#ifdef RUN_PERIOD_BY_TIM
			if(GetRunFlag())
			{
				USART_SendData(0xA5);
				
				HD7279ShowInt(0xA5);
//				WaterLight();
			}
		#endif
	}
}








