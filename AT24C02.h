#ifndef __AT24C02_H__
#define __AT24C02_H__

void AT24C02_writepage(unsigned char saddr, char *databuf, unsigned char buflen);
unsigned char* AT24C02_readseq(unsigned char saddr, unsigned char rlen);
unsigned char AT24C02_readbyte(unsigned char saddr);

#endif

//		//I2CÍ¨ÐÅ	
//		unsigned char *src, i, temp;

//		unsigned char dat[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
//		
//		LCD_Init();

////		AT24C02_writepage(0, dat, 8);
////		src = AT24C02_readseq(0, 8);
////		
////		temp = AT24C02_readbyte(0);
////		LCD_ShowHexNum(1, 1, src[0], 2);
////		
////		temp = AT24C02_readbyte(1);
////		LCD_ShowHexNum(1, 4, src[1], 2);
////		
////		temp = AT24C02_readbyte(2);
////		LCD_ShowHexNum(1, 7, src[2], 2);
////		
////		temp = AT24C02_readbyte(3);
////		LCD_ShowHexNum(1, 10, src[3], 2);
//		
//		for(i = 0;i < 8;i++)
//		{
//			LCD_ShowHexNum(1 + i/4, 1 + (i%4)*3, AT24C02_readbyte(i), 2);
//		}