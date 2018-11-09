
/*******************************main.c***********************************/

#include "STC15F2K60S2.h"
#include "gpio.h"
#include "motor.h"
#include "timer.h"
#include "interrupt.h"

gParam_t gParam={0};
void HardWareInit(void)
{
	/*定义5ms运行周期*/
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM0
			TIM0_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,56);
	#elif  RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM1
			TIM1_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,56);
	#endif
	
	EXHandlerInit(EX_INTERRUPT0,EX_INTERRUPT_BY_EDGE);
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
				WaterLight();
			}
		#endif

//		P1_0 =0;
//		MotorControl();
	}
}








