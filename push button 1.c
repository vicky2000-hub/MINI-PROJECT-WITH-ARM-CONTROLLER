#include <lpc214x.h>
int main()
{
IODIR0=0xFFF7FFFF;
IODIR1=0x00000000;
	while(1)
	{
		if((IOPIN0 | (1<<19))==0)
		{
			IOSET0=0xFFF7FFFF;
		}
		else
		{ 
			IOCLR0=0xFFF7FFFF;
		}
	}
}