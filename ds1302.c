#include <REGX52.H>
#include "smg.h"

#define DS1302_WP_WADDR 		0x8E
#define DS1302_SEC_RADDR 		0x81
#define DS1302_SEC_WADDR 		0x80
#define DS1302_MIN_RADDR 		0x83
#define DS1302_MIN_WADDR 		0x82
#define DS1302_HOUR_RADDR 	0x85
#define DS1302_HOUR_WADDR 	0x84

sbit DS1302_CE = P3^5;
sbit DS1302_IO = P3^4;
sbit DS1302_SCLK = P3^6;


void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

void DS1302_writebyte(unsigned char addr, dat)
{
	unsigned char i;
	DS1302_CE = 1;
	//write addr
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = addr & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	//write data
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = dat & (0x01 << i);
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
	 
}

unsigned char DS1302_readbyte(unsigned char addr)
{
	unsigned char i, dat = 0;
	DS1302_CE = 1;
	//write addr
	for(i = 0;i < 8;i++)
	{
		DS1302_IO = addr & (0x01 << i);
//		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
		if(7 != i)
		{
			DS1302_SCLK = 0;
		}
	}
	//read data
	for(i = 0;i < 8;i++)
	{
		dat >>= 1;
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if(DS1302_IO)
		{
			dat |= 0x80;
		}
		if(7 != i)
		{
			DS1302_SCLK = 1;
		}	
	}
	DS1302_CE = 0;
	DS1302_IO = 0; //write 0 or read data error!!!
	return dat;
}

// 0 enable write; 1 disable write
void DS1302_WP_Enable(unsigned char enable)
{
	DS1302_writebyte(DS1302_WP_WADDR, (enable << 7)& 0x80);
}

//0 24mod;1 12mod
void DS1302_SET_TimeMod(unsigned char timemod)
{
	DS1302_writebyte(DS1302_HOUR_WADDR, (timemod << 7)& 0x80);
}

//read realtime
unsigned char* DS1302_Read_RealTime()
{
	unsigned char RTime[8];
	unsigned char temp = 0;
	temp = DS1302_readbyte(DS1302_HOUR_RADDR);
	RTime[0] = temp / 16 ;
	RTime[1] = temp % 16;
	temp = DS1302_readbyte(DS1302_MIN_RADDR);
	RTime[3] = temp / 16 ;
	RTime[4] = temp % 16;
	temp = DS1302_readbyte(DS1302_SEC_RADDR);
	RTime[6] = temp / 16 ;
	RTime[7] = temp % 16;
	return RTime;
}
//set realtime
void DS1302_Write_RealTime(unsigned char hours, mins, secs)
{
	unsigned char temp;
	temp = hours /10 *16 + hours % 10;
	DS1302_writebyte(DS1302_HOUR_WADDR, temp);
	temp = mins /10 *16 + mins % 10;
	DS1302_writebyte(DS1302_MIN_WADDR, temp);
	temp = secs /10 *16 + secs % 10;
	DS1302_writebyte(DS1302_SEC_WADDR, temp);
}


void Timer2Init(void)		//10ms@11.0592MHz
{
	T2MOD = 0;		
	T2CON = 0;		
	TL2 = 0x00;		
	TH2 = 0xDC;		
	RCAP2L = 0x00;		
	RCAP2H = 0xDC;	
	TR2 = 1;
	ET2 = 1;
	EA = 1;
}

void Timer2_Routine() interrupt 5
{
	unsigned char i;
	unsigned char *RTBuffer, smgbuffer[8];

		RTBuffer = DS1302_Read_RealTime();
		for(i = 0;i < 8;i++)
			{
				if(2 == i || 5 == i)
				{
					smgbuffer[i] = 0x40;
				}
				else
				{
					smgbuffer[i] = get_smg_code(RTBuffer[i]);
				}
			}
		smg_display(smgbuffer, 1);

	TF2 = 0;
}