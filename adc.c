#include <LPC214X.H>
#define LCD_RS 1<<24
#define LCD_RW 1<<16
#define LCD_EN 1<<17
#define LCD_DATA 0xFF<<16
#define LCD_STS 1<<23
#define AD0_1 1<<24
#define CLK_DIV 1<<8
#define PDN 1<<21
#define SOC 1<<24
#define BURST 1<<16
#define DONE 1<<31

int main(void);
int lcdini(void);

void lsts(void);
void lcdct1(unsigned char vall);
void lputc(unsigned char lcr);
void lputval(unsigned int lbuf);

unsigned int adc_read(unsigned char channel);

void adc_init(void);
void delay(unsigned int k);

int main(void)
{
unsigned int tpl;

IODIR0 = LCD_RW|LCD_EN;
IODIR0 = LCD_RS;

PINSEL0=0;
PINSEL0=0|AD0_1;

IOCLR0=LCD_EN;IOCLR1=LCD_RS;IOCLR0=LCD_RW;
delay(1000);

lcdini();
adc_init();

do
{
 tpl =adc_read(1);
lputval( tpl );
delay(500);
lcdct1(0x01);
lsts();
}while(1);
return 0;
}


void lsts()
{
unsigned long int tp1;
IOCLR1=LCD_RS; IOCLR0=LCD_RW;

do{
IOCLR0=LCD_EN;
tp1= IOPIN1&LCD_STS;
IOCLR0=LCD_EN;
}while(tp1);

IOCLR0 = LCD_EN;
IOCLR0 = LCD_RW;
}
int lcdini()
{
lcdct1(0x38);
delay(5);

lcdct1(0x38);
delay(5);

lcdct1(0x38);
lsts();

lcdct1(0x38);
lsts();

lcdct1(0x04);
lsts();

lcdct1(0x01);
lsts();
	
lcdct1(0x06);
lsts();
lcdct1(0x0c);
}
void lcdct1(unsigned char vall)
{
unsigned long int dat;
dat=((unsigned long int) vall)<<16;

IODIR1 = LCD_RS|LCD_DATA;
IOCLR1 = LCD_RS;

IOCLR0 = LCD_RW;
IOCLR1 = LCD_DATA;

IOSET1 = dat;
IOSET0 = LCD_EN;

IOCLR0 = LCD_EN;
IOSET0 = LCD_RW;
IODIR1 = LCD_RS;
}

void lputc(unsigned char lcr)
{
unsigned long int dat;
lsts();
dat = ((unsigned char )lcr)<<16;

IODIR1 = LCD_RS|LCD_DATA;
IOSET1 = LCD_RS; IOCLR0 = LCD_RW;

IOCLR1 = LCD_DATA;
IOSET1 = dat;

IOSET0 = LCD_EN;
IOCLR0 = LCD_EN;

IOSET0 = LCD_RW;
IODIR1 = LCD_RS;
}

void adc_init()
{
unsigned long int ADC_CH;
	ADC_CH = 0|1<<1;
ADC_CH = S0SPCR | CLK_DIV | ADC_CH | BURST;
}

unsigned int adc_read(unsigned char channel)
{
unsigned int aval;
unsigned long int val;


if (channel == 1) val = AD0DR1;
else if (channel == 2) val = AD0DR2;
else if (channel == 3) val = AD0DR3;


val = val>>6;
val = val & 0x3FF;
aval = val;

return(aval);
}

void lputval(unsigned int lbuf)
{
unsigned int val;
unsigned int tpl;

val=lbuf;
tpl = (val/1000) + '0';

lputc(tpl);

val = val %1000;
tpl = (val /100) + '0';

lputc(tpl);

tpl = (val /10) + '0';
lputc(tpl);

tpl = (val %10) + '0';
lputc(tpl);
}

void delay(unsigned int k)
{
unsigned int i,j;

for(j=0; j<k; j++)
{
  for(i=0; i<k;i++)
  {}
}

}