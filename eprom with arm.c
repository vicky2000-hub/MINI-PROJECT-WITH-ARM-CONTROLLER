#include <LPC214X.H>
#define SDA0 1<<6
#define SCL0 1<<4
#define I2EN 1<<6
#define STA  1<<5
#define STO  1<<4
#define SI   1<<3
#define AA   1<<2
int main(void);
void i2c_init();
void i2c_word_write( unsigned char slave_addr, unsigned char word_addr,unsigned char data );
unsigned char i2c_word_read( unsigned char slave_addr, unsigned char word_addr );                           
void i2c_write(unsigned char addr, unsigned char dat);
void disp_value(unsigned char value);
void delay(unsigned int k);
unsigned char seg_dat[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x98};
int main()
{
unsigned char count;
i2c_init();
count = i2c_word_read(0xA0, 0);
if(count>9) count=0;
while(1)
{ disp_value(count); 
   i2c_word_write(0xA0, 0 , count); 
delay(2000);       
count++;           
if(count>9) count=0;
  }
return(0);
}
void i2c_init()
{
PINSEL0 = 0 | SDA0 | SCL0; 
I2C0SCLH = 200; I2C0SCLL = 200; 
I2C0CONSET = I2EN;
}
void i2c_word_write( unsigned char slave_addr,
unsigned char word_addr,
unsigned char data )
{
unsigned char sts; 
 I2C0CONSET = STA;
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0CONCLR = STA; 
 I2C0DAT = slave_addr; 
 I2C0CONSET = AA; 
 I2C0CONCLR = SI; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0DAT = word_addr; 
 I2C0CONSET = AA; 
 I2C0CONCLR = SI; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0DAT = data;  
 I2C0CONSET = AA; 
 I2C0CONCLR = SI; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0CONSET = STO | AA; 
 I2C0CONCLR = SI; 
delay(15);
 I2C0CONCLR = SI;
}
unsigned char i2c_word_read( unsigned char slave_addr, unsigned char word_addr )                       
{
unsigned char sts;
unsigned char data;
 I2C0CONSET = STA;
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0CONCLR = STA; 

 I2C0DAT = slave_addr; 
 I2C0CONSET = AA; 
 I2C0CONCLR = SI; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0DAT =word_addr; 
 I2C0CONSET = AA; 
 I2C0CONCLR = SI; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
I2C0CONSET = STO | AA; 
 I2C0CONCLR = SI; 
delay(2);
 I2C0CONCLR = SI; 
I2C0CONSET = STA;
do{
sts = I2C0CONSET & SI;
   }
while(sts!=SI);
 I2C0CONCLR = STA; 

I2C0DAT = slave_addr | 1; 
I2C0CONSET = AA; 
I2C0CONCLR = SI; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
I2C0CONSET = AA; 
  I2C0CONCLR = SI; 

do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
data = I2C0DAT; 
  I2C0CONCLR = SI | AA; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI); 
 I2C0CONSET = STO | AA; 
 I2C0CONCLR = SI; 
delay(2);
 I2C0CONCLR = SI; 
return(data); 
}
void i2c_write(unsigned char addr, unsigned char dat)
{
unsigned char sts;
 I2C0CONSET = STA;
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0CONCLR = STA; 
I2C0DAT = addr; 
 I2C0CONSET = AA; 
 I2C0CONCLR = SI; 
do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0DAT = dat; 
 I2C0CONSET = AA; 
 I2C0CONCLR = SI; 

do{
sts = I2C0CONSET & SI;
}while(sts!=SI);
 I2C0CONSET = STO | AA; 
 I2C0CONCLR = SI; 
 I2C0CONCLR = SI; 
}
void disp_value(unsigned char value)
{ 

i2c_write(0x70, seg_dat[value]);
}	
void delay(unsigned int k)
{
	unsigned int i,j;
	for (j=0; j< k; j++){
		for(i = 0; i<=5035; i++){}}
}
