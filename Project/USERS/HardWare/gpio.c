/****************************gpio.c********************************/

#include "gpio.h"
#include "STC15F2K60S2.h"
#include "math.h"

const enum
{
	GPIOP0 = 0,
	GPIOP1,
	GPIOP2,
	GPIOP3,
	GPIOP4
}GPIOTypeDef_t;

void GPIOx_SetBits(unsigned char GPIOx,unsigned char GPIO_Pin_x)
{
	switch(GPIOx)
	{
		case GPIOP0:
			P0 |=(int)pow(2,GPIO_Pin_x);
		break;
		
		case GPIOP1:
			P1 |=(int)pow(2,GPIO_Pin_x);
		break;
		
		case GPIOP2:
			P2 |=(int)pow(2,GPIO_Pin_x);
		break;
		
		case GPIOP3:
			P3 |=(int)pow(2,GPIO_Pin_x);
		break;
		
		case GPIOP4:
			P4 |=(int)pow(2,GPIO_Pin_x);
		break;
		
		default:
			
		break;
	}
		
}

void GPIOx_ResetBits(unsigned char GPIOx,unsigned char GPIO_Pin_x)
{
	switch(GPIOx)
	{
		case GPIOP0:
			P0 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOP1:
			P1 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOP2:
			P2 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOP3:
			P3 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		case GPIOP4:
			P4 &=(~(int)pow(2,GPIO_Pin_x));
		break;
		
		default:
			
		break;
	}

}

unsigned char GPIOx_ReadBits(unsigned char GPIOx, unsigned char GPIO_Pin_x)
{
	unsigned char returnStatus=0;
	unsigned char GPIO_Pin_x_BIN=(int)pow(2,GPIO_Pin_x);
	
	switch(GPIOx)
	{
		case GPIOP0:
			returnStatus = P0 & GPIO_Pin_x_BIN;
		break;
		
		case GPIOP1:
			returnStatus = P1 & GPIO_Pin_x_BIN;
		break;
		
		case GPIOP2:
			returnStatus = P2 & GPIO_Pin_x_BIN;
		break;
		
		case GPIOP3:
			returnStatus = P3 & GPIO_Pin_x_BIN;
		break;
		
		default:
		break;
	}
	
	return (returnStatus>>GPIO_Pin_x);
}

#define GET_BIT_NUMBER    4
void KeyControl(void)
{
	unsigned char HighFour= (P1 & 0xf0);	
	P1= (~(HighFour>>4));

}
void ShowKeyValue(void)
{
	unsigned char HighFour= ((P1 & 0xf0)>>4);	
	unsigned char codeMy=0;
	unsigned char i=0;
	for(i=0;i<4;i++)
	{
		codeMy+=((HighFour&((int)pow(2,i)))>>i)*i;
	}
	GPIOx_SetBits(1,2);
	GPIOx_SetBits(1,3);
//	if(HighFour==0x08)
//	{
//		GPIOx_ResetBits(1,0);
//		GPIOx_ResetBits(1,1);
//	}
//	else if(HighFour==0x04)
//	{
//		GPIOx_SetBits(1,0);
//		GPIOx_ResetBits(1,1);
//	}else if(HighFour==0x02)
//	{
//		GPIOx_ResetBits(1,0);
//		GPIOx_SetBits(1,1);
//	}else if (HighFour==0x01)
//	{
//		GPIOx_SetBits(1,0);
//		GPIOx_SetBits(1,1);
//	}else
//	{
//		GPIOx_SetBits(1,0);
//		GPIOx_SetBits(1,1);
//	}
	P1=~codeMy;

}