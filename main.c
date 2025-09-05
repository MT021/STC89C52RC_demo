#include <REGX52.H>
// #include "delay.h"
#include "IR.h"
// #include "smg.h"
#include "XPT2046.h"
#include "PWM.h"
#include "Timer0.h"
#include "EKey.h"

void main()
{
	IR_INT0_Init();
	Timer0Init();
	PWM_Init(0xAE, 0xFF, 10, 5);

	while(1)
	{
		//scan ekey to set ADC target
		switch (scan_ekey())
		{
			case K1:
				xpt2046_set_target(XPT2046_XP);
				break;
			
			case K2:
				xpt2046_set_target(XPT2046_YP);
				break;	
			
			case K3:
				xpt2046_set_target(XPT2046_VBAT);
				break;
			
			case K4:
				xpt2046_set_target(XPT2046_AUX);
				break;	

			default:
				break;
		}
	}
}
