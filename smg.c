//#include "smg.h"
#include <REGX52.H>
#include "delay.h"
#define SMG_A_DP_PORT	P0	//使用宏定义数码管段码口

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//共阴极数码管显示0~F的段码数据
unsigned char gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};


/*******************************************************************************
* 函 数 名       : get_smg_code
* 函数功能		 : get segment code for number 0-F
* 输    入       : num：number 0-15
* 输    出    	 : segment code
*******************************************************************************/
unsigned char get_smg_code(unsigned char num)
{
	if(num < 17)
	{
		return gsmg_code[num];
	}
	else
	{
		return 0x00;
	}
}
/*******************************************************************************
* 函 数 名       : smg_display
* 函数功能		 : 动态数码管显示
* 输    入       : dat：要显示的数据
				   pos：从左开始第几个位置开始显示，范围1-8
* 输    出    	 : 无
*******************************************************************************/
void smg_display(unsigned char dat[],unsigned char pos)
{
	unsigned char i=0;
	unsigned char pos_temp=pos-1;

	for(i=pos_temp;i<8;i++)
	{
	   	switch(i)//位选
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;
		}
		SMG_A_DP_PORT=dat[i-pos_temp];//传送段选数据
		delay_10us(100);//延时一段时间，等待显示稳定
		SMG_A_DP_PORT=0x00;//消音
	}
}
