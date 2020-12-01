#include <LPC214X.H>
/*---- I2C0 Signals ---------------*/
/************************************/
#define SDA0 1<<6
#define SCL0 1<<4
/*--- I2C0 Signal Declaration */
#define I2EN 1<<6
#define STA  1<<5
#define STO  1<<4
#define SI   1<<3
#define AA   1<<2
//Function declaration
int main(void);
void i2c_init();
void i2c_word_write( unsigned char slave_addr,
                     unsigned char word_addr,
                     unsigned char data );
unsigned char i2c_word_read( unsigned char slave_addr,
                             unsigned char word_addr );
void i2c_write(unsigned char addr, unsigned char dat);
void disp_value(unsigned char value);
void delay(unsigned int k);
//Seven Segment Code
unsigned char seg_dat[]={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x98};
int main()
{
unsigned char count;
//Initialize I2C 
i2c_init();
//Load Count value from EEPROM
count = i2c_word_read(0xA0, 0);
//Limit the value
if(count>9) count=0;
while(1)
 { disp_value(count); //Display Count
   i2c_word_write(0xA0, 0 , count); //Store count
   delay(2000);       //2 Sec Delay
   count++;           //increment count
   //Limit the value
   if(count>9) count=0;
  }
return(0);
}
void i2c_init()
{
//Enable SDA0 & SCL0 Pins
PINSEL0 = 0 | SDA0 | SCL0; 
//Set I2C0 Clock rate to 100Khz
I2C0SCLH = 200; I2C0SCLL = 200;
//Enable I2C 
I2C0CONSET = I2EN;
}
/*------------------------------------------------------*/
void i2c_word_write( unsigned char slave_addr,
                     unsigned char word_addr,
                     unsigned char data )
{
unsigned char sts; 
//Transmit Start Condition
 I2C0CONSET = STA;
 //Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
 I2C0CONCLR = STA; //Clear STA 
//Transmit Slave Address
 I2C0DAT = slave_addr; //Slave Addr.+W
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag
//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
//Transmit Slave Word Address
 I2C0DAT = word_addr; //Slave Word address
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag
//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);

//----------Write Data
 I2C0DAT = data;  //data
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag

//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
//----------End of write
//Stop Bit 
 I2C0CONSET = STO | AA; //Stop & Ack bit
 I2C0CONCLR = SI; //Clear SI flag
 delay(15);
 I2C0CONCLR = SI; //Clear SI flag
}
/*-----------------------------------------------------*/
unsigned char i2c_word_read( unsigned char slave_addr,
                             unsigned char word_addr )
{
  unsigned char sts;
  unsigned char data;

//Transmit Start Condition
 I2C0CONSET = STA;
 //Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
 I2C0CONCLR = STA; //Clear STA 

//Transmit Slave Address
 I2C0DAT = slave_addr; //Slave Addr.+W
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag
//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
}while(sts!=SI);
//Transmit Slave Word Address
 I2C0DAT = word_addr; //Slave Word address
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag
//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
//Stop Bit 
 I2C0CONSET = STO | AA; //Stop & Ack bit
 I2C0CONCLR = SI; //Clear SI flag
 delay(2);
 I2C0CONCLR = SI; //Clear SI flag
/*----------------------------------------------*/
//Repeat Start Condition
 I2C0CONSET = STA;
 //Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
 I2C0CONCLR = STA; //Clear STA 

//Transmit Slave Address (Read)
 I2C0DAT = slave_addr | 1; //Slave Addr.+R
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag
//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
/*------Data Read-------*/
I2C0CONSET = AA; //Ack bit
  I2C0CONCLR = SI; //Clear SI flag
   //Wait for rx to complete
  do{
      sts = I2C0CONSET & SI;
      }while(sts!=SI);
    data = I2C0DAT; //read data
/** Send Data with NOT ACK **/
  I2C0CONCLR = SI | AA; //Clear SI flag
   //Wait for rx to complete
  do{
      sts = I2C0CONSET & SI;
      }while(sts!=SI);
//Stop Bit 
 I2C0CONSET = STO | AA; //Stop & Ack bit
 I2C0CONCLR = SI; //Clear SI flag
 delay(2);
 I2C0CONCLR = SI; //Clear SI flag
  return(data); 
}
/*-----------------------------------------------------*/
void i2c_write(unsigned char addr, unsigned char dat)
{
unsigned char sts;
//Transmit Start Condition
 I2C0CONSET = STA;
 //Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
 I2C0CONCLR = STA; //Clear STA 
//Transmit Slave Address
I2C0DAT = addr; //Slave Addr.+W
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag
//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
//Transmit data
 I2C0DAT = dat; //data
 I2C0CONSET = AA; //Ack bit
 I2C0CONCLR = SI; //Clear SI flag
//Wait for tansmit to complete
do{
   sts = I2C0CONSET & SI;
   }while(sts!=SI);
//Stop Bit 
 I2C0CONSET = STO | AA; //Stop & Ack bit
 I2C0CONCLR = SI; //Clear SI flag
 delay(2);
 I2C0CONCLR = SI; //Clear SI flag
}
void disp_value(unsigned char value)
{ 
//Convert as 7Seg. code and Display in DS3 & DS4
i2c_write(0x70, seg_dat[value]); //PCF8574A => 0x70, PCF8574P => 0x40
}
/*------------------------------------------------------*/
//Delay Program
//Input - delay value in milli seconds
void delay(unsigned int k)  	
{
	unsigned int i,j;
	for (j=0; j<k; j++)
		for(i = 0; i<=5035; i++);
}