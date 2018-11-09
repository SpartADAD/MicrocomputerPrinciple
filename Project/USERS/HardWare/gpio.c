/****************************gpio.c********************************/

#include "gpio.h"
#include "STC15F2K60S2.h"
#include "math.h"
#include "main.h"
/**
  * @brief  GPIO口某位置位函数
  * @param  GPIOx 某一GPIO口  
	* @param  GPIO_Pin_x	某一GPIO口的某一位
  * @retval void
  */
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
/**
	* @brief  GPIO口某位复位函数
  * @param  GPIOx 某一GPIO口  
	* @param  GPIO_Pin_x	某一GPIO口的某一位
  * @retval void
  */
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
/**
	* @brief  GPIO口某位读取当前状态函数
  * @param  GPIOx 某一GPIO口  
	* @param  GPIO_Pin_x	某一GPIO口的某一位
  * @retval 某一GPIO口当前GPIO的状态
  */
unsigned char GPIOx_ReadBits(unsigned char GPIOx, unsigned char GPIO_Pin_x)
{
	unsigned char returnStatus=0;
	unsigned char GPIO_Pin_x_BIN=(int)pow(2,GPIO_Pin_x);
	
	switch(GPIOx)
	{
		case GPIOP0:
			P0|=GPIO_Pin_x_BIN;
			returnStatus = P0 & GPIO_Pin_x_BIN;
		break;
		
		case GPIOP1:
			P1|=GPIO_Pin_x_BIN;
			returnStatus = P1 & GPIO_Pin_x_BIN;
		break;
		
		case GPIOP2:
			P2|=GPIO_Pin_x_BIN;
			returnStatus = P2 & GPIO_Pin_x_BIN;
		break;
		
		case GPIOP3:
			P3|=GPIO_Pin_x_BIN;
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
	unsigned char HighFour=0;
	
	/*输入端置位操作*/
	P1|=0xf0;
	
	HighFour=(P1 & 0xf0);	
	P1= (~(HighFour>>4));

}
void ShowKeyValue(void)
{
	unsigned char HighFour=0;	
	unsigned char codeMy=0;
	unsigned char i=0;
	
  P1|=0xf0;
	HighFour= ((P1 & 0xf0)>>4);	
	/*输入端置位操作*/
	
	for(i=0;i<4;i++)
	{
		codeMy+=((HighFour&((int)pow(2,i)))>>i)*(i+1);
	}
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
#define LED_NUMBER     8
void WaterLight(void)
{
	static uint32_t xdata runTime=0;
	static uint8_t xdata ledIndex=0;
	uint16_t xdata timeControl=200-gParam.flag*150;
	
	runTime++;
	if(runTime<=timeControl)
	{
		GPIOx_ResetBits(GPIOP1,ledIndex);
	}
	else if(runTime>timeControl&&runTime<=timeControl*2)
	{
		GPIOx_SetBits(GPIOP1,ledIndex);
	}
	else if(runTime>timeControl*2)
	{
		runTime=0;
		ledIndex++;
		ledIndex%=LED_NUMBER;
	}
}