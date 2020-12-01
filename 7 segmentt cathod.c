
//anode

#include <lpc214x.h>
void delay();
	unsigned int i,j,k;
unsigned int ar[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
int main()
{
	PINSEL0=0x00000000;
	IODIR0=0x000000ff;
	while(1)
	{
		for(i=0;i<10;i++)
		{
			IOSET0=ar[i];
			delay();
			IOCLR0=ar[i];
		}
	}
	return 0;
}
void delay()
{
	for(j=0;j<1000;j++);
	for(k=0;k<400;k++);
}

		
		
		
		
		
		