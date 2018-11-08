/****************************gpio.c********************************/

#include "timer.h"
#include "STC15F2K60S2.h"
#include "main.h"
#include "gpio.h"
#include "interrupt.h"


static uint8_t runFlag=0;
void SetRunFlag(void)
{
	runFlag=1;
}

uint8_t GetRunFlag(void)
{
	if(runFlag)
	{
		runFlag =0;
		return 1;	
	}
	return 0;
}
static  uint32_t xdata timeCnt=0;
void TIM0_Handler() interrupt 1 
{
	
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM0
		timeCnt++;
		if(timeCnt>PERIOD_RUN)
		{
			timeCnt=0;
			SetRunFlag();
		}
	#else
		
	#endif
}


void TIM1_Handler() interrupt 3
{
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM1
    timeCnt++;
		if(timeCnt>PERIOD_RUN)
		{
			timeCnt=0;
			SetRunFlag();
		}
	#else

	#endif
}

void EXHandlerInit(uint8_t EXNumber,uint8_t workMode)
{
	if(EXNumber==EX_INTERRUPT0)
	{
		EX0=1;
		IT0=workMode; 
	}
	else if(EXNumber==EX_INTERRUPT1)
	{
		EX1=1;
		IT1=workMode; 
	}
	EA = 1;
}

void EX0Handler(void) interrupt 0
{
	gParam.flag++;
	gParam.flag%=2;
	
}

void EX1Handler(void) interrupt 2
{




} 