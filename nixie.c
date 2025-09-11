#include <REGX52.H>
#include "delay.h"

unsigned char numbers[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
														 0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};

void nixie(unsigned char location, unsigned char number, unsigned char addtional_value)
{
	switch(location)
	{
		case 0: P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
		case 1: P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
		case 2: P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
		case 3: P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
		case 4: P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
		case 5: P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
		case 6: P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
		case 7: P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
	}
	P0 = numbers[number] | addtional_value;
//	delay_10us(100);
	Delay1ms(1);
	P0 = 0x00;
}