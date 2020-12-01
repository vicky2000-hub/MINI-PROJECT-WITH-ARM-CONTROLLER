// port 0 default low
// port 1 default high
#include <lpc214x.h>
void delay();

void main()
{
PINSEL0=0x00000000;// we set 0 to 15 pin as led ouput(gigo)
PINSEL1=0x00000000;// we set 16 to 31 pin as led output(gigo)
IODIR0=0xFFFFFFFF;// we set 0 to 31 pin has output
while(1)
{
IOSET0=0xFFFFFFFF;
delay();
IOCLR0=0xFFFFFFFF;
delay();
}
}
void delay()
{
	unsigned int i;
	for(i=0;i<3000000;i++);
}