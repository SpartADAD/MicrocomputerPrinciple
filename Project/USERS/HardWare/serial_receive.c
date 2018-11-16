#include "reg51.h"

#define uint  unsigned int
#define uchar unsigned char
#define ulong unsigned long

sbit P1_0 = P1^0;
sbit dat = P1^4;
sbit key = P1^5;
sbit cs  = P1^6;
sbit clk = P1^7;

uchar Receive_value;
uchar code baud_rate[]={0x98,0xcc,0xe6,0xf3,0xf9,0xfd};     //1200,2400,4800,9600,19200,38400--4MHZ

uchar code baud_rate1[] = {0xf4,0xfa,0xfd,0xfd,0xff};       //1200, 2400, 4800, 9600, 19200(SMOD=1) -- 5.5296MHz



uchar code code2[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b, 0x01, 0x80, 0x00, 0x6f}; //0,1,2,3,4,5,6,7,8,9 - . blank  error

unsigned char code number[]={0x1b,0x13,0x0b,0x03,
			     0x1a,0x12,0x0a,0x02,
			     0x19,0x11,0x09,0x01,
			     0x18,0x10,0x08,0x00};

void short_delay(void);
void long_delay(void);
void send_byte(uchar out_byte);
uchar receive_byte(void);
uchar key_read(void);
void led_write(uchar cmd, uchar dat);
void led_int_disp(uint IntData);


void main()
{
	uchar i;

	SCON=0x50;PCON=0x80;TMOD=0x20; AUXR = 0X00;

	TH1=baud_rate1[3];TL1=baud_rate1[3];
	
	RI = 0; EA = 1; ES = 1; TR1=1;

    while(1)
	{
	


	}



}

void UART_Interrupt_Receive(void) interrupt 4
{
 			



}






void short_delay(void)
{
 	uchar i;
	for(i = 0; i < 8; i++);
}

void long_delay(void)
{
	uchar i;
	for(i = 0; i < 0x30; i++);
}

void send_byte(uchar out_byte)
{
	uchar i;
	cs = 0;
	long_delay();
	for(i = 0; i < 8; i++)
	{
		if(out_byte & 0x80)
		{
			dat = 1;
		}else{
			dat = 0;
		}
		clk = 1;
		short_delay();
		clk = 0;
		short_delay();
		out_byte *= 2;
	}
	dat = 0;
}
uchar receive_byte(void)
{
 	uchar i,in_byte;
	dat = 1;
	long_delay();
	for(i=0;i<8;i++)
	{
	 	clk = 1;
		short_delay();
		in_byte *= 2;
		if(dat)
		{
		 	in_byte = in_byte|0x01;
		}
		clk = 0;
		short_delay();
	}
	dat = 0;
	return(in_byte);
}

uchar key_read(void)
{
 	send_byte(0x15);
	return(receive_byte( ));
}

void led_write(uchar cmd, uchar dat)
{
	send_byte(cmd);
	send_byte(dat);
}

void led_int_disp(uint IntData)
{
	uchar LCD_Data[8];
	uchar i;

	LCD_Data[0] = 12; LCD_Data[1] = 12; LCD_Data[2] = 12; 
	LCD_Data[3] = IntData / 10000; IntData = IntData % 10000;
	LCD_Data[4] = IntData /  1000; IntData = IntData %  1000;
	LCD_Data[5] = IntData /   100; IntData = IntData %   100;
	LCD_Data[6] = IntData /    10; IntData = IntData %    10;
	LCD_Data[7] = IntData /     1;

	for(i = 0; i< 8; i++)
	{
		LCD_Data[i] = code2[LCD_Data[i]];
	}
	for(i = 0; i < 8; i++)
	{
		led_write(0x97 - i, LCD_Data[i]);
	}

}











