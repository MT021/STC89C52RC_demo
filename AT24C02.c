#include "I2C.h"
#include "delay.h"
#include "intrins.h"

#define AT24C02_ADDR 0xA0
#define AT24C02_RXBUF_MAX 8

void AT24C02_writepage(unsigned char saddr, char *databuf, unsigned char buflen)
{
	unsigned char i;
	I2C_start();
	I2C_writebyte(AT24C02_ADDR);
	I2C_waitack();
	I2C_writebyte(saddr);
	I2C_waitack();
	for(i = 0;i < buflen;i++)
	{
		I2C_writebyte(databuf[i]);
		I2C_waitack();	

	}
	I2C_stop();	
	Delay1ms(5);
}

unsigned char* AT24C02_readseq(unsigned char saddr, unsigned char rlen)
{
	unsigned char i;
	unsigned char dat[AT24C02_RXBUF_MAX];
	I2C_start();
	I2C_writebyte(AT24C02_ADDR);
	I2C_waitack();
	I2C_writebyte(saddr);
	I2C_waitack();
	I2C_start();
	I2C_writebyte(AT24C02_ADDR | 0x01);
	I2C_waitack();
	
	for(i = 0;i < rlen;i++)
	{
		dat[i] = I2C_readbyte();
		_nop_();_nop_();
		if(i != rlen - 1)
		{
			I2C_ACK();
			_nop_();_nop_();
		}
		
	}
	I2C_NACK();
	I2C_stop();	
		
	return dat;
}

unsigned char AT24C02_readbyte(unsigned char saddr)
{
	unsigned char dat;
	I2C_start();
	I2C_writebyte(AT24C02_ADDR);
	I2C_waitack();
	I2C_writebyte(saddr);
	I2C_waitack();
	I2C_start();
	I2C_writebyte(AT24C02_ADDR | 0x01);
	I2C_waitack();

	dat = I2C_readbyte();

	I2C_NACK();
	I2C_stop();	
		
	return dat;
}