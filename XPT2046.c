#include <REGX52.H>
//#include "delay.h"
// #include "XPT2046.h"

// #define XPT2046_XP 		0x94
// #define XPT2046_YP 		0xD4
// #define XPT2046_VBAT	0xA4
// #define XPT2046_AUX		0xE4

sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;

// unsigned int XPT2046_ADC_Value = 0;
// unsigned int XPT2046_target = XPT2046_VBAT;

// void Timer0Init(void)		//10ms@11.0592MHz
// {

// 	TMOD &= 0xF0;		
// 	TMOD |= 0x01;		
// 	TL0 = 0x00;		
// 	TH0 = 0xDC;		
// 	TF0 = 0;	
// 	TR0 = 1;	
// 	ET0 = 1;
// 	EA = 1;
// }


unsigned int xpt2046_readADC(unsigned char cmd)
{
	unsigned char i;
	unsigned int adc = 0;

	XPT2046_DCLK = 0;
	XPT2046_CS = 0;
		
	for(i = 0;i < 8;i++)
	{
		XPT2046_DIN = cmd >> 7;
		cmd <<= 1;
		XPT2046_DCLK = 0;
		XPT2046_DCLK = 1;	 	
	}

	XPT2046_DCLK = 1;
	XPT2046_DCLK = 0;
	
	for(i = 0;i < 12;i++)
	{
		adc <<= 1;
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		adc |= XPT2046_DOUT; 	
	}
	
	XPT2046_CS = 1;
	
	return adc;
}

// void Timer0_Routine() interrupt 1
// {
// 	static unsigned char counts = 0;
// 	TL0 = 0x00;		
// 	TH0 = 0xDC;
// 	counts++;
// 	counts %= 50;
// 	if(0 == counts)
// 	{
// 		XPT2046_ADC_Value = xpt2046_readADC(XPT2046_target);
// 	}
// }

// void xpt2046_set_target(unsigned char target)
// {
// 	XPT2046_target = target;
// }
