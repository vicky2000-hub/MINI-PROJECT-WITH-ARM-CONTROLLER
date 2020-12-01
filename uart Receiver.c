#include<lpc214x.h>
void sercon();
int main()
{
	unsigned char x;
	sercon();
	while(1){
	while(!(U0LSR & 0x01));
	x=U0RBR;
	U0THR=x;
	while(!(U0LSR & 0x40));
	
}}
void sercon()
			{
				PINSEL0=0x00000005;
				U0LCR=0x85;
				U0DLL=0x061;
				U0LCR=0x03;
			}