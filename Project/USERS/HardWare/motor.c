/****************************gpio.c********************************/
#include "motor.h"
#include "gpio.h"
#include "STC15F2K60S2.h"
#include "math.h"
#include "main.h"
#include "delay.h"

#define CLOCK_WISE		        1
#define COUNTER_CLOCK_WISE		0

void MotorControl(void)
{
	uint32_t xdata vel = 0;
	vel=10+((MOTOR_VEL_HIGH<<1)|MOTOR_VEL_LOW)*30;
	
	if(MOTOR_SWITCH)
	{
		if(MOTOR_ROTATE_DIRECTION)
		{
			MotorRotate(CLOCK_WISE,vel);
		}
		else
		{
			MotorRotate(COUNTER_CLOCK_WISE,vel);	
		}
	}
}
#define SEQUENCE    4
void MotorRotate(uint8_t rotateDirection,uint32_t rotateVel)
{
	uint8_t xdata sequence=0;
	uint8_t xdata myCode=0;
	if(rotateDirection)
	{
		for(sequence = 0; sequence<SEQUENCE;sequence++)
		{
			myCode=pow(2,sequence);
			
			P1=myCode;
			DelayMs(rotateVel);
			
			myCode=myCode|(myCode<<1);
			if(myCode>0x0f)
			{
				myCode=0x09;
			}
			
			P1=myCode;
			DelayMs(rotateVel);
		}
	}
	else
	{
		for(sequence = SEQUENCE-1; sequence>0;sequence--)
		{
			myCode=pow(2,sequence);
			
			P1=myCode;
			DelayMs(rotateVel);
			
			myCode=myCode|(myCode>>1);
			if(myCode==0x01)
			{
				myCode=0x09;
			}
			
			P1=myCode;
			DelayMs(rotateVel);
		}
	}

}
