#include <lpc21xx.h>
#include<string.h>
#include "can_header.h"
#include "uart_header.h"
#include "lcd.h"
#include "gsm.h"

int main()
{
	can2_msg m1;
	int i;
	char s[20]="060067882FC6";
	char ch,maddy[20];

	can2_init();       //FIX: called first, so VPBDIV/PCLK is settled before
	                    //the UART divisors below are computed against it
	LCD_init();
	UART0_INIT();
	UART1_INIT();

//	LCD_COMMAND(0x80);
//	LCD_STR("BATTLE GUARD");
//	delay_ms(200);

	m1.id=0x00000150;   //FIX: set once, not re-set every loop iteration
	m1.rtr=0;
	m1.dlc=4;

	while(1)
	{
		for(i=0;i<12;i++)
		{
			ch= UART0_RX();
			maddy[i]=ch;
		}
		maddy[12]='\0';

		//LCD_COMMAND(0xC0);
		//LCD_STR(maddy);
		//delay_ms(200);

		UART0_STR((unsigned char*)maddy);

		if(strcmp(s,maddy)==0)
		{
			//LCD_COMMAND(0xC0);
			//LCD_STR("RFID IS MATCH");
			m1.byteA=0x01;
			m1.byteB=0x00;
		}
		else
		{
			gsm_code();
			//LCD_COMMAND(0xC0);
			//LCD_STR("RFID not MATCH");
			m1.byteA=0x02;
			m1.byteB=0x00;
		}

		can2_tx(m1);
		//delay_ms(200);
		//LCD_COMMAND(0xC0);
		//LCD_STR("can msg sent");
	}
}
