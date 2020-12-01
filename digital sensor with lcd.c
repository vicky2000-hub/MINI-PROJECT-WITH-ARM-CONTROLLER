#include <lpc214x.h>
#define lcd (0xff<<16)
#define rs (1<<13)//output
#define rw (1<<14)//output
#define en (1<<15)//output
void delay();
void lcd_display(unsigned char x);
void lcd_displays(unsigned char *y);
void cmd (unsigned int m);
void lcd_init();
int main()
{
	PINSEL0=0x00000000;
	PINSEL1=0x00000000;
	IODIR0=0xFFFFFFFF;
	IODIR1=0x00000000;
	lcd_init();
	while(1)
	{
		if((IOPIN1 & (1<<16))==0)
		{
			lcd_init();
			lcd_displays("appadiya irru...");
		}
		else
		{ 
		  lcd_init();
			lcd_displays("kaiya edhu da...");
		}
	}}
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
void lcd_displays(unsigned char *y)
{
	while(*y)
	{
		lcd_display(*y++);
	}
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