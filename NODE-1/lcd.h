/*lcd.h -- reconstructed to match the LCD_init()/LCD_COMMAND()/LCD_STR()/
  delay_ms() calls used in main_project.c. If you already have your own
  working version of this file, use that instead -- this is only here so
  the upload compiles standalone.
  Pin assumptions (same as your other project's LCD driver):
    D0-D7 -> P0.10-P0.17, RS -> P0.18, E -> P0.19 */
#ifndef __LCD_H_
#define __LCD_H_
#include <lpc21xx.h>

#define LCD_D  (0xFF<<10)
#define RS     (1<<18)
#define E      (1<<19)

void delay_ms(unsigned int ms){
	unsigned int i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<6000;j++);
}

static void LCD_pulse_e(void){
	IOSET0=E;
	delay_ms(1);
	IOCLR0=E;
	delay_ms(1);
}

void LCD_COMMAND(unsigned char cmd){
	IOCLR0=RS;
	IOCLR0=LCD_D;
	IOSET0=(cmd<<10)&LCD_D;
	LCD_pulse_e();
	delay_ms(2);
}

void LCD_DATA(unsigned char data){
	IOSET0=RS;
	IOCLR0=LCD_D;
	IOSET0=(data<<10)&LCD_D;
	LCD_pulse_e();
	delay_ms(1);
}

void LCD_init(void){
	IODIR0 |= (LCD_D|RS|E);
	delay_ms(20);
	LCD_COMMAND(0x38); //8-bit, 2-line, 5x8 font
	LCD_COMMAND(0x0C); //display ON, cursor OFF
	LCD_COMMAND(0x06); //entry mode: increment cursor
	LCD_COMMAND(0x01); //clear display
	delay_ms(2);
}

void LCD_STR(unsigned char *str){
	while(*str){
		LCD_DATA(*str);
		str++;
	}
}

#endif
