#include <lpc214x.h>
#define lcd (0xFF<<8)
#define rs (1<<16)
#define rw (1<<17)
#define en (1<<18)
#define r1 (1<<16)
#define r2 (1<<17)
#define r3 (1<<18)
#define r4 (1<<19)
#define c1 (1<<20)
#define c2 (1<<21)
#define c3 (1<<22)
#define c4 (1<<23)
void delay (unsigned int time);
void lcd_int(void);
void lcd_print(char *str);
void lcd_cmd(unsigned int command);
void lcd_dat(unsigned char data);
unsigned char keypad(void);
void keypad_delay(void);
int main(void)
{
	PINSEL0=0x00000000;
	IODIR0=0xFFFFFFFF;
	PINSEL1=0x00000000;
	IODIR1=0x00F00000;
	lcd_int();
	lcd_print("press any key");
	lcd_cmd(0xc0);
	while(1)
	{
		lcd_dat(keypad());
	}
	return 0;
}
void keypad_delay(void)
{
	unsigned int t1,t2;
	for(t1=0;t1<300;t1++)
	{for(t2=0;t2<1275;t2++){}}
}
unsigned char keypad(void)
{
	unsigned char key;
	IOCLR1=0x00FF0000;
	while(1)
	{
		IOCLR1=0x00100000;
		IOSET1=0x00E00000;//first collumn
		if((IOPIN1&r1)==0)
		{
			key ='7';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&r2)==0)
		{
			key ='8';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&r3)==0)
		{
			key='9';
			keypad_delay();
			return key;
		}
		else if((IOPIN1&r4)==0)
		{
			key='/';
			keypad_delay();
			return key;
		}
		IOCLR1=0x00200000;
		IOSET1=0x00D00000;//secound collumn
		if((IOPIN1 & r1 )==0)
		{key ='4';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 &r2)==0)
		{
			key ='3';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 &r3)==0)
		{
			key='6';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 & r4)==0)
		{
			key='*';
			keypad_delay();
			return key;
		}	
		IOCLR1=0x00400000;
		IOSET1=0x00B00000;//THIRE collumn
		if((IOPIN1 & r1 )==0)
		{key ='1';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 &r2)==0)
		{
			key ='2';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 &r3)==0)
		{
			key='3';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 & r4)==0)
		{
			key='_';
			keypad_delay();
			return key;
		}
		IOCLR1=0x00800000;
		IOSET1=0x00700000;//four collumn
		if((IOPIN1 & r1)==0)
		{
			lcd_cmd(0x01);
			return key;
		}
		else if((IOPIN1 &r2)==0)
		{
			key ='0';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 &r3)==0)
		{
			key='=';
			keypad_delay();
			return key;
		}
		else if((IOPIN1 & r4)==0)
		{
			key='+';
			keypad_delay();
			return key;
		}
	}
}
		void lcd_cmd(unsigned int command)
		{
			IOCLR0=0xFFFFFFFF;
			IOSET0=(command <<8);
			IOCLR0=rs;
			IOCLR0=rw;
			IOSET0=en;
			delay(2);
			IOCLR0=en;
			delay(3);
		}
		void lcd_dat(unsigned char data)
		{
      IOCLR0=0xFFFFFFFF;
			IOSET0=(data <<8);
			IOSET0=rs;
			IOCLR0=rw;
			IOSET0=en;
			delay(2);
			IOCLR0=en;
			delay(3);
		}
		void lcd_print(char*str)
			{
			while(*str!='\0'){
				lcd_dat(*str);
				str++;
			}
		}
		void lcd_int(void)
		{
			delay(5);
			lcd_cmd(0x38);
			lcd_cmd(0x01);
		//	lcd_cmd(0x06);
			//lcd_cmd(0x01);
			delay(5);
			lcd_cmd(0x80);
		}
		void delay(unsigned int time)
		{
			unsigned int t1,t2;
	for(t1=0;t1<time;t1++)
	{for(t2=0;t2<1275;t2++){}}
	}
