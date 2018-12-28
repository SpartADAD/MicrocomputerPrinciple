
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
#include "82c55.h"
#include "82c54.h"
#include "ADDA.h"
gParam_t gParam={0};
void HardWareInit(void)
{
	/*设置串口中断高优先级*/
	//Interrupt_Priority(0x10);
	
	/*定义5ms运行周期*/
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM0
			/*定时器0 8位自动重装载 初始值56*/
			TIM0_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,256-ONE_INTTEUPT_TIME);
			/*使能中断定时器0中断*/
			Timer_Interrupt(TIM0);
	#elif  RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM1
			/*定时器1 8位自动重装载 初始值56*/
			TIM1_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,256-ONE_INTTEUPT_TIME);
			/*使能中断定时器1中断*/
			Timer_Interrupt(TIM1);
	#endif
	/*外部中断使能*/
	EXHandlerInit(EX_INTERRUPT0,EX_INTERRUPT_BY_EDGE);	
	//USART_Init(USART_MODE_1,1,9600,0);
	/*上电延时等数码管能用*/
	DelayMs(25);
	/*HD7279初始化*/
	//HD7279SendByte(CMD_RESET);
//	MyC55_Init();

	My82C54Init();
}
void main(void)
{
	HardWareInit();
	while(1)
	{
		#ifdef RUN_PERIOD_BY_TIM
			/*5ms运行周期*/
			if(GetRunFlag())
			{
					FinalTest();
//					HD7279ShowInt(gParam.readKey);
//					HD7279ShowInt(gParam.adcValue);
//				  AdcHD7279Show();
				  //P374=0xf0;
					
			}
		#endif
	}
}

/*5ms运行周期*/
static uint32_t daoJiShi = 0;
void FinalTest(void)
{
	static uint8_t ledShowCode = 0x01;
	static uint32_t runTime = 0;
	static uint8_t daoJiShiShow = 10;
	if(gParam.finalUpdate)
	{
		gParam.finalUpdate = 0;
		daoJiShi = 0;
		runTime = 0;
		daoJiShiShow =10;
	}
	
	if(daoJiShi<=2001)
	{
		daoJiShi++;
		runTime++;
		switch(gParam.finalMode)
		{
			case LEFT_TO_RIGHT:
				if(runTime>=200)
				{
					ledShowCode = ledShowCode<<1;
					runTime=0;
					daoJiShiShow--;
				}
				if(ledShowCode>0x80||ledShowCode==0x00)
				{
					ledShowCode=0x01;
				}
			break;
			
			case RIGHT_TO_LEFT:
				if(runTime>=200)
				{
					ledShowCode = ledShowCode>>1;
					runTime=0;					
					daoJiShiShow--;
				}
				if(ledShowCode>0x80||ledShowCode==0x00)
				{
					ledShowCode=0x80;
				}
			break;
			
			default:
			break;
		}
		
	}
	P374 = ~ledShowCode;
	HD7279ShowInt(daoJiShiShow);



}





