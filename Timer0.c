#include <REGX52.H>
#include "XPT2046.h"
#include "smg.h"
#include "IR.h"

//XPT2046_ADC
unsigned char XPT2046_target = XPT2046_VBAT; 
unsigned int XPT2046_ADC_Value = 0;

//smg
unsigned char smg_value_buf[8];

//IR
unsigned char ir_temp = 0;


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

	//smg
	smg_value_buf[7] = 0X76;// Hex H
	smg_value_buf[4] = 0x00;// gap
}

void Timer0_Routine() interrupt 1
{
	static unsigned char counts = 0;

	TL0 = 0x00;		
	TH0 = 0xDC;
	counts++;
	counts %= 50;
	if(0 == counts)
	{
		
		/*############################### IR ########################*/
		ir_temp = IR_get_ctrl_char();

		smg_value_buf[5] = gsmg_code[ir_temp/16];//十位 hex
		smg_value_buf[6] = gsmg_code[ir_temp%16];//个位 hex
		

		/*############################### show ADC on nixie #######################*/	
		XPT2046_ADC_Value = xpt2046_readADC(XPT2046_target);
		smg_value_buf[0] = gsmg_code[XPT2046_ADC_Value / 1000];
		smg_value_buf[1] = gsmg_code[XPT2046_ADC_Value / 100 % 10];
		smg_value_buf[2] = gsmg_code[XPT2046_ADC_Value / 10 % 10];
		smg_value_buf[3] = gsmg_code[XPT2046_ADC_Value % 10];
		
		
	}
	smg_display(smg_value_buf,1);
}

void xpt2046_set_target(unsigned char target)
{
	XPT2046_target = target;
}

// unsigned int xpt2046_get_adc_value()
// {
//     return XPT2046_ADC_Value;
// }