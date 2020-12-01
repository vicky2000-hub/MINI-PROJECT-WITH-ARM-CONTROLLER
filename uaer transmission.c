#include<lpc214x.h>
void sercon();
int main()
{
	sercon();
	while(1)
	{
		U0THR= 'A';
		while(!(U0LSR & 0X40))
		{}}
		}
	void sercon()
			{
				PINSEL0=0x00000005;
				U0LCR=0x85;
				U0DLL=0x061;
				U0LCR=0x03;
			}