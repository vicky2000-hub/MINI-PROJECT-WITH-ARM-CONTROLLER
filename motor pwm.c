#include "lpc214x.h"
#define TON 100
#define PWM5 1<<17
#define PWMMROR 1<<1
#define PWMENA5 1<<13
#define EPWMMOL 1<<0
#define EPWMM5L 1<<5
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
	PINSEL0 = PWM5;
	clock();
	PWMMCR = PWMMROR;
	PWMPCR = 0 | PWMENA5;
	PWMPR = 2;
	PWMMR0 = 100;
	PWMMR5 = TON;
	PWMLER = EPWMMOL | EPWMM5L;
	PWMTCR =9;
	while(1);
}