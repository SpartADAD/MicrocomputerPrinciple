
/*******************************main.c***********************************/

#include "STC15F2K60S2.h"
#include "gpio.h"
#include "motor.h"
void main(void)
{
	while(1)
	{
		MotorControl();
	}
}









