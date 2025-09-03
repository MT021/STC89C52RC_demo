#include <REGX52.H>
#include "delay.h"

sbit SER = P3^4;
sbit SCK = P3^6;
sbit RCK = P3^5;

void matrixled_init()
{
	SCK = 0;
	RCK = 0;
}

void matrixled(unsigned char col, unsigned char Byte)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		SER = Byte & (0x80 >> i);
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
	
	P0 = ~(0x80 >> col);
	Delay1ms(1);
	P0 = 0xFF;
	
}