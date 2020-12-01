#include "lpc214x.h"
#define MSE 4
#define PSET 1<<5
#define AOUT 1<<19

void delay (int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<5;j++)
		{;}
		}
	}
void clock(void)
{
  PLL0CFG = PSET| MSE;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	
	PLL0CON = 3;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	VPBDIV =0;
}
int main(void)
{
	//unsigned short val;
	clock();
	PINSEL0= 0;
	PINSEL1= AOUT;
	while(1)
	{
		DACR = 0;
		delay(1);
		DACR=0x3FF <<6;
		delay(1);
	}
}