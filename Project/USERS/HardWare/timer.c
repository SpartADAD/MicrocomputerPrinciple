/****************************gpio.c********************************/

#include "timer.h"
#include "STC15F2K60S2.h"
#include "math.h"


#include "delay.h"

void DelayMs(unsigned int timeMs)
{
	unsigned int xdata nMsCounter = 0;
	unsigned short xdata msCounter = 0;
	unsigned char xdata i = 0;
	for(nMsCounter = 0 ; nMsCounter < timeMs ; nMsCounter++)
	{
		for(msCounter = 0 ; msCounter < TIME_1_MS ; msCounter++)
		{
			i = 1;
		}
	}
}

void Delay10Us(unsigned int timeUs)
{
	unsigned int xdata nUsCounter = 0;
	unsigned char xdata usCounter = 0;
	for(nUsCounter = 0 ; nUsCounter < timeUs ; nUsCounter++)
	{
		for(usCounter = 0 ; usCounter < TIME_10_US ; usCounter++)
		{
		
		}
	}
}