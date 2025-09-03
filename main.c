#include <REGX52.H>
#include "delay.h"
#include "IR.h"
#include "smg.h"
#include "XPT2046.h"
#include "PWM.h"

void main()
{
	unsigned char ir_temp, XPT2046_ADC_Value, XPT2046_target;
	unsigned char smg_value_buf[8];
	
	IR_INT0_Init();
	// Timer0Init();
	PWM_Init(0xAE, 0xFF, 10, 5);

	while(1)
	{
/*############################### 扫描独立键盘设置 ADC 命令 ########################*/
		switch (ekey_scan())
		{
			case 0:
				XPT2046_target = XPT2046_XP;
				break;
			
			case 1:
				XPT2046_target = XPT2046_YP;
				break;	
			
			case 2:
				XPT2046_target = XPT2046_VBAT;
				break;
			
			case 3:
				XPT2046_target = XPT2046_AUX;
				break;	

			default:
				break;
		}
/*############################### 红外接收 ########################*/
		ir_temp = IR_get_ctrl_char();

		smg_value_buf[5] = gsmg_code[ir_temp/16];//十位
		smg_value_buf[6] = gsmg_code[ir_temp%16];//个位
		smg_value_buf[7] = 0X76;// 16进制 H

/*############################### ADC #######################*/	
		XPT2046_ADC_Value = xpt2046_readADC(XPT2046_target)
		smg_value_buf[0] = gsmg_code[XPT2046_ADC_Value / 1000];
		smg_value_buf[1] = gsmg_code[XPT2046_ADC_Value / 100 % 10];
		smg_value_buf[2] = gsmg_code[XPT2046_ADC_Value / 10 % 10];
		smg_value_buf[3] = gsmg_code[XPT2046_ADC_Value % 10];
		smg_value_buf[4] = 0x00;
		smg_display(smg_value_buf,1);
	}
}
