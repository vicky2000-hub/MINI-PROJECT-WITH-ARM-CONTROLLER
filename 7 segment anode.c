#include <lpc214x.h>
void delay();
void main()
{
	PINSEL0=0x00000000;
	IODIR0=0x0000007F;
	while(1)
	{
		IOSET0=0x00000080;
		delay();//0
		IOCLR0=0x00000080;
		IOSET0=0x00000079;
		delay();//1
		IOCLR0=0x00000079;
		IOSET0=0x00000034;
		delay();//2
		IOCLR0=0x00000034;
		IOSET0=0x00000030;
		delay();//3
		IOCLR0=0x00000030;
		IOSET0=0x00000019;
		delay();//4
		IOCLR0=0x00000019;
		IOSET0=0x00000012;
		delay();//5
		IOCLR0=0x00000012;
		IOSET0=0x00000002;
		delay();//6
		IOCLR0=0x00000002;
		IOSET0=0x00000038;
		delay();//7
		IOCLR0=0x00000038;
		IOSET0=0x00000000;
		delay();//8
		IOCLR0=0x00000000;
		IOSET0=0x00000010;
		delay();//9
		IOCLR0=0x00000010;
	}
}
void delay()
{
	unsigned int i;
	for(i=0;i<30000;i++);
}


		
		
		
		
		
		