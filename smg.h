#ifndef _smg_H
#define _smg_H

//#include "public.h"


//#define SMG_A_DP_PORT	P0	//ʹ�ú궨������ܶ����

//���������λѡ�źſ��ƽ�
//sbit LSA=P2^2;
//sbit LSB=P2^3;
//sbit LSC=P2^4;

// extern unsigned char gsmg_code[17];
unsigned char get_smg_code(unsigned char num);

void smg_display(unsigned char dat[],unsigned char pos);

#endif