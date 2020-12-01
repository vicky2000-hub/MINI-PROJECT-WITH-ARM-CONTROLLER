#include <lpc214x.h>
#include <math.h>

#define MSEL 4
#define PSEL 1<<5
#define AOUT 1<<19
#define PI2 6.28
#define STEPS 500

void clock(void)
{
	PLL0CFG = PSEL | MSEL;
	
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	PLL0CON = 3;
	
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	VPBDIV =0;
}
int main(void)
{
	unsigned short val,dval;
	float sa;
	clock();
	PINSEL0 =0;
	PINSEL1 =AOUT;
	while(1)
	{
		for(val =0; val <STEPS; val++)
		{
			sa = (val*PI2)/STEPS;
			sa = sin(sa);
			sa = (sa*511.0)+ 511.0;
			dval = sa;
			DACR = dval<<6;
		}
	}
}