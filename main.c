#include <REGX52.H>
// #include "delay.h"
//#include "IR.h"
// #include "smg.h"
#include "XPT2046.h"
//#include "PWM.h"
#include "Timer0.h"
#include "EKey.h"
#include "matrixkey.h"
#include "SG90.h"

void main()
{


	Timer0Init();
	PWM_Motor_Init();
//	PWM_Init(0xAE, 0xFF, 10, 5);

	while(1)
	{
		//scan ekey to set ADC target
		switch (scan_ekey())
		{
			case K1:
				xpt2046_set_target(XPT2046_XP);  //AIN0 AD1
				P2_7 = !P2_7;
				break;
			
			case K2:
				xpt2046_set_target(XPT2046_YP);	//AIN1 NTC1
				P2_7 = !P2_7;
				break;	
			
			case K3:
				xpt2046_set_target(XPT2046_VBAT);	//AIN2 GR1
				P2_7 = !P2_7;
				break;
			
			case K4:
				xpt2046_set_target(XPT2046_AUX);	//AIN3 J52
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
	}
}
