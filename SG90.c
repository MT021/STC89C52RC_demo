#include <REGX52.H>

/*	
		0.5ms 	  0  degree
		1ms			 45  degree
		1.5ms		 90  degree
		2ms			135  degree
		2.5ms		180  degree
*/
		
		
sbit PWM_Motor = P2^1;
//sbit PWM_FAN = P1^0;

unsigned char g_pwm_motor_threshold = 1;

void PWM_Motor_Init()
{
	TMOD &= 0x0F;	
	TMOD |= 0x10;	
//	TL1 = 0x33;			//500us
//	TH1 = 0xFE;
	TL1 = 0xA4;		//100us
	TH1 = 0xFF;
	TF1 = 0;	
	TR1 = 1;
	ET1 = 1;
	EA = 1;
	
	PWM_Motor = 1;

}

void PWM_Motor_Timer1Routine() interrupt 3
{
	static unsigned char counter = 0;
//	static unsigned int looptime = 0;
//	static char dirt = 1;
	
//	TL1 = 0x33; //500us
//	TH1 = 0xFE;
	TL1 = 0xA4;		//100us
	TH1 = 0xFF;
	counter++;
//	counter %= 40;//500us * 40 = 20ms
	counter %= 200;//100us * 200 = 20ms
	
	if(counter < g_pwm_motor_threshold)
	{
		PWM_Motor = 1;
	}
	else
	{
		PWM_Motor = 0;
	}
	
}

void PWM_Motor_Set_Threshold(unsigned char thred)
{
	g_pwm_motor_threshold = thred;
}
