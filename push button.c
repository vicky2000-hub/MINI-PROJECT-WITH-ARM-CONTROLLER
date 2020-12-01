#include <lpc214x.h>
int main()
{
IODIR0=0xFFFFFFFF;
IODIR1=0x00000000;
	while(1)
	{
		if((IOPIN1 & (1<<16))==0)
		{
			IOSET0=0xFFFFFFFF;
		}
		else
		{ 
			IOCLR0=0xFFFFFFFF;
		}
	}
}