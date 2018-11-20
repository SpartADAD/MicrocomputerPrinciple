/****************************82C55.c***********************/
#include "82C55.h"
#include "delay.h"
#include "stdio.h"
#include "main.h"


uint8_t xdata P8255_CTL _at_ 0xf803;
uint8_t xdata P8255_A _at_ 0xf800;
uint8_t xdata P8255_B _at_ 0xf801;
uint8_t xdata P8255_C _at_ 0xf802;

#define A0    P0^0  
#define A1    P0^1  

void C55_IORegister(uint8_t registerChoose)
{
//	switch()



}

void C55_Init(uint8_t group,uint8_t groupWorkMode,uint8_t Port,uint8_t PortInOrOut)
{
	P8255_CTL|=0x80;
//	C55_IORegister();
	switch(group)
	{
		case GROUP_A:
			groupWorkMode&=0x10;
			P8255_CTL|=(groupWorkMode<<5);
		break;
		
		case GROUP_B:
			groupWorkMode&=0x01;
			P8255_CTL|=(groupWorkMode<<2);
		break;
		
		default:
		break;
	}
	
	switch(Port)
	{
		case PORT_A:
			P8255_CTL|=(PortInOrOut<<4);
		break;
		
		case PORT_B:
			P8255_CTL|=(PortInOrOut<<2);
		break;
		
		case PORT_C_HIGH:
			P8255_CTL|=(PortInOrOut<<3);
		break;
		
		case PORT_C_LOW:
			P8255_CTL|=(PortInOrOut<<1);
		break;
		
		default:
		break;
	}
}	

void KeyReadBy82C55(void)
{
	uint8_t keyStatus =0;
	
	keyStatus = P8255_A;

	P8255_B=(~keyStatus);

}