#include <REGX52.H>

#define RLEN 8

unsigned char rbytes[RLEN];
bit rflag = 0;

void UartInit(void)		//9600bps@11.0592MHz
{
	PCON |= 0x80;		//波特率倍速
	SCON = 0x50;		//8位数据,可变波特率
//	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
//	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFA;		//设定定时初值
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;	//禁止定时器1中断
	ES = 1;			//使能UART中断
	EA = 1;			//使能全局中断
	TR1 = 1;		//启动定时器1
}

void Uart_SendBytes(unsigned char *dat)
{
	while(*dat)
	{
		SBUF = *dat++;
		while(!TI);
		TI = 0;
	}

}

unsigned char* Uart_ReadBytes()
{
	rflag = 0;
	return rbytes;
}

void Uart_Routine(void) interrupt 4
{
	static unsigned char count = 0;
	if(!rflag)
	{
		if(RI)
		{
			RI = 0;
			rbytes[count] = SBUF;
			if((rbytes[0] == 0x23)&& count < RLEN)
			{
				if(rbytes[count] == 0x24)
				{
					rflag = 1;
					count = 0;
				}
				else
				{
					count++;
				}
			}
			else
			{
				count = 0;
			}		
		}
	}
}
