/***********************gpio.h************************/

#ifndef __GPIO_H
#define __GPIO_H


void GPIOx_ResetBits(unsigned char GPIOx,unsigned char GPIO_Pin_x);
void GPIOx_SetBits(unsigned char GPIOx,unsigned char GPIO_Pin_x);
unsigned char GPIOx_ReadBits(unsigned char GPIOx, unsigned char GPIO_Pin_x);

void KeyControl(void);
void ShowKeyValue(void);


#define GPIO_PIN_0    0
#define GPIO_PIN_1    1
#define GPIO_PIN_2    2
#define GPIO_PIN_3    3
#define GPIO_PIN_4    4
#define GPIO_PIN_5    5
#define GPIO_PIN_6    6
#define GPIO_PIN_7    7



#define	GPIOP0  0
#define	GPIOP1  1
#define	GPIOP2  2
#define	GPIOP3  3 
#define	GPIOP4  4

#endif
