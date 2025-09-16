#include <REGX52.H>
#include "delay.h"
#include "matrixkey.h"

mkey matrix_key_scan()
{
	static mkey keymap[4][4] = {
								{mKey1, mKey2, mKey3, mKey4},
								{mKey5, mKey6, mKey7, mKey8},
								{mKey9, mKey10, mKey11, mKey12},
								{mKey13, mKey14, mKey15, mKey16}
										};
	static unsigned char row, col;
	P1 = 0x0F;
	if(P1 != 0x0F)
		{
			Delay1ms(10);
			switch(P1)
				{
				case 0x07: col = 0; break;
				case 0x0B: col = 1; break;
				case 0x0D: col = 2; break;
				case 0x0E: col = 3; break;
				}
			P1 = 0xF0;
			switch(P1)
				{
				case 0x70: row = 0; break;
				case 0xB0: row = 1; break;
				case 0xD0: row = 2; break;
				case 0xE0: row = 3; break;
				}
			while(P1 != 0xF0);
			Delay1ms(10);
			return keymap[row][col];
		}
	return mKey_None;

}
