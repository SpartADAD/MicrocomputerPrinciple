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


/**
	* @brief  82C55初始化函数 A口作为输出B口作为输入 C口高位做输出 低位做输入
  * @param  void
  * @retval void
  */
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
/**
	* @brief  82C55初始化函数
  * @param  C55InitStuct 初始化结构体 通过传递结构体对控制字进行赋值
  * @retval void
  */
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


/**
	* @brief  82C55某个端口发数函数 相当于改变端口状态
  * @param  Port 82C55某一个端口
	* @param  dataSend 要发送的字节
  * @retval void
  */
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
/**
	* @brief  82C55某个端口接受函数 得到当前端口8位的数据大小
  * @param  Port 82C55某一个端口
  * @retval dataReceive 读取端口当前的电平值得到8位返回值
  */
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
  * @brief  82C55 PORT口某位置位函数
  * @param  PORTx 某一GPIO口  
	* @param  PORT_Pin_x	某一GPIO口的某一位
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
	* @brief  82C55 PORT口某位复位函数
  * @param  PORTx 某一GPIO口  
	* @param  PORT_Pin_x	某一GPIO口的某一位
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
  * @brief  PORT口某位读取当前状态函数
  * @param  PORTx 某一PORT口  
  * @param  PORT_Pin_x	某一PORT口的某一位
  * @retval 某一PORT口某一位当前的状态
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
			returnStatus = portA & Port_Pin_x_BIN;
		break;
		
		case PORT_B:
			returnStatus = portB & Port_Pin_x_BIN;
		break;
		
		case PORT_C:
			returnStatus = portC & Port_Pin_x_BIN;
		break;
		
		
		default:
		break;
	}
	
	return (returnStatus>>Port_Pin_x);
}
/**
  * @brief  读取82C55（A口作为输入B口作为输出）通过开关控制led亮灭
  * @param  void
  * @retval void
  */
void KeyReadBy82C55(void)
{
	uint8_t keyStatus =0;
	
	keyStatus = P8255_A;

	P8255_B=~keyStatus;

}
/*定义发送的字节大小*/
#define DATA_LENGTH   20
/*定义发送的字节大小*/
static int xdata receiveFromB[DATA_LENGTH]={0};
/**
  * @brief  甲箱发数函数
  * @param  void
  * @retval void
  */
void AToB(void)
{
	uint8_t xdata i=0;
	uint8_t sendArray[DATA_LENGTH]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

	for(i=0;i<DATA_LENGTH;i++)
	{
		STB_SET;
		C55_SendByte(PORT_A,sendArray[i]);
		receiveFromB[i]=C55_ReceiveByte(PORT_B);
		STB_RESET;
		while(BUSY_STATUS);
	}
}
/*从A端口接受的数组*/
static int xdata receiveFromA[DATA_LENGTH]={0};
/**
  * @brief  乙箱接受函数
  * @param  void
  * @retval void
  */
void BReceiveSort(void)
{
	static uint8_t xdata i=0;
	static int xdata dataSort[DATA_LENGTH]={0};
	
	while(STB_STATUS);
	BUSY_SET;
	receiveFromA[i]=C55_ReceiveByte(PORT_B);
	dataSort[i]=receiveFromA[i];
	i++;
	
	if(i>=20)
	{
		/*开始排序*/
		MaoPaoSort(DATA_LENGTH,dataSort);
		/*排序结束*/
		for(i=0;i<DATA_LENGTH;i++)
		{
			HD7279ShowInt(receiveFromA[i]);
			DelayMs(1000);
		}
		i=0;
	}
	DelayMs(200);
	BUSY_RESET;

}
/**
	* @brief  发送或者接受 通过预编译宏下载到不同箱子上
  * @param  void
  * @retval void
  */
void SendOrReceive(void)
{
	#if  ROLE ==     1
		AToB();
	#elif ROLE ==     2
		BReceiveSort();
	#endif
}
/**
  * @brief  冒泡排序法 从左到右由大到小
  * @param  dataLength 排血数组长度
	* @param  dataSorted 要排序的数组
  * @retval void
  */
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