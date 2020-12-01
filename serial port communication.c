#include <lpc214x.h>
int main(void);
void UART1_Init(void);
void SendString(char *text);
int main(void)
{
	UART1_Init();
	while(1)
	{
		SendString("uart test program");
	}
}
void UART1_Init(void)
{
	PLL0CON=0;
	PLL0FEED=0xAA;
	PLL0FEED=055;
	VPBDIV =1;
	PINSEL0 |= 0x00050000;
	U1FCR =0;
	U1LCR = 0x63;
	U1DLL =0x27;
	U1DLM =0;
	U1LCR =3;
}
void SendString(char *text)
{
	while(*text)
	{
		while(!(U1LSR & 0x20));
		U1THR = *text++;
	}
}
	