#include <REGX52.H>
// #include "delay.h"
//#include "IR.h"
 #include "smg.h"
#include "XPT2046.h"
//#include "PWM.h"
//#include "Timer0.h"
#include "EKey.h"
#include "matrixkey.h"
#include "SG90.h"
#include "ds18b20.h"
#include "matrixled.h"

void main()
{
	//smg
	unsigned char smg_value_buf[8];
	//adc
	unsigned char XPT2046_target = XPT2046_VBAT; 
	unsigned int XPT2046_ADC_Value = 0;
	//matrixled -- ARE YOU OK !
	unsigned char i, counts = 0, offset = 0;
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
	//ds18b20
	int ds18b20_temp = 0;
//	Timer0Init();
	PWM_Motor_Init();
//	PWM_Init(0xAE, 0xFF, 10, 5);

	while(1)
	{
		//scan ekey to set ADC target
		switch (scan_ekey())
		{
			case K1:
				XPT2046_target = XPT2046_XP;  //AIN0 AD1
				P2_7 = !P2_7;
				break;
			
			case K2:
				XPT2046_target = XPT2046_YP;	//AIN1 NTC1
				P2_7 = !P2_7;
				break;	
			
			case K3:
				XPT2046_target = XPT2046_VBAT;	//AIN2 GR1
				P2_7 = !P2_7;
				break;
			
			case K4:
				XPT2046_target = XPT2046_AUX;	//AIN3 J52
				// smg_set_enable(!smg_get_enable());
				P2_7 = !P2_7;
				break;	

			default:
				break;
		}

		//scan matrix key TO DO
		switch (matrix_key_scan())
		{
			case mKey1:
				PWM_Motor_Set_Threshold(1);
				P2_7 = !P2_7;
				break;
			
			case mKey2:
				PWM_Motor_Set_Threshold(2);
				P2_7 = !P2_7;
				break;

			case mKey3:
				PWM_Motor_Set_Threshold(3);
				P2_7 = !P2_7;
				break;
			
			case mKey4:
				PWM_Motor_Set_Threshold(4);
				P2_7 = !P2_7;
				break;

			case mKey5:
				PWM_Motor_Set_Threshold(5);
				P2_7 = !P2_7;
				break;
			
			case mKey6:
				P2_7 = !P2_7;
				break;

			case mKey7:
				P2_7 = !P2_7;
				break;
			
			case mKey8:
				P2_7 = !P2_7;
				break;

			case mKey9:
				P2_7 = !P2_7;
				break;

			case mKey10:
				P2_7 = !P2_7;
				break;

			case mKey11:
				P2_7 = !P2_7;
				break;

			case mKey12:
				P2_7 = !P2_7;
				break;

			case mKey13:
				P2_7 = !P2_7;
				break;

			case mKey14:
				P2_7 = !P2_7;
				break;

			case mKey15:
				P2_7 = !P2_7;
				break;

			case mKey16:
				P2_7 = !P2_7;
				break;	

			default:
				break;
		}

			//adc
			XPT2046_ADC_Value = xpt2046_readADC(XPT2046_target);		
			smg_value_buf[0] = get_smg_code(XPT2046_ADC_Value / 1000);
			smg_value_buf[1] = get_smg_code(XPT2046_ADC_Value / 100 % 10);
			smg_value_buf[2] = get_smg_code(XPT2046_ADC_Value / 10 % 10);
			smg_value_buf[3] = get_smg_code(XPT2046_ADC_Value % 10);
		
			//ds18b20
			ds18b20_temp  = ds18b20_readtemperature() * 10;
			if(ds18b20_temp < 0)
 			{
				smg_value_buf[4] = 0x40;
 				ds18b20_temp = -ds18b20_temp;
 			}
 			else
 			{
				smg_value_buf[4] = 0x00;
			}
			smg_value_buf[5] = get_smg_code(ds18b20_temp / 100);
			smg_value_buf[6] = get_smg_code((ds18b20_temp / 10) % 10) | 0x80;
			smg_value_buf[7] = get_smg_code(ds18b20_temp % 10);

			smg_display(smg_value_buf, 1);
			
			//matrixled
//			counts++;
//			counts %= 10;
//			for(i = 0;i < 8;i++)
//			{
//				matrixled(i, arr_image_dynamic[i + offset]);
//			}
//			if( 0 == counts)
//			{
//				if(++offset > 56)
//				{
//					offset = 0;
//				}			
//			}
	}
}
