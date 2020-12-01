
// port 0 default low
// port 1 default high
#include <lpc214x.h>
void delay();

void main()
{
IOSET0=0x00000000;
IODIR1=0xFFFFFFFF;
IOSET1=0x00000000;	
PINSEL0=0x00000000;// we set 0 to 15 pin as led ouput(gigo)
PINSEL1=0x00000000;// we set 16 to 31 pin as led output(gigo)
IODIR0=0x24208408;// we set 0 to 31 pin has output
while(1)
{
	
IOSET0=0x242F84F8;
delay();
IOCLR0=0x242F84F8;
delay();
}
}
void delay()
{
	unsigned int i;
	for(i=0;i<30000;i++);
}