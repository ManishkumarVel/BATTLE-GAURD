/* servo_driver.c -- Node2: generates a 50Hz servo control signal on P0.1
   (PWM3 output). */

#include <LPC21xx.H>
#include "header.h"

void servo_init(void){
	VPBDIV = 1;			// PCLK = CCLK = 60MHz

	PINSEL0 &= ~(3 << 2);
	PINSEL0 |=  (2 << 2);		// P0.1 = PWM3

	PWMPR = 3;			// 60MHz/(3+1) = 15MHz

	PWMMR0 = 300000 - 1;		// 20ms period = 50Hz

	PWMMR3 = 7500;			// Initial position = CLOSED

	PWMMCR = 0x00000003;		// Reset TC on MR0 match

	PWMPCR = 0x00000800;		// Enable PWM3

	PWMTCR = 0x00000009;		// Enable PWM and counter

	PWMLER = 0x08;
}

void servo_set_angle(u16 angle_deg){

	if(angle_deg == 0)
	{
		/* Gate CLOSED */
		PWMMR3 = 7500;
		PWMLER = 0x08;
	}
	else if(angle_deg == 90)
	{
		/* Gate OPEN */
		PWMMR3 = 21750;
		PWMLER = 0x08;																			    
	}
}