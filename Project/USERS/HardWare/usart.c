
/************************usart.c******************************/
#include "usart.h"
#include "main.h"
#include "timer.h"
#include "STC15F2K60S2.h"
/**
  * @brief  串口中断初始化函数
	* @param  void	
  * @retval none
  */
void USART_Interrupt_Init(void)
{
	EA = 1;
	ES = 1;
}
/**
  * @brief  串口中断初始化函数
	* @param  USART_Mode 串口工作模式
	* @param  baudRateDouble 波特率是否加倍开关控制 输入值 1或0
	* @param  baudRate 波特率	
	* @param  nightBitEnble是否启用第九位接受	
  * @retval none
  */
void USART_Init(uint8_t USART_Mode,uint8_t baudRateDouble,uint32_t baudRate,uint8_t nightBitEnble)
{
		uint8_t timer1Reload=0;
		SCON|=((USART_Mode<<6)|0x10);
		switch(USART_Mode)
		{
			case USART_MODE_0:
				/*SYSCLK /12 bits/s*/
			break;
			
			case USART_MODE_1:
				timer1Reload=(uint8_t)(256 - SYSCLK*(1+baudRateDouble)/baudRate/384);
				/*定时器1初始化为八位重装载定时器 作为波特率发生器*/
				TIM1_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,timer1Reload);
				PCON |= (baudRateDouble<<7);
			  /*指定定时器1为波特率发生器！！！*/
				AUXR&=0xfe;
			break;
			
			case USART_MODE_2:
				/*SYSCLK/64*2*BaudRateDouble bits/s*/
				SCON|=(nightBitEnble<<5);
			break;
			
			case USART_MODE_3:
				timer1Reload=(uint8_t)(256 - SYSCLK*(1+baudRateDouble)/baudRate/384);
				/*定时器1初始化为八位重装载定时器 作为波特率发生器*/
				TIM1_Init(EIGHT_BIT_AUTO_RELOUD_COUNT,timer1Reload);
				PCON |= (baudRateDouble<<7);
				SCON|=(nightBitEnble<<5);
				/*指定定时器1为波特率发生器！！！*/
				AUXR&=0xfe;
			break;
			
			default:
			break;
		}
		USART_Interrupt_Init();
}


/**
  * @brief  串口发数函数
	* @param  sendData 串口需要发送的数据	
  * @retval none
  */
void USART_SendData(uint8_t sendData)
{
	TI = 0;
	SBUF = sendData;
	/*等待发数完成*/
	while(!TI){};
	/*清除标志位*/
	TI = 0;
}




