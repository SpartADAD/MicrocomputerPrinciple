/****************************82C55.c***********************/
#include "82C54.h"
#include "main.h"
uint8_t xdata P8254_CTL _at_ 0xF903;
uint8_t xdata P8254_0 _at_ 0xF900;
uint8_t xdata P8254_1 _at_ 0xF901;
uint8_t xdata P8254_2 _at_ 0xF902;

uint8_t  P374       _at_ 0xFa00; 

void Init_8254(uint8_t count_x, uint8_t timerMode, uint8_t countTime,uint8_t codeMode)
{
	uint8_t lowValue=0;
	uint8_t highValue=0;
	uint8_t  initCode=0;
	
	count_x&=0x03;
	timerMode&=0x05;
	initCode = ((count_x << 6) | (timerMode << 1)) | 0X30 | codeMode;
	//先写低位，再写高位，选择二进制计数
	P8254_CTL = initCode;		
	//当为工作方式即方式0时，计数值需要减1
	if(timerMode == INTERRUPT_MODE)			
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
	uint32_t time0Cnt=P8254_0;
	static uint16_t timeDelay=0;
	static uint8_t rightShift=0x01;
	timeDelay++;
	if(gParam.c55LedMode)
	{
		if(time0Cnt%2)
		{
			P374=0x0f;
		}else
		{
			P374=0xf0;
		}
	}
	else
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

#define KEY_VALUE (P1&0x02)
void DiffFangBo(void)
{
	if(KEY_VALUE==0)
	{
		Init_8254(COUNT_0,SQUARE_WAVE_MODE,10,BINARY_COUNT);
	}
	else if(KEY_VALUE==1)
	{
		Init_8254(COUNT_0,SQUARE_WAVE_MODE,100,BINARY_COUNT);
	}
	else if(KEY_VALUE==2)
	{
		Init_8254(COUNT_0,SQUARE_WAVE_MODE,1000,BINARY_COUNT);
	}
	else if(KEY_VALUE==3)
	{
		Init_8254(COUNT_0,SQUARE_WAVE_MODE,10000,BINARY_COUNT);
	}
	
}
