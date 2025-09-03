#ifndef __PWM_H__
#define __PWM_H__

void PWM_Init(unsigned char timel, unsigned char timeh, unsigned char counter, unsigned char threshold);
void PWM_Set_Threshold(unsigned char thred);

#endif