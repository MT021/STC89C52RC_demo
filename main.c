#include <REGX52.H>
#include "delay.h"
#include "IR.h"
#include "smg.h"
#include "XPT2046.h"
#include "PWM.h"

void main()
{

	unsigned char ir_temp;
	unsigned char smg_value_buf[8];
	
	IR_INT0_Init();
	Timer0Init();
	PWM_Init(0xAE, 0xFF, 10, 5);

	
	while(1)
	{
/*############################### 红外接收 #######################*/
		ir_temp = gIR_databuf[2];

		smg_value_buf[5] = gsmg_code[ir_temp/16];//将控制码高4位转换为数码管段码
		smg_value_buf[6] = gsmg_code[ir_temp%16];//将控制码低4位转换为数码管段码
		smg_value_buf[7] = 0X76;//显示H的段码

//		smg_display(ired_buf,6);
		
/*############################### ADC #######################*/	
		smg_value_buf[0] = gsmg_code[g_ADC_AD1_Value / 1000];
		smg_value_buf[1] = gsmg_code[g_ADC_AD1_Value / 100 % 10];
		smg_value_buf[2] = gsmg_code[g_ADC_AD1_Value / 10 % 10];
		smg_value_buf[3] = gsmg_code[g_ADC_AD1_Value % 10];
		smg_value_buf[4] = 0x00;
		smg_display(smg_value_buf,1);
	}
}
