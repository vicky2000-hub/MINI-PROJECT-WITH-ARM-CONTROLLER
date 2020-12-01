#include <LPC214X.H> 
#define LCD_RS  1<<24 //Port1.24 
#define LCD_RW  1<<16 //Port0.16
#define LCD_EN  1<<17 //Port0.17
#define LCD_DATA 0xFF<<16 //Port1.16 to 1.23
#define LCD_STS 1<<23 //Port1.23
#define CLKEN 1
#define CLKSRC 1<<4
int main(void);
void lcdini(void);
void lsts(void);
void lcdctl(unsigned char val1);
void lputc(unsigned char lcr);
void delay (unsigned int k);
void rtc_init(void);
void t_disp(void);
void t_set(unsigned char shrs, unsigned char smin, unsigned char ssec);
int main(void)
{  	
  IODIR0 = LCD_RW | LCD_EN;
  IODIR1 = LCD_RS;
  PINSEL0 = 0;   
  PINSEL1 = 0;
	IOCLR0=LCD_EN; IOCLR1=LCD_RS; IOSET0=LCD_RW; 
  delay(1000); 
   lcdini();   
  rtc_init(); 
       do
  {  
  	 lsts();   
  	 lcdctl(2); 
  	 lsts();   
		  t_disp();
   }while(1);   
}
void lcdini()
{  
  lcdctl(0x38); 	 
  delay(5);   			 
  lcdctl(0x38); 	 
  delay(5);   
  lcdctl(0x38);   
  lsts();      		
  lcdctl(0x38);   
  lsts();      			 
  lcdctl(0x04);   
  lsts();      			
  lcdctl(0x01);   /* Clear Display */
  lsts();      			 /* Wait Till BUSY=0 */
  lcdctl(0x06);   /* Set Entry mode */
  lsts();      			 /* Wait Till BUSY=0 */
 lcdctl(0x0c);   /* Set Display ON */
 }
void lsts()
{
unsigned long int tp1;
  IOCLR1=LCD_RS; IOSET0=LCD_RW;
do{
  IOSET0=LCD_EN;
  tp1 = IOPIN1 & LCD_STS;
  IOCLR0=LCD_EN;
  }while(tp1);
 IOCLR0=LCD_EN;
 IOCLR0=LCD_RW;
}
void lcdctl(unsigned char val1)
{ unsigned long int dat;
  dat = ((unsigned long int)val1) << 16; 
IODIR1 = LCD_RS | LCD_DATA; 
 IOCLR1 = LCD_RS;
 IOCLR0 = LCD_RW;
  IOCLR1 = LCD_DATA;
 IOSET1 = dat;
 IOSET0=LCD_EN;
 IOCLR0=LCD_EN;
 IOSET0=LCD_RW;
 IODIR1 = LCD_RS;
 }
void lputc(unsigned char lcr)
{ unsigned long int dat;
 lsts();
 dat = ((unsigned long int)lcr)<<16;
 IODIR1 = LCD_RS | LCD_DATA; 
 IOSET1=LCD_RS; IOCLR0=LCD_RW;
  IOCLR1 = LCD_DATA;
 IOSET1 = dat;
  IOSET0=LCD_EN;
 IOCLR0=LCD_EN;
  IOSET0=LCD_RW;
 IODIR1 = LCD_RS; 
 }
void delay(unsigned int k)  	
{
	unsigned int i,j;
	for (j=0; j<k; j++)
		for(i = 0; i<=800; i++);
}
void rtc_init()
{
CCR = CLKSRC | CLKEN;
CIIR = 0; 
AMR = 0xff; 
}
void t_disp()
{unsigned char ten, one;
 unsigned char tp1;
tp1 = HOUR & 0x1F;
ten = (tp1/10)+'0';
one = (tp1%10)+'0';
lputc(ten); lputc(one); lputc(':');
tp1 = MIN & 0x3F;
ten = (tp1/10)+'0';
one = (tp1%10)+'0';
lputc(ten); lputc(one); lputc(':');
tp1 = SEC & 0x3F;
ten = (tp1/10)+'0';
one = (tp1%10)+'0';
lputc(ten); lputc(one);
}
void t_set(unsigned char shrs, unsigned char smin, unsigned char ssec)
{
HOUR = shrs & 0x1F;
MIN  = smin & 0x3F;
SEC  = ssec & 0x3F;	
}