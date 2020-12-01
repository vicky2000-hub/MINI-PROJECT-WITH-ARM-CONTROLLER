#include "lpc214x.h"
#define TON 100
#define PWM4 1<<17
#define PWMMROR 1<<1
#define PWMENA4 1<<12
#define EPWMMOL 1<<0
#define EPWMM4L 1<<4
void clock(void)
{
	PLL0CON = 0;
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	VPBDIV = 0;
}
int main(void)
{
	IODIR0 = 0xFFFFFFFF;
	PINSEL0 = PWM4;
	clock();
	PWMMCR = PWMMROR;
	PWMPCR = 0 | PWMENA4;
	PWMPR = 2;
	PWMMR0 = 1000;
	PWMMR4 = TON;
	PWMLER = EPWMMOL | EPWMM4L;
	while(1);
}