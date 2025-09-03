#ifndef __UART_H__
#define __UART_H__

extern bit rflag;

void UartInit(void);
void Uart_SendBytes(unsigned char *dat);
unsigned char* Uart_ReadBytes();

#endif

			//´®¿ÚÍ¨ÐÅ
//		if(rflag)
//		{
//			P2 = ~P2;
//			Uart_SendBytes(Uart_ReadBytes());

//		}