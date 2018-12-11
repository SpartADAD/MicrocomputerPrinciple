/****************************interrupt.c********************************/

#include "timer.h"
#include "STC15F2K60S2.h"
#include "main.h"
#include "gpio.h"
#include "interrupt.h"
#include "delay.h"
#include "82C55.h"
/*运行程序标志位*/
static uint8_t runFlag=0;
/*** @brief   运行程序标志位置1函数
  *  @param   void           
  *  @retval  None 
  */
void SetRunFlag(void)
{
	runFlag=1;
}
/*** @brief    得到当前运行标志位，若为1，便置0并且在主函数判断，使得主函数运行一次
  *  @param  	 void           
  *  @retval   为1主程序能够运行一次  为0主程序不运行
  */
uint8_t GetRunFlag(void)
{
	if(runFlag)
	{
		runFlag =0;
		return 1;	
	}
	return 0;
}
/*** @brief   定时器0中断 timeCnt计数，可能进一次中断的时间太短，通过软件增
							加计时时间
							通过预编译#if判断5ms运行周期由谁提供
  *  @param   void           
  *  @retval  None
  */
static  uint32_t xdata timeCnt=0;
void TIM0_Handler() interrupt 1 
{
	
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM0
		timeCnt++;
		if(timeCnt>=PERIOD_RUN)
		{
			timeCnt=0;
			SetRunFlag();
		}
	#else
		
	#endif
}

/*** @brief   定时器1中断 timeCnt计数，可能进一次中断的时间太短，通过软件增
							加计时时间
							通过预编译#if判断5ms运行周期由谁提供
  *  @param   void           
  *  @retval 	None  
  */
void TIM1_Handler() interrupt 3
{
	#if RUN_PERIOD_BY_TIM == FIVE_MS_RUN_BY_TIM1
    timeCnt++;
		if(timeCnt>=PERIOD_RUN)
		{
			timeCnt=0;
			SetRunFlag();
		}
	#else

	#endif
}
/*** @brief    外部中断初始化函数
  *  @param    EXNumber 初始化外部中断序号 0/1   
  *  @param    workMode 外部中断工作方式  EX_INTERRUPT_BY_LOW_LEVEL 低电平触发 EX_INTERRUPT_BY_EDGE边沿触发          
  *  @retval   None
  */
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
/*** @brief    外部中断0中断函数 gParam.flag 用来控制流水灯样式
  *  @param    void       
  *  @retval   None
  */
void EX0Handler(void) interrupt 0
{
	gParam.c55LedMode++;
	gParam.c55LedMode%=2;
//	gParam.flag++;
//	gParam.flag%=2;
//	P1=0xff;
}
/*** @brief    外部中断1中断函数 
  *  @param    void       
  *  @retval   None
  */
void EX1Handler(void) interrupt 2
{




} 
/*** @brief    串口中断函数
  *  @param    void       
  *  @retval   None
  */
void USART_Handler(void)	interrupt 4 
{
	if(RI)
	{
		RI=0;
		gParam.receiveDataByUsart = (uint8_t)SBUF;
	}
}
/*** @brief    中断优先级配置
  *  @param    void       
  *  @retval   None
  */
void Interrupt_Priority(uint8_t priority)
{
		IP |= priority;
}