#ifndef __USART_H
#define __USART_H

#include "main.h"

#define USART_MODE_0   0
#define USART_MODE_1   1
#define USART_MODE_2   2
#define USART_MODE_3   3

void USART_SendData(uint8_t sendData);
void USART_Init(uint8_t USART_Mode,uint8_t baudRateDouble,uint32_t baudRate,uint8_t nightBitEnble);
#endif
