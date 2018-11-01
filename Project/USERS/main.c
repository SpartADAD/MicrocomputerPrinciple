
/*******************************main.c***********************************/

#include "STC15F2K60S2.h"
#include "gpio.h"
#include "motor.h"
void main(void)
{
	P1=0xF0;
	while(1)
	{
		MotorControl();
//		MotorRotate(0,1);
//			KeyControl();
//			ShowKeyValue();
	}
}









