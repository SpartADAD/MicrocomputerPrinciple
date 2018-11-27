/****************************82C55.c***********************/
#include "82C55.h"
#include "delay.h"
#include "stdio.h"
#include "main.h"


uint8_t xdata P8255_CTL _at_ 0xf803;
uint8_t xdata P8255_A _at_ 0xf800;
uint8_t xdata P8255_B _at_ 0xf801;
uint8_t xdata P8255_C _at_ 0xf802;

#define A0    P0^0  
#define A1    P0^1  

void C55_Init(uint8_t group,uint8_t groupWorkMode,uint8_t Port,uint8_t PortInOrOut)
{
	P8255_CTL|=0x80;
	switch(group)
	{
		case GROUP_A:
			groupWorkMode&=0x10;
			P8255_CTL|=(groupWorkMode<<5);
		break;
		
		case GROUP_B:
			groupWorkMode&=0x01;
			P8255_CTL|=(groupWorkMode<<2);
		break;
		
		default:
		break;
	}
	
	switch(Port)
	{
		case PORT_A:
			P8255_CTL|=(PortInOrOut<<4);
		break;
		
		case PORT_B:
			P8255_CTL|=(PortInOrOut<<2);
		break;
		
		case PORT_C_HIGH:
			P8255_CTL|=(PortInOrOut<<3);
		break;
		
		case PORT_C_LOW:
			P8255_CTL|=(PortInOrOut<<1);
		break;
		
		default:
		break;
	}
}	



void C55_SendByte(uint8_t Port,uint8_t dataSend)
{
	switch(Port)
	{
		case PORT_A:
			P8255_A = dataSend;
		break;
		
		case PORT_B:
			P8255_B = dataSend;
		break;
		
		case PORT_C:
			P8255_C = dataSend;
		break;
		
		default:
		break;
	}
}

uint8_t C55_ReceiveByte(uint8_t Port)
{
	uint8_t dataReceive= 0;
	switch(Port)
	{
		case PORT_A:
			dataReceive = P8255_A;
		break;
		
		case PORT_B:
			dataReceive = P8255_B;
		break;
		
		case PORT_C:
			dataReceive = P8255_C;
		break;
		
		default:
		break;
	}
	
	return dataReceive;
}
	
/**
  * @brief  GPIO口某位置位函数
  * @param  GPIOx 某一GPIO口  
	* @param  GPIO_Pin_x	某一GPIO口的某一位
  * @retval void
  */
void PORTx_SetBits(unsigned char PORTx,unsigned char PORT_Pin_x)
{
	switch(PORTx)
	{
		case PORT_A:
			P8255_A |=(int)pow(2,PORT_Pin_x);
		break;
		
		case PORT_B:
			P8255_B |=(int)pow(2,PORT_Pin_x);
		break;
		
		case PORT_C:
			P8255_C |=(int)pow(2,PORT_Pin_x);
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
void PORTx_ResetBits(unsigned char PORTx,unsigned char PORT_Pin_x)
{
	switch(PORTx)
	{
		case PORT_A:
			P8255_A &=(~(int)pow(2,PORT_Pin_x));
		break;
		
		case PORT_B:
			P8255_B &=(~(int)pow(2,PORT_Pin_x));
		break;
		
		case PORT_C:
			P8255_C &=(~(int)pow(2,PORT_Pin_x));
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
uint8_t PORTx_ReadBits(uint8_t PORTx, unsigned char Port_Pin_x)
{
	unsigned char returnStatus=0;
	unsigned char Port_Pin_x_BIN=(int)pow(2,Port_Pin_x);
	
	switch(PORTx)
	{
		case PORT_A:
//			P8255_A|=Port_Pin_x_BIN;
			returnStatus = P8255_A & Port_Pin_x_BIN;
		break;
		
		case PORT_B:
//			P8255_B|=Port_Pin_x_BIN;
			returnStatus = P8255_B & Port_Pin_x_BIN;
		break;
		
		case PORT_C:
//			P8255_C|=Port_Pin_x_BIN;
			returnStatus = P8255_C & Port_Pin_x_BIN;
		break;
		
		
		default:
		break;
	}
	
	return (returnStatus>>Port_Pin_x_BIN);
}

void KeyReadBy82C55(void)
{
	uint8_t keyStatus =0;
	
	keyStatus = P8255_A;

	P8255_B=(~keyStatus);

}
#define STB_STATUS  PORTx_ReadBits(PORT_C,PORT_PIN_4)
#define STB_RESET		PORTx_ResetBits(PORT_C,PORT_PIN_4)
#define STB_SET			PORTx_SetBits(PORT_C,PORT_PIN_4)

#define BUSY_STATUS	PORTx_ReadBits(PORT_C,PORT_PIN_0)
#define BUSY_RESET	PORTx_ResetBits(PORT_C,PORT_PIN_0)
#define BUSY_SET		PORTx_SetBits(PORT_C,PORT_PIN_0)

void AToB(void)
{
	uint8_t sendArray[1]={'H'};

	STB_SET;
	C55_SendByte(PORT_A,sendArray[1]);
	STB_RESET;
	while(BUSY_STATUS);
}

void BReceive(void)
{
	uint8_t receiveFromA=0;
	while(STB_STATUS);
	BUSY_SET;
	receiveFromA=C55_ReceiveByte();
	BUSY_RESET;
}

void SendAndReceive(void)
{
	uint8_t receiveFromA=0;
	
	C55_Init();
	
	STB_SET;
	C55_SendByte(PORT_A,sendArray[1]);
	
	STB_RESET;
	
	
	receiveFromA=C55_ReceiveByte();
	BUSY_RESET;



}

