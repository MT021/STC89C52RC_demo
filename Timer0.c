#include <REGX52.H>
#include "XPT2046.h"
#include "smg.h"
//#include "IR.h"
#include "matrixled.h"
#include "delay.h"
//#include "nixie.h"
//#include "ds18b20.h"

#define SMG_EN 1  //1: enable smg, 0: disable smg and enable matrixled

//XPT2046_ADC
unsigned char XPT2046_target = XPT2046_VBAT; 
unsigned int XPT2046_ADC_Value = 0;

//smg
unsigned char smg_value_buf[8];
bit smg_enable = 1;	// 1: enable smg, 0: disable smg and enable matrixled

//ds18b20
//int ds18b20_temp = 0;

//IR
//unsigned char ir_temp = 0;


// matrixled --ARE YOU OK !
//unsigned char i, offset = 0;
unsigned char code arr_image_dynamic[] = {
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
											0x00,0x3E,0x48,0x48,0x3E,0x00,0x7E,0x48,
											0x4C,0x32,0x00,0x7E,0x52,0x52,0x52,0x00,
											0x00,0x40,0x20,0x1E,0x20,0x40,0x00,0x3C,
											0x42,0x42,0x3C,0x00,0x7C,0x02,0x02,0x7C,
											0x00,0x00,0x3C,0x42,0x42,0x3C,0x00,0x7E,
											0x18,0x24,0x42,0x00,0x00,0x7A,0x7A,0x00,
											0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
										};

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
	smg_value_buf[7] = 0X76;// Hex "H"
	smg_value_buf[4] = 0x00;// gap between ADC and IR char

	//matrixled
	matrixled_init();
	
//	IR_INT0_Init();
//	singlebus_Init();
	
}

//void Timer0_Routine() interrupt 1
//{
//	static unsigned char counts = 0;
////	static unsigned char i, offset = 0;
////	unsigned char ir_temp = 0;
//	
//	TL0 = 0x00;		
//	TH0 = 0xDC;
//	counts++;	
//	counts %= 100;

//	#if SMG_EN
//			
//			//IR
////			ir_temp = IR_get_ctrl_char();
////			smg_value_buf[5] = get_smg_code(ir_temp / 16);
////			smg_value_buf[6] = get_smg_code(ir_temp % 16);
//			//ds18b20
////			ds18b20_temp  = ds18b20_readtemperature() * 10;
////			if(ds18b20_temp < 0)
//// 			{
////				smg_value_buf[4] = 0x40;
//// 				ds18b20_temp = -ds18b20_temp;
//// 			}
//// 			else
//// 			{
////				smg_value_buf[4] = 0x00;
////			}
////			smg_value_buf[5] = get_smg_code(ds18b20_temp / 100);
////			smg_value_buf[6] = get_smg_code((ds18b20_temp / 10) % 10) | 0x80;
////			smg_value_buf[7] = get_smg_code(ds18b20_temp % 10);

//			//ADC
//			if(0 == counts % 15)
//			{
//				XPT2046_ADC_Value = xpt2046_readADC(XPT2046_target);
//				
//				smg_value_buf[0] = get_smg_code(XPT2046_ADC_Value / 1000);
//				smg_value_buf[1] = get_smg_code(XPT2046_ADC_Value / 100 % 10);
//				smg_value_buf[2] = get_smg_code(XPT2046_ADC_Value / 10 % 10);
//				smg_value_buf[3] = get_smg_code(XPT2046_ADC_Value % 10);
//			}
//			smg_display(smg_value_buf, 1);


//		// show on nixie(matrixled is conflict with smg, use matrixled only when J24 connect to GND)

//	#else
//		//matrixled
//		for(i = 0;i < 8;i++)
//		{
//			matrixled(i, arr_image_dynamic[i + offset]);
//		}
//		if( 0 == counts % 20)
//		{
//			if(++offset > 56)
//			{
//				offset = 0;
//			}			
//		}
//	#endif
//}

void xpt2046_set_target(unsigned char target)
{
	XPT2046_target = target;
}

void smg_set_enable(bit enable)
{
	smg_enable = enable;	// 1: enable smg, 0: disable smg and enable matrixled
}

bit smg_get_enable()
{
	return smg_enable;
}
// unsigned int xpt2046_get_adc_value()
// {
//     return XPT2046_ADC_Value;
// }