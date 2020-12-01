#include "lpc214x.h"
#define SC0 1<< 12
#define SC1 1<< 13
#define SC2 1<< 14
#define SC3 1<< 15
#define RTN 0x0F << 8
#define SDA0 1<< 6
#define SCL0 1<< 4
#define I2EN 1<< 6
#define STA  1<< 5
#define ST0  1<< 4
#define SI   1<< 3
#define AA   1<< 2
unsigned char getkey(void);
void i2c_init(void);
void i2c_write(unsigned char addr,unsigned char dat);
void delay(unsigned int k);
unsigned char seg_dat[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x88,0x83,0xC6,0xA1,0x86,0x8E};
unsigned char scan;
int main(void)
{ unsigned char tpl;
IODIR0 =0xFFFFF0FF;
i2c_init();
PINSEL1 = 0;
scan=0;
do{
   tpl=getkey();
   i2c_write(0x70,seg_dat[tpl]);
}while(1);
}
unsigned char getkey()
{ unsigned long int tpl;
do{
switch(scan)
	{ case 0:
    IOCLR0=SC0;IOSET0=SC1;IOSET0=SC2;IOSET0=SC3;
	 tpl = IOPIN0 & RTN;
	 if(tpl!=RTN)
	  { switch(tpl)
	 {   case 0x0E00:
	            return(0);
				      break;
	  case 0x0D00:
	            return(1);
				      break;
 case 0x0B00:
	     return(2);
				  break;
       case 0x0700:
	            return(3);
				      break;	
					  }
					  }	
			case 1:
    IOSET0=SC0;IOCLR0=SC1;IOSET0=SC2;IOSET0=SC3;
	 tpl = IOPIN0 & RTN;
	 if(tpl!=RTN)
	  { switch(tpl)
	 {   case 0x0E00:
	            return(4);
				      break;
	  case 0x0D00:
	            return(5);
				      break;
 case 0x0B00:
	     return(6);
				  break;
       case 0x0700:
	            return(7);
				      break;	
					  }
					  }						  
		case 2:
    IOSET0=SC0;IOSET0=SC1;IOCLR0=SC2;IOSET0=SC3;
	 tpl = IOPIN0 & RTN;
	 if(tpl!=RTN)
	  { switch(tpl)
	 {   case 0x0E00:
	            return(8);
				      break;
	  case 0x0D00:
	            return(9);
				      break;
 case 0x0B00:
	     return(10);
				  break;
       case 0x0700:
	            return(11);
				      break;	
					  }
					  }
		case 3:
    IOSET0=SC0;IOSET0=SC1;IOSET0=SC2;IOCLR0=SC3;
	 tpl = IOPIN0 & RTN;
	 if(tpl!=RTN)
	  { switch(tpl)
	 {   case 0x0E00:
	            return(12);
				      break;
	  case 0x0D00:
	            return(13);
				      break;
 case 0x0B00:
	     return(14);
				  break;
       case 0x0700:
	            return(15);
				      break;	
					  }
					  }	}
delay(2);
if (scan==4) scan =0;
 else scan ++;
 }while(1);
 }
 void i2c_init()
{
PINSEL0 = 0| SDA0 | SCL0;
I2C0SCLH = 75;I2C0SCLL =75;
I2C0CONSET = I2EN;
}
void i2c_write(unsigned char addr,unsigned char dat)
{
unsigned char sts;
 I2C0CONSET = STA;
 do{
    sts = I2C0CONSET & SI;
	}while(sts!=SI);
   I2C0CONCLR = STA;
   I2C0DAT = addr;
   I2C0CONSET =AA;
   I2C0CONCLR = SI;
  do{
    sts = I2C0CONSET & SI;
	}while(sts!=SI);
   I2C0DAT =  dat;
   I2C0CONSET =AA;
   I2C0CONCLR = SI;
  do{
    sts = I2C0CONSET & SI;
	}while(sts!=SI);
   I2C0CONSET = ST0  |  AA;
   I2C0CONSET =SI;
   delay(2);
   I2C0CONCLR = SI;
   }
void delay(unsigned int k)
{
   unsigned int i,j;
 for(j=0;j<k;j++)
   for(i=0;i<=800;i++);
   }   
   