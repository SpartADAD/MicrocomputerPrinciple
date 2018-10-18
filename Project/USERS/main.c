
/*******************************main.c***********************************/

#include "STC15F2K60S2.h"
#include "gpio.h"

//sbit key=P1^4;
void main(void)
{
		while(1)
		{
//			if(GPIOx_ReadBits(1,4))
////			if(key)
//			{
//				GPIOx_ResetBits(1,0);
//				GPIOx_ResetBits(1,1);
//				GPIOx_ResetBits(1,2);
//				GPIOx_ResetBits(1,3);
//			}
//			else
//			{
//				GPIOx_SetBits(1,0);
//				GPIOx_SetBits(1,1);
//				GPIOx_SetBits(1,2);
//				GPIOx_SetBits(1,3);
//			}

//			KeyControl();
			ShowKeyValue();


		
		
		}







}









