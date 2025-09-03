#include <REGX52.H>

sbit PWM_LED = P2^1;
sbit PWM_FAN = P1^0;

unsigned char g_pwm_timel = 0;
unsigned char g_pwm_timeh = 0;
unsigned char g_pwm_counter = 0;
unsigned char g_pwm_threshold = 0;

void PWM_Init(unsigned char timel, unsigned char timeh, unsigned char counter, unsigned char threshold)
{
	TMOD &= 0x0F;	
	TMOD |= 0x10;	
	TL1 = timel;
	TH1 = timeh;
	TF1 = 0;	
	TR1 = 1;
	ET1 = 1;
	EA = 1;

//	PT1 = 1;
//	IPH |= 0x80;

	
	g_pwm_timel = timel;
	g_pwm_timeh = timeh;
	g_pwm_counter = counter;
	g_pwm_threshold = threshold;
}

void PWM_Config() interrupt 3
{
	static unsigned char counter = 0;
	TL0 = g_pwm_timel;
	TH0 = g_pwm_timeh;
	
	counter++;
	counter %= g_pwm_counter;
	if(counter <= g_pwm_threshold)
	{
		PWM_LED = 1;
//			PWM_FAN = 1;
	}
	else
	{
		PWM_LED = 0;
//			PWM_FAN = 0;
	}
	
}

void PWM_Set_Threshold(unsigned char thred)
{
	g_pwm_threshold = thred;
}
