/****************************82C55.c***********************/
#include "82C55.h"
#include "delay.h"
#include "stdio.h"
#include "main.h"
#include "HD7279.h"

uint8_t xdata P8255_CTL _at_ 0xf803;
uint8_t xdata P8255_A _at_ 0xf800;
uint8_t xdata P8255_B _at_ 0xf801;
uint8_t xdata P8255_C _at_ 0xf802;

#define A0    P0^0  
#define A1    P0^1  
void MyC55_Init(void)
{
	C55Init_t C55InitStucture={0};
	C55InitStucture.portAInit.workMode = IO8255_MODE0;
	C55InitStucture.portAInit.inOrOut =  IO8255_OUTPUT;
	
	C55InitStucture.portBInit.workMode = IO8255_MODE0;
	C55InitStucture.portBInit.inOrOut =  IO8255_INPUT;
	
	C55InitStucture.portCHInit.inOrOut = IO8255_OUTPUT;
	C55InitStucture.portCLInit.inOrOut = IO8255_INPUT;

	C55_Init(C55InitStucture);

}
void C55_Init(C55Init_t C55InitStuct)
{
	uint8_t xdata initCode = 0x80;
	
	//根据输入状态配置控制字并发送
	initCode|=(C55InitStuct.portAInit.workMode<<5);
	initCode|=(C55InitStuct.portAInit.inOrOut<<4);
	
	initCode|=(C55InitStuct.portBInit.workMode<<2);
	initCode|=(C55InitStuct.portBInit.inOrOut<<1);
	
	initCode|=(C55InitStuct.portCHInit.inOrOut<<3);
	initCode|=(C55InitStuct.portCLInit.inOrOut);
	
	P8255_CTL = initCode;
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
	uint8_t xdata portA = P8255_A;
	uint8_t xdata portB = P8255_B;
	uint8_t xdata portC = 0;
	switch(PORTx)
	{
		case PORT_A:
			portA |=(int)pow(2,PORT_Pin_x);
			P8255_A = portA;
		break;
		
		case PORT_B:
			portB |=(int)pow(2,PORT_Pin_x);
			P8255_B = portB;
		break;
		
		case PORT_C:
			portC = (PORT_Pin_x<<1)|0x01;
			P8255_CTL = portC;
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
	uint8_t xdata portA = P8255_A;
	uint8_t xdata portB = P8255_B;
	uint8_t xdata portC = 0;
	switch(PORTx)
	{
		case PORT_A:
			portA &=(~(int)pow(2,PORT_Pin_x));
			P8255_A =portA;
		break;
		
		case PORT_B:
			portB &=(~(int)pow(2,PORT_Pin_x));
			P8255_B = portB;
		break;
		
		case PORT_C:
			portC = (PORT_Pin_x<<1)&0xfe;
			P8255_CTL = portC;
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
	uint8_t xdata portA = P8255_A;
	uint8_t xdata portB = P8255_B;
	uint8_t xdata portC = P8255_C;
	unsigned char returnStatus=0;
	unsigned char Port_Pin_x_BIN=(int)pow(2,Port_Pin_x);
	
	switch(PORTx)
	{
		case PORT_A:
//			P8255_A|=Port_Pin_x_BIN;
			returnStatus = portA & Port_Pin_x_BIN;
		break;
		
		case PORT_B:
//			P8255_B|=Port_Pin_x_BIN;
			returnStatus = portB & Port_Pin_x_BIN;
		break;
		
		case PORT_C:
//			P8255_C|=Port_Pin_x_BIN;
			returnStatus = portC & Port_Pin_x_BIN;
		break;
		
		
		default:
		break;
	}
	
	return (returnStatus>>Port_Pin_x);
}

void KeyReadBy82C55(void)
{
	uint8_t keyStatus =0;
	
	keyStatus = P8255_A;

	P8255_B=~keyStatus;

}


void AToB(void)
{
	uint8_t sendArray[1]={'H'};

	STB_SET;
	C55_SendByte(PORT_A,sendArray[1]);
	STB_RESET;
	while(BUSY_STATUS);
}
uint8_t receiveFromA=0;
void BReceive(void)
{
//	uint8_t receiveFromA=0;
	while(STB_STATUS);
	BUSY_SET;
	receiveFromA=C55_ReceiveByte(PORT_A);
	HD7279ShowInt(receiveFromA);
	BUSY_RESET;
}

void SendOrReceive(void)
{
	#if  ROLE ==     1
		AToB();
	#elif ROLE ==     2
		BReceive();
	#endif
}
//void SendOrReceive(void)
//{
//	uint8_t xdata pc0 = BUSY_STATUS;
//	P8255_CTL=0x09;	
//  //STB_SET;
////	C55_SendByte(PORT_A,sendArray[1]);
////	STB_RESET;
////	while(BUSY_STATUS);
//}

