#ifndef __DS18B20_H__
#define __DS18B20_H__

float ds18b20_readtemperature();
unsigned char singlebus_Init();

#endif

// #include <REGX52.H>
// #include "ds18b20.h"
// #include "nixie.h"

// void main()
// {
// 	int temp;
// 	unsigned char i = 0;	
	
// 	while(1)
// 	{	

// 		if(++i % 100 == 0)
// 		{
// 			temp = ds18b20_readtemperature() * 10;
// 			if(temp < 0)
// 			{
// 				nixie(3, 10, 0);
// 				temp = -temp;
// 			}
// 			else
// 			{
// 				nixie(3, 12, 0);
// 			}
// 			nixie(4, temp / 1000, 0);
// 			nixie(5, (temp % 1000) /100, 0);
// 			nixie(6, (temp % 100) / 10, 1);
// 			nixie(7, temp % 10, 0);
			
// 		}
		
// 	}
// }