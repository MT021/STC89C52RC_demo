#include <REGX52.H>
#include "delay.h"
sbit IR_Signal = P3^2;
unsigned char gIR_databuf[4];

void IR_INT0_Init()
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	IR_Signal = 1;
}

void IR_INT0_Routine() interrupt 0
{
	unsigned int timecnt; 
	unsigned char i, j, IR_highcnt = 0;
	if(IR_Signal == 0)
	{
		timecnt = 1000;
		while((IR_Signal == 0) && timecnt)
		{
			delay_10us(1);
			timecnt--;
			if(timecnt == 0) return;
			
		}

		if(IR_Signal)
		{
			timecnt = 550;
			while(IR_Signal && timecnt)
			{
				delay_10us(1);
				timecnt--;
				if(timecnt == 0)	return;		
			}
	
		}
		for(i = 0;i < 4;i++)
		{
			for(j = 0;j < 8;j++)
			{
				gIR_databuf[i] >>= 1;
				
					timecnt = 600;
					while((IR_Signal == 0) && timecnt)
					{
						delay_10us(1);
						timecnt--;
						if(timecnt == 0) return;
					}

					timecnt = 20;
					while(IR_Signal && timecnt)
					{
						delay_10us(10);
//						IR_highcnt++;
						timecnt--;
//						if(IR_highcnt > 20) return;
						if(timecnt == 0) return;
						
					}
						if(timecnt < 12) gIR_databuf[i] |= 0x80;

//					if(IR_highcnt >= 8) gIR_databuf[i] |= 0x80;
//						
//					IR_highcnt = 0;
			}
		}
		if(gIR_databuf[2] != ~gIR_databuf[3])
		{
			for(i = 0;i < 4;i++)
			{
				gIR_databuf[i] = 0;
			}
		}
	}
}
