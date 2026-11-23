/* node2_main.c -- Node2: receives the access decision broadcast from
   Node1, shows it on the LCD, and drives the gate servo:
     Authorized   -> "ACCESS GRANTED", servo 90 deg (gate open)

/*     Unauthorized -> //"ACCESS DENIED",  servo 0 deg  (gate stays closed) */
/*
#include "header.h"
#include "lcd_header.h"
//#include "delay.h"

static void show_title(void){
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x80);
	LCD_STR("BATTLE GUARD");
	LCD_COMMAND(0xC0);
	LCD_STR("Access Control");
	delay_milliseconds(2000);
	LCD_COMMAND(0x01);
}

static void show_status(u8 granted){
   // int i;
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x80);
	if(granted){
		LCD_COMMAND(0X01);
		LCD_STR("ACCESS GRANTED");
		LCD_COMMAND(0xC0);
		LCD_STR("Gate: OPEN");
		//servo_set_angle(90);
	  servo_set_angle(90);

		
		delay_milliseconds(5000);

	
		  servo_set_angle(0);
		
		}
	
	else{
		LCD_COMMAND(0X01);
		LCD_STR("ACCESS DENIED");
		LCD_COMMAND(0xC0);
		LCD_STR("Gate: CLOSED");
		//servo_set_angle(0);
		servo_set_angle(0);
	}
	}


main(){
	CAN2_MSG rx;

	can2_init();
	LCD_INIT();
	servo_init();

	show_title();
	show_status(0); 
	servo_set_angle(0);           //default to closed until first decision arrives

	while(1){
		can2_rx(&rx);

		if(rx.byteA==0x01){
			show_status(1);
		}
		else
		{
		show_status(0);
		}
	}
}
*/
/* node2_main.c -- Node2: receives the access decision broadcast from
   Node1, shows it on the LCD, and drives the gate servo:
     Authorized   -> "ACCESS GRANTED", servo 90 deg (gate open)
     Unauthorized -> "ACCESS DENIED",  servo 0 deg  (gate stays closed) */

#include "header.h"
#include "lcd_header.h"
//#include "delay.h"

static void show_title(void){
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x80);
	LCD_STR("BATTLE GUARD");
	LCD_COMMAND(0xC0);
	LCD_STR("Access Control");
	delay_milliseconds(2000);
	LCD_COMMAND(0x01);
}

static void show_status(u8 granted){
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x80);

	if(granted){
		LCD_COMMAND(0X01);
		LCD_STR("ACCESS GRANTED");
		LCD_COMMAND(0xC0);
		LCD_STR("Gate: OPEN");

		/* Gate opens immediately */
		servo_set_angle(90);

		/* Gate stays OPEN for 5 seconds */
		//delay_milliseconds(5000);

		/* Gate closes */
		//servo_set_angle(0);
	}
	else{
		LCD_COMMAND(0X01);
		LCD_STR("ACCESS DENIED");
		LCD_COMMAND(0xC0);
		LCD_STR("Gate: CLOSED");

		/* Gate stays CLOSED */
		servo_set_angle(0);
	}
}

main(){
	CAN2_MSG rx;

	can2_init();
	LCD_INIT();
	servo_init();

	show_title();
	show_status(0);

	servo_set_angle(0);           //default to closed until first decision arrives

	while(1){
		can2_rx(&rx);

		if(rx.byteA==0x01){
			show_status(1);
		}
	//	else if(rx.byteA==0x02){
		//	show_status(0);
	//	}
	}
}

