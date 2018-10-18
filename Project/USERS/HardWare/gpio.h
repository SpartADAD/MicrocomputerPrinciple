/***********************gpio.h************************/

#ifndef __GPIO_H
#define __GPIO_H


void GPIOx_ResetBits(unsigned char GPIOx,unsigned char GPIO_Pin_x);
void GPIOx_SetBits(unsigned short GPIOx,unsigned char GPIO_Pin_x);
unsigned char GPIOx_ReadBits(unsigned char GPIOx, unsigned char GPIO_Pin_x);

void KeyControl(void);
void ShowKeyValue(void);
#endif
