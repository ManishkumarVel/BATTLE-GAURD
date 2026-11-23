/* node3_main.c -- Node3: receives the access decision broadcast from
   Node1 and drives the alert outputs:
     Authorized   -> LED OFF, Buzzer OFF (silent)
     Unauthorized -> LED ON,  Buzzer ON  (alert)
   LED on P1.16, Buzzer on P1.17 -- change if wired elsewhere. */
#include<lpc21xx.h>
#include "header.h"

#define LED1   (1<<16)
#define BUZZER (1<<17)

main(){
	CAN2_MSG rx;

	can2_init();
	IODIR1 |= (LED1|BUZZER);
	IOSET1  = (LED1|BUZZER);

	while(1){
		can2_rx(&rx);

		
			if(rx.byteA==0x01)
			{
				IOSET1 = (LED1|BUZZER);
			}
			else
			{
				IOCLR1 = (LED1|BUZZER);
			}
		
	}
}
