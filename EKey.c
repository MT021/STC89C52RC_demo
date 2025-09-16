#include <REGX52.H>
#include "delay.h"
#include "EKey.h"

ekey scan_ekey()
{
		if(P3_1 == 0)
		{
			Delay1ms(10);
			while(P3_1 == 0);
			Delay1ms(10);

			return K1;	
	
		}

		if(P3_0 == 0)
		{
			Delay1ms(10);
			while(P3_0 == 0);
			Delay1ms(10);

			return K2;	
			
		}

		if(P3_2 == 0)
		{
			Delay1ms(10);
			while(P3_2 == 0);
			Delay1ms(10);

			return K3;	
	
		}

		if(P3_3 == 0)
		{
			Delay1ms(10);
			while(P3_3 == 0);
			Delay1ms(10);

			return K4;	
	
		}
		return eKey_None;
}
