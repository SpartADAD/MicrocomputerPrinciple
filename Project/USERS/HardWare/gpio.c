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
	P1=~codeMy;

}
/*** @brief  流水灯2s切换 
			timeControl是半个周期的时间
			静态变量runTime用来计数 计算运行时间 由于本函数是5ms运行1次所以当runTime运行等于2倍的timeControl相当于1个周期=2s
runTime==timeControl半个周期时让led灯亮 另外半个周期让led灭
			ledIndex 是控制当前灯的序号，通过传入序号控制led
			外部中断内 控制全局变量gParam.flag的值通过改变 其大小改变流水灯样式

  * @param  void           
  * @retval None
  */
/*led的数量*/
#define LED_NUMBER     8
void WaterLight(void)
{
	static uint32_t xdata runTime=0;
	static char xdata ledIndex=0;
	uint16_t xdata timeControl=200;
	/*进行计时*/
	runTime++;
	if(runTime<=timeControl)
	{
		/*传入序号控制led*/
		GPIOx_ResetBits(GPIOP1,ledIndex);
	}
	else if(runTime>timeControl&&runTime<=timeControl*2)
	{
		GPIOx_SetBits(GPIOP1,ledIndex);
	}
	else if(runTime>timeControl*2)
	{
		/*1个周期后清空计数*/
		runTime=0;
		if(gParam.flag)
		{
			/*顺次控制P1.0到P1.7*/
			ledIndex++;
			/*回到循环开始*/
			if(ledIndex>=LED_NUMBER)
				ledIndex=0;
		}
		else
		{
			/*顺次控制P1.7到P1.0*/
			ledIndex--;
			/*回到循环开始*/
			if(ledIndex<0)
				ledIndex=LED_NUMBER-1;
		}
	}
}