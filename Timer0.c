//#include <REGX52.H>
//#include "XPT2046.h"
//#include "smg.h"
//#include "IR.h"
//#include "matrixled.h"
//#include "delay.h"
//#include "nixie.h"
//#include "ds18b20.h"

//#define SMG_EN 1  //1: enable smg, 0: disable smg and enable matrixled

//XPT2046_ADC
//unsigned char XPT2046_target = XPT2046_VBAT; 
//unsigned int XPT2046_ADC_Value = 0;

//smg
//unsigned char smg_value_buf[8];

//unsigned char i = 0;


//void Timer0Init(void)		//10ms@11.0592MHz
//{
//	TMOD &= 0xF0;		
//	TMOD |= 0x01;		
//	TL0 = 0x00;		
//	TH0 = 0xDC;		
//	TF0 = 0;	
//	TR0 = 1;	
//	ET0 = 1;
//	EA = 1;
//}

//void Timer0_Routine() interrupt 1
//{
//	static unsigned char counts = 0;

//	TL0 = 0x00;		
//	TH0 = 0xDC;
//	
//	smg_display(smg_value_buf, 1);	

//}

//void set_smg_value_buf(unsigned char *smg_value_buf_new)
//{
//	for(i = 0;i < 8;i++)
//	{
//		smg_value_buf[i] = smg_value_buf_new[i];	
//	}
//}

