#ifndef __TIMER0_H__
#define __TIMER0_H__

void Timer0Init(void);
void xpt2046_set_target(unsigned char target);
unsigned int xpt2046_get_adc_value();

#endif