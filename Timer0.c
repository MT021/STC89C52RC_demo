#include <REGX52.H>
#include "XPT2046.h"

//XPT2046_ADC
unsigned char XPT2046_target = XPT2046_VBAT; 
unsigned int XPT2046_ADC_Value = 0;

void Timer0Init(void)		//10ms@11.0592MHz
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0x00;		
	TH0 = 0xDC;		
	TF0 = 0;	
	TR0 = 1;	
	ET0 = 1;
	EA = 1;
}

void Timer0_Routine() interrupt 1
{
	static unsigned char counts = 0;
    //XPT2046_ADC
	TL0 = 0x00;		
	TH0 = 0xDC;
	counts++;
	counts %= 50;
	if(0 == counts)
	{
		XPT2046_ADC_Value = xpt2046_readADC(XPT2046_target);
	}
}

void xpt2046_set_target(unsigned char target)
{
	XPT2046_target = target;
}

unsigned int xpt2046_get_adc_value()
{
    return XPT2046_ADC_Value;
}