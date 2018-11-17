
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
//	TMOD =0x20;SCON=0x50;
//	TH1=0xF4;TL1=0xF4;
//	TR1=1;ES=1;EA=1;AUXR&=0xfe;
	/*定义5ms运行周期*/
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM0
			TIM0_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,256-ONE_INTTEUPT_TIME);
			Timer_Interrupt(TIM0);
	#elif  RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM1
			TIM1_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,256-ONE_INTTEUPT_TIME);
			Timer_Interrupt(TIM1);
	#endif
	USART_Init(USART_MODE_1,1,9600,0);
	
//	EXHandlerInit(EX_INTERRUPT0,EX_INTERRUPT_BY_EDGE);
	
	/*HD7279初始化*/
	HD7279SendByte(CMD_RESET);
}
void main(void)
{
//	P1=0xF0;
	HardWareInit();
	while(1)
	{
		#ifdef RUN_PERIOD_BY_TIM
			if(GetRunFlag())
			{
				DelayMs(25);
				USART_SendData(84);
				HD7279ShowInt(gParam.receiveDataByUsart);
//				LEDShowInt(gParam.receiveDataByUsart);
//				WaterLight();
			}
		#endif
	}
}








