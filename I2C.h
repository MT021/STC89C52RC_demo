#ifndef __I2C_H__
#define __I2C_H__

void I2C_start(void);
void I2C_stop(void);
void I2C_writebyte(unsigned char dat);
unsigned char I2C_readbyte(void);
void I2C_ACK(void);
void I2C_NACK(void);
unsigned char I2C_waitack();

#endif