#include <REGX52.H>
#include "delay.h"

sbit SCL = P2^1;
sbit SDA = P2^0;

void I2C_start(void)
{
	SDA = 1;
	delay_10us(1);
	SCL = 1;
	delay_10us(1);
	SDA = 0;
	delay_10us(1);
	SCL = 0;
	delay_10us(1);
}

void I2C_stop(void)
{
	SDA = 0;
	delay_10us(1);
	SCL = 1;
	delay_10us(1);
	SDA = 1;
	delay_10us(1);
}

void I2C_writebyte(unsigned char dat)
{
	unsigned char i;
	SCL = 0;
	for(i = 0;i < 8;i++)
	{
		SDA = dat >> 7;
		dat <<= 1;
		delay_10us(1);
		SCL = 1;
		delay_10us(1);
		SCL = 0;
		delay_10us(1);

	}
}

unsigned char I2C_readbyte(void)
{
	unsigned char i,dat;
	SDA = 1;
	for(i = 0;i < 8;i++)
	{
		SCL = 1;
		delay_10us(1);
		dat <<= 1;
		dat |= SDA;
		SCL = 0;
	}
	return dat;
}

void I2C_ACK(void)
{
	SCL = 0;
	SDA = 0;
	delay_10us(1);
	SCL = 1;
	delay_10us(1);
	SCL = 0;
}

void I2C_NACK(void)
{
	SCL = 0;
	SDA = 1;
	delay_10us(1);
	SCL = 1;
	delay_10us(1);	
	SCL = 0;
}

unsigned char I2C_waitack()
{
	unsigned char ack;
	SDA = 1;
	SCL = 1;
	delay_10us(1);
	ack = SDA;
	SCL = 0;
	return ack;
}