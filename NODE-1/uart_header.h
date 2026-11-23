/*uart_header.h -- FIXED: the original hardcoded DLL=97/DLM=0 assumed the
  *default* peripheral clock (PCLK = CCLK/4, i.e. ~15MHz if CCLK=60MHz).
  But can_header.h's can2_init() sets VPBDIV=1, which raises PCLK to the
  full 60MHz -- and since that's a live, shared clock (not latched), it
  changes the UART's actual baud rate too, for every UART call made after
  can2_init() runs. Call can2_init() FIRST (see main_project.c), and this
  version computes the correct divisor for PCLK=60MHz so 9600 baud is
  actually 9600 baud throughout, not just before the first CAN call. */
#include <lpc21xx.h>

void UART0_INIT(void)
{
	unsigned int divisor;
	PINSEL0|=0X5;
	U0LCR=0X83;
	divisor = 60000000UL/(16UL*9600UL);  //PCLK=60MHz (set by can2_init, called first)
	U0DLL = divisor & 0xFF;
	U0DLM = (divisor>>8) & 0xFF;
	U0LCR=0X03;
}

unsigned char UART0_RX(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}

void UART0_TX(unsigned char TXbyte)
{
	while(((U0LSR>>5)&1)==0);
	U0THR=TXbyte;
}

void UART0_STR(unsigned char* s)
{
	while(*s)
	{
		while(((U0LSR>>5)&1)==0);
		U0THR=*s++;
	}
}

void UART1_INIT(void)
{
	unsigned int divisor;
	PINSEL0|=0X00050000;
	U1LCR=0X83;
	divisor = 60000000UL/(16UL*9600UL);  //PCLK=60MHz (set by can2_init, called first)
	U1DLL = divisor & 0xFF;
	U1DLM = (divisor>>8) & 0xFF;
	U1LCR=0X03;
}

unsigned char UART1_RX(void)
{
	while((U1LSR&1)==0);
	return U1RBR;
}

void UART1_TX(unsigned char TXbyte)
{
	while(((U1LSR>>5)&1)==0);
	U1THR=TXbyte;
}

void UART1_STR(unsigned char* s)
{
	while(*s)
	{
		while(((U1LSR>>5)&1)==0);
		U1THR=*s++;
	}
}
