#ifndef __XPT2046_H__
#define __XPT2046_H__

extern unsigned int g_ADC_AD1_Value;

void Timer0Init(void);
unsigned int xpt2046_readADC(unsigned char cmd);

#endif

//unsigned int adc_value = 0;
//	LCD_Init();
//	LCD_ShowString(1, 1, "AD1   NTC1   GR1");	
//	P2_0 = 0;
//	while(1)
//	{	
//		adc_value = xpt2046_readADC(XPT2046_XP);
//		LCD_ShowNum(2, 1, adc_value, 4);
//		Delay1ms(100);
//		adc_value = xpt2046_readADC(XPT2046_YP);
//		LCD_ShowNum(2, 7, adc_value, 4);
//		Delay1ms(100);
//		adc_value = xpt2046_readADC(XPT2046_VBAT);
//		LCD_ShowNum(2, 13, adc_value, 4);
//		Delay1ms(100);
//		P2_0 = ~P2_0;
//	}