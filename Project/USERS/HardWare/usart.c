
/************************usart.c******************************/
#include "usart.h"
#include "main.h"
#include "timer.h"
#include "STC15F2K60S2.h"
void USART_Interrupt_Init(void)
{
	EA = 1;
	ES = 1;
}
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



void USART_SendData(uint8_t sendData)
{
	TI = 0;
	SBUF = sendData;
	while(!TI){};/*等待发数完成*/
	/*清除标志位*/
	TI = 0;
}




