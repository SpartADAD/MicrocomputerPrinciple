/****************************82C55.c***********************/
#include "82C55.h"
#include "delay.h"
#include "stdio.h"
#include "main.h"
#include "HD7279.h"
#include "string.h"

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
	uint8_t xdata dataReceive= 0;
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

#define DATA_LENGTH   20
static int xdata receiveFromB[DATA_LENGTH]={0};
void AToB(void)
{
	uint8_t xdata i=0;
	//uint8_t sendArray[DATA_LENGTH]={20,19,18,17,16,15,14,13,55,22,33,44,54,65,78,46,63,126,52,40};
	uint8_t sendArray[DATA_LENGTH]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	for(i=0;i<DATA_LENGTH;i++)
	{
		STB_SET;
		C55_SendByte(PORT_A,sendArray[i]);
		receiveFromB[i]=C55_ReceiveByte(PORT_B);
		STB_RESET;
		while(BUSY_STATUS);
	}
	
	/*显示一下哈*/
//	for(i=0;i<DATA_LENGTH;i++)
//	{
//		HD7279ShowInt(receiveFromB[i]);
//	}
//	STB_RESET;
}

static int xdata receiveFromA[DATA_LENGTH]={0};
void BReceiveNoSort(void)
{
	uint8_t xdata i=0;
	while(STB_STATUS);
	BUSY_SET;
	receiveFromA[i]=C55_ReceiveByte(PORT_B);
	HD7279ShowInt(receiveFromA[i]);
	BUSY_RESET;
}
void BReceiveSort(void)
{
	static uint8_t xdata i=0;
	static int xdata dataSort[DATA_LENGTH]={0};
	
	while(STB_STATUS);
	BUSY_SET;
	receiveFromA[i]=C55_ReceiveByte(PORT_B);
	C55_SendByte(PORT_A,dataSort[i]);
	i++;
	
	if(i>=20)
	{
		for(i=0;i<DATA_LENGTH;i++)
		{
			dataSort[i]=receiveFromA[i];
		}
		/*开始排序*/
		MaoPaoSort(DATA_LENGTH,dataSort);
		/*排序结束*/
		for(i=0;i<DATA_LENGTH;i++)
		{
			HD7279ShowInt(dataSort[i]);
			DelayMs(1000);
		}
		i=0;
		
	}
//	HD7279ShowInt(receiveFromA[i]);
	DelayMs(200);
	BUSY_RESET;

}
void SendOrReceive(void)
{
	#if  ROLE ==     1
		AToB();
	#elif ROLE ==     2
		BReceiveSort();
	#endif
}
void MaoPaoSort(uint32_t dataLength,int *dataSorted)
{
	//比较的轮数
  uint32_t xdata i=0;  
	 //每轮比较的次数
  uint32_t xdata j=0;
	int temp=0;
	for (i=0; i<dataLength-1; ++i)  //比较n-1轮
	{
			for (j=0; j<dataLength-1-i; ++j)  //每轮比较n-1-i次,
			{
					if (dataSorted[j] < dataSorted[j+1])
					{
							temp = dataSorted[j];
							dataSorted[j] = dataSorted[j+1];
							dataSorted[j+1] = temp;
					}
			}
	}

}