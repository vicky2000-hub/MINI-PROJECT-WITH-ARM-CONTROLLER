#include <lpc214x.h>
#define EINT2 3<<14    //Configure P0.7 as EINT2 input => PINSEL0 
#define LEDS  0xFF<<8   //LED => P0.8 to P0.15
void eint2_isr(void) __attribute__ ((interrupt("IRQ")));
unsigned long count;
void delay(int n)
{
int i,j;
for(i=0;i<n;i++)
 {for(j=0;j<1007;j++)   //5035 for 60Mhz ** 1007 for 12Mhz
    {;}
 }
}
void eint2_isr(void)
{
EXTINT  = 1<<2;  //External Interrupt Flag register
count++;
if(count>255) count=0;
VICVectAddr=0xFF;
}
int main(void)
{
IODIR0   = LEDS; //Configure Port0 as output Port
PINSEL0  = EINT2; //Configure Port0.7 as EINT2 Input
PINSEL1  = 0;
VICIntEnable = 1 << 16; //Enable EINT2 interrupt
VICIntSelect = 0; //Interrupt request assigned to the IRQ category
EXTMODE  = 1<<2; 
EXTPOLAR = 0; 
VICVectAddr0 = (unsigned long) eint2_isr;
VICVectCntl0 =0x20 | 16;
count=0;
while(1){
         IOSET0 =  LEDS;  //Switch OFF all LEDS
         IOCLR0 = count << 8;  //Set VAlue
         delay(1000);
        }
}
