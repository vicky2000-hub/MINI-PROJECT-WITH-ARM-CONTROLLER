#include <lpc214x.h>
int main (void); 
void UART1_Init(void); 
voidSendString(char *text); 
int main (void) 
{ 
UART1_Init(); 
while (1) 
{ 
SendString("UART1 Test Program\r\n"); 
} 
} 
void UART1_Init(void) 
{ 
PLL0CON = 0; 
PLL0FEED=0xAA; 
PLL0FEED=0x55;
VPBDIV = 1; 
PINSEL0 |= 0x00050000; 
U1FCR = 0; 
U1LCR = 0x83; 
U1DLL = 0x27; 
U1DLM = 0; 
U1LCR = 3; 
}
voidSendString(char *text) 
{ 
while(*text) 
{ 
while(!(U1LSR & 0x20)); 
U1THR = *text++; 
} 
}
