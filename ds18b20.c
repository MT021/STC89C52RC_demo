#include <REGX52.H>
#include "intrins.h"
#include "delay.h"

sbit singlebus = P3^7;

void singlebus_reset()
{
	singlebus = 0;
	delay_10us(75);
	singlebus = 1;
	delay_10us(2);
}

unsigned char check_edge()
{
	unsigned char timeout = 0;
	while(singlebus && timeout < 20)
	{
		timeout++;
		delay_10us(1);
	}
	if(timeout >= 20)
	{
		return 1;
	}
	timeout = 0;
	while((!singlebus) && timeout < 20)
	{
		timeout++;
		delay_10us(1);
	}
	if(timeout >= 20)
	{
		return 1;
	}
	return 0;
}

unsigned char singlebus_Init()
{
	singlebus_reset();
	return check_edge();
}

void singlebus_writebyte(unsigned char dat)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		if(dat&(0x01 << i))
		{
			singlebus = 0;
			_nop_();
			_nop_();
//			_nop_();
			singlebus = 1;
			delay_10us(6);
		}
		else
		{
			singlebus = 0;
			delay_10us(6);
			singlebus = 1;
			_nop_();
			_nop_();
//			_nop_();
		}
	}
}

unsigned char singlebus_read_bit(void)
{
	unsigned char dat=0;
	
	singlebus=0;
	_nop_();_nop_();
	singlebus=1;	
	_nop_();_nop_(); //该段时间不能过长，必须在15us内读取数据
	if(singlebus)dat=1;	//如果总线上为1则数据dat为1，否则为0
	else dat=0;
	delay_10us(5);
	return dat;
} 

unsigned char singlebus_readbyte()
{
	unsigned char i, temp = 0, dat = 0;
	for(i = 0;i < 8;i++)
	{
		dat >>= 1;
		singlebus = 0;
		_nop_();
		_nop_();
		singlebus = 1;
		_nop_();
		_nop_();
		if(singlebus)
		{
			dat |= 0x80;		
		}
		delay_10us(5);
	}
	return dat;
}

float ds18b20_readtemperature()
{
	unsigned char dat_l, dat_h;
	unsigned int dat;
	float temp;
	
	singlebus_Init();
	singlebus_writebyte(0xcc);
	singlebus_writebyte(0x44);
	singlebus_Init();
	singlebus_writebyte(0xcc);	
	singlebus_writebyte(0xbe);
	
	dat_l = singlebus_readbyte();
	dat_h = singlebus_readbyte();

	dat = (dat_h << 8) | dat_l;
	
	if((dat_h & 0xf8) == 0xf8)
	{
		temp = (~dat + 1) * (-0.0625);
	}
	else
	{
		temp = dat * 0.0625;
	}

	
	return temp;
}
