#include <lpc214x.h>
#define lcd (0x0f<<16)
#define rs (1<<13)//output
#define rw (1<<14)//output
#define en (1<<15)//output
void delay();
void lcd_display(unsigned char x);
void cmd (unsigned int m);
void lcd_init();
int main()
{
	PINSEL0=0x00000000;
	IODIR0=0xFFFFFFFF;
	lcd_init();
	while(1)
	{
		lcd_init();
		lcd_display(' ');
		lcd_display('v');
		delay();
		lcd_display('i');
		delay();
		lcd_display('c');
		delay();
		lcd_display('k');
		delay();
		lcd_display('y');
		delay();
	}
}
void delay()
{
	unsigned int i;
	for(i=0;i<30000;i++);
}
void lcd_display(unsigned char x)
{
	IOCLR0 =0xFFFFFFFF;
	IOSET0=(x<<16);
	IOSET0 = rs;//rs ==1 data
	IOCLR0 =rw;
	IOSET0 =en;
	delay();
	IOCLR0=en;
}
void cmd (unsigned int m)
{
	IOCLR0 =0xFFFFFFFF;
	IOSET0=(m<<16);
	IOCLR0 = rs; //rs==0 com
	IOCLR0 =rw;
	IOSET0 =en;
	delay();
	IOCLR0=en;
}	
void lcd_init()
{
	cmd(0x38);
	cmd(0x0e);
	cmd(0x06);
	cmd(0x01);
	cmd(0x80);
}