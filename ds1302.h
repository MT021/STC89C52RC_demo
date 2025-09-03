#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init();
void DS1302_Write_RealTime(unsigned char hours, mins, secs);
unsigned char* DS1302_Read_RealTime();
void DS1302_SET_TimeMod(unsigned char timemod);
void DS1302_WP_Enable(unsigned char enable);

void Timer2Init(void);

#endif