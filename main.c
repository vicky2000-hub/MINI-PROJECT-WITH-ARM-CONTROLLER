#include <lpc214x.h>
#define I2EN (1<<6) //Enable/Disable bit
#define STA  (1<<5) //Start Set/Clear bit
#define STO  (1<<4) //Stop bit
#define SI   (1<<3) //Serial Interrupt Flag Clear bit
#define AA   (1<<2) //Assert Acknowledge Set/Clear bit
void i2c_delay (unsigned int delay);
void lcd_write_data (unsigned char data);
void lcd_send_string (char *data);
void lcd_write_cmd (unsigned char cmd);
void lcd_init ();
void pll_init(void);
void waitforsi (void);
void i2c_send_start (void);
void i2c_send_stop (void);
void i2c_init (void);
void i2c_write (unsigned char data);
unsigned char address = 0x4E;


void i2c_delay (unsigned int delay)
{
	delay = delay*100;
	while (delay--);
}


void lcd_write_data (unsigned char data)
{
	unsigned char data_l, data_u;
	data_l = (data<<4)&0xf0;  //select lower nibble by moving it to the upper nibble position
	data_u = data&0xf0;  //select upper nibble
	i2c_send_start();
	i2c_write (address);
	i2c_write (data_u|0x05);  //enable=1 and rs =1
	i2c_write (data_u|0x01);  //enable=0 and rs =1
	i2c_write (data_l|0x05);  //enable =1 and rs =1
	i2c_write (data_l|0x01);  //enable=0 and rs =1
	i2c_send_stop();
}


void lcd_send_string (char *data)
{
	while (*data) lcd_write_data (*data++);
}


void lcd_write_cmd (unsigned char cmd)
{
	unsigned char cmd_l, cmd_u;
	cmd_l = (cmd<<4)&0xf0;  //select lower nibble by moving it to the upper nibble position
	cmd_u = cmd&0xf0;  //selct upper nibble
	
	
	i2c_send_start ();
	i2c_write (address);
	i2c_write (cmd_u|0x04);  //enable =1, rs =0
	i2c_write (cmd_u);  //enable =0, rs =0
	
	i2c_write (cmd_l|0x04);  //enable =1, rs =0
	i2c_write (cmd_l);  //enable =0, rs =0
	
	i2c_send_stop ();
}

void lcd_init ()
{
 i2c_init ();
 lcd_write_cmd (0x02);
 lcd_write_cmd (0x28);
 lcd_write_cmd (0x0c);
 lcd_write_cmd (0x80);
}
void pll_init(void)
{
 PLL0CON = 0x01;    //Enable PLL
 PLL0CFG = 0x24;    //Multiplier and divider setup  M is (5-1=4) because we need 60 Mhz and we have 12 so 5 is multiplier. P is 2. so 0x24.
 PLL0FEED = 0xAA;   //Feed sequence
 PLL0FEED = 0x55;   // feed sequence
 
 while(!(PLL0STAT & 0x00000400)); //is locked?
 
 PLL0CON = 0x03;   //Connect PLL after PLL is locked
 PLL0FEED = 0xAA;  //Feed sequence
 PLL0FEED = 0x55;  //Feed sequence
}

void waitforsi (void)
{
	while (!(I2C0CONSET & SI));  //while interrupt in not set /wait till SI goes 1
}


void i2c_send_start (void)
{
	I2C0CONSET = STA;  // set start bit
	waitforsi();  //wait for interrupt to set it will transmit previous condition
}


void i2c_write (unsigned char data)
{
	
	I2C0DAT = data;  // load data
	I2C0CONCLR = SI|STA|AA;  //clear interrupt, start, ack
	waitforsi ();  // wait for condition  to transmit
}

void i2c_send_stop (void)
{
	I2C0CONCLR = AA|SI;  // clear ack and interrupt
	I2C0CONSET = STO;  // send stop
}


void i2c_init (void)
{
	PINSEL0 = (1<<4)|(1<<6);  // for i2c line
	I2C0SCLH = 75;  // 15MHz/150 = 100000 speed i2c
	I2C0SCLL = 75;
	I2C0CONCLR = STA|STO|AA|SI;  // clear all bits
	I2C0CONSET = I2EN;  // enable bit set
}


int main ()
{
	pll_init ();
	VPBDIV=0x00;   //pclk = cclk/4 = 15MHz
	//timer0_init (15000);  // timer init with 1ms delay 
	
  lcd_init ();   // initialise lcd and i2c will be initialise automatically
	
	lcd_send_string ("hello !!");   // write data 
	
	while (1);
}