/****************************82C55.c***********************/
#include "82C54.h"
#include "main.h"
#include "STC15F2K60S2.h"
#include "HD7279.h"

uint8_t xdata P8254_CTL _at_ 0xF903;
uint8_t xdata P8254_0 _at_ 0xF900;
uint8_t xdata P8254_1 _at_ 0xF901;
uint8_t xdata P8254_2 _at_ 0xF902;

uint8_t  P374       _at_ 0xFa00; 
void My82C54Init(void)
{
	CLK_DIV=0x40;
	#if C54_EXPERIMENT == C54_EXPERIMENT_1
			Init_82C54(COUNT_0, INTERRUPT_MODE,5,BINARY_COUNT);
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_2
			/**/
			Init_82C54(COUNT_1, SQUARE_WAVE_MODE,2000,BINARY_COUNT);
			Init_82C54(COUNT_2, SQUARE_WAVE_MODE,2000,BINARY_COUNT);
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_3
			
	#endif


}

void Init_82C54(uint8_t count_x, uint8_t counterMode, uint16_t countTime,uint8_t codeMode)
{
	uint8_t lowValue=0;
	uint8_t highValue=0;
	uint8_t  initCode=0;
	
	count_x&=0x03;
	counterMode&=0x07;
	initCode = ((count_x << 6) | (counterMode << 1)) | 0X30 | codeMode;
	//先写低位，再写高位，选择二进制计数
	P8254_CTL = initCode;		
	//当为工作方式即方式0时，计数值需要减1
	if(counterMode == INTERRUPT_MODE)			
	{
		countTime -= 1;
	}
	
	lowValue = (countTime & 0XFF);		//取低字节数
	highValue = (countTime >> 8) & 0XFF; 		//取高字节数
	switch(count_x)
	{
		case COUNT_0 :				//对应计数器0
			P8254_0 = lowValue;
			P8254_0 = highValue;
			break;
		
		case COUNT_1 :				//对应计数器1
			P8254_1= lowValue;
			P8254_1 = highValue;
			break;
		
		case COUNT_2 :				//对应计数器2
			P8254_2= lowValue;
			P8254_2 = highValue;
			break;
		
		default:
			
		break;
	}
}

void EXInterruptLed(void)
{
	static uint16_t timeDelay=0;
	static uint8_t rightShift=0x01;
	timeDelay++;
	if(gParam.c55LedMode==0)
	{
		if(timeDelay<=100)
		{
			P374=0xf0;
		}else if(timeDelay>100&&timeDelay<200)
		{
			P374=0x0f;
		}else
		{
			timeDelay=0;
		}
	}
	else if(gParam.c55LedMode==1)
	{
		
		if(timeDelay>=200)
		{
			timeDelay=0;
			rightShift=(rightShift<<1);
			if(rightShift==0)
			{
				rightShift=0x01;
			}
			P374=~rightShift;
		}
	}
}
void ShowCountTime(void)
{
	uint32_t xdata countTime1=P8254_0;
	uint32_t xdata countTime2=P8254_1;

}
#define KEY_VALUE (P1&0x03)
void DiffFangBo(void)
{
	static  xdata lastValue = 0;
	uint8_t key = KEY_VALUE;
	uint16_t xdata countTime1=P8254_0;
	
	if(lastValue==key)
	{	
		return;
	}
	
	if(KEY_VALUE==0)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,10,BINARY_COUNT);
		HD7279ShowInt(200000);
	}
	else if(KEY_VALUE==1)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,100,BINARY_COUNT);
		HD7279ShowInt(20000);
	}
	else if(KEY_VALUE==2)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,1000,BINARY_COUNT);
		HD7279ShowInt(2000);
	}
	else if(KEY_VALUE==3)
	{
		Init_82C54(COUNT_0,SQUARE_WAVE_MODE,10000,BINARY_COUNT);
		HD7279ShowInt(200);
	}
	lastValue = key;
}

void MyExperiment82C54(void)
{
	#if C54_EXPERIMENT == C54_EXPERIMENT_1
		 EXInterruptLed();
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_2
		 ShowCountTime();
	#elif	C54_EXPERIMENT == C54_EXPERIMENT_3
			DiffFangBo();
	#endif



}
