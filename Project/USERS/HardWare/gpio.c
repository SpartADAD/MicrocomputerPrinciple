/****************************gpio.c********************************/

#include "gpio.h"
#include "STC15F2K60S2.h"
#include "math.h"

enum
{
	GPIOPort0 = 0,
	GPIOPort1,
	GPIOPort2,
	GPIOPort3,
	GPIOPort4
}GPIOTypeDef_t;

void GPIOx_SetBits(unsigned char GPIOx,unsigned char GPIO_Pin_x)
{
		GPIOx |=(int)pow(2,GPIO_Pin_x);
}

void GPIOx_ResetBits(unsigned char GPIOx,unsigned char GPIO_Pin_x)
{
	switch(GPIOx)
	{
		case GPIOPort0:
			P0 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOPort1:
			P1 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOPort2:
			P2 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOPort3:
			P3 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOPort4:
			P4 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		default:
			
		break;
	}

}

unsigned char GPIOx_ReadBits(unsigned char GPIOx, unsigned char GPIO_Pin_x)
{
	switch(GPIO_Pin_x)
	{
		case GPIOPort0:
			P0|=GPIOPin;
			return ((P0&GPIOPin)!=0x00);
		break;
		
		case GPIOPort1:
			P1|=GPIOPin;
			return ((P1&GPIOPin)!=0x00);
		break;
		
		case GPIOPort2:
			P2|=GPIOPin;
			return ((P2&GPIOPin)!=0x00);
		break;
		
		case GPIOPort3:
			P3|=GPIOPin;
			return ((P3&GPIOPin)!=0x00);
		break;
		
		default:
		break;
	}
}