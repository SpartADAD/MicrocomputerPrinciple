/*************************82C55.h********************************/
#ifndef __82C55_H
#define __82C55_H

#include "main.h"
#define ROLE  2
#if  ROLE ==     1
#define STB_STATUS  PORTx_ReadBits(PORT_C,PORT_PIN_4)
#define STB_RESET		PORTx_ResetBits(PORT_C,PORT_PIN_4)
#define STB_SET			PORTx_SetBits(PORT_C,PORT_PIN_4)

#define BUSY_STATUS	PORTx_ReadBits(PORT_C,PORT_PIN_0)
#define BUSY_RESET	PORTx_ResetBits(PORT_C,PORT_PIN_0)
#define BUSY_SET		PORTx_SetBits(PORT_C,PORT_PIN_0)
#elif ROLE ==     2
#define STB_STATUS  PORTx_ReadBits(PORT_C,PORT_PIN_0)
#define STB_RESET		PORTx_ResetBits(PORT_C,PORT_PIN_0)
#define STB_SET			PORTx_SetBits(PORT_C,PORT_PIN_0)

#define BUSY_STATUS	PORTx_ReadBits(PORT_C,PORT_PIN_4)
#define BUSY_RESET	PORTx_ResetBits(PORT_C,PORT_PIN_4)
#define BUSY_SET		PORTx_SetBits(PORT_C,PORT_PIN_4)
#endif


#define PORT_A				0
#define PORT_B				1
/*C口高四位PC7-PC4和PORT_A组成A组*/
#define PORT_C_HIGH   2
/*C口低四位PC3-PC0和PORT_B组成B组*/
#define PORT_C_LOW		3
#define PORT_C				4

#define PORT_PIN_0    0
#define PORT_PIN_1    1
#define PORT_PIN_2    2
#define PORT_PIN_3    3
#define PORT_PIN_4    4
#define PORT_PIN_5    5
#define PORT_PIN_6    6
#define PORT_PIN_7    7

#define IO8255_MODE0	0
#define IO8255_MODE1 	1
#define IO8255_MODE2	2

//8255输入输出宏定义
#define IO8255_OUTPUT 0
#define IO8255_INPUT	1


//8255端口 初始化结构体类型定义
typedef struct
{
	uint8_t workMode;
	uint8_t inOrOut;
}C55PortInit_t;

typedef struct
{
	C55PortInit_t portAInit;
	C55PortInit_t portBInit;
	C55PortInit_t portCHInit;
	C55PortInit_t portCLInit;	
}C55Init_t;
void MyC55_Init(void);
void C55_Init(C55Init_t C55InitStuct);
void AToB(void);
void BReceiveNoSort(void);
void BReceiveSort(void);
uint8_t C55_ReceiveByte(uint8_t Port);
void C55_SendByte(uint8_t Port,uint8_t dataSend);
uint8_t C55_ReadBits(uint8_t Port, unsigned char Port_Pin_x);
void KeyReadBy82C55(void);
void SendOrReceive(void);
void MaoPaoSort(uint32_t dataLength,int *dataSorted);
#endif