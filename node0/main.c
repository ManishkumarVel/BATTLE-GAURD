#include <LPC21xx.H>
#include "lcd.h"
#include "uart.h"
#include "can.h"
#include "delay.h"

#define VALID_CARD "123456789012"

int check_card(unsigned char *card)
{
    unsigned char i;

    for(i = 0; i < 12; i++)
    {
        if(card[i] != VALID_CARD[i])
            return 0;
    }

    return 1;
}

int main(void)
{
    unsigned char card[13];
    unsigned char i;

    /* Initialize LCD */
    lcd_init();

    /* Initialize RFID software UART */
    uart0_init();

    /* Initialize CAN1 */
    can1_init();

    /* Display startup message */
    lcd_cmd(0x01);
    lcd_string("BATTLEGUARD");

    lcd_cmd(0xC0);
    lcd_string("SCAN RFID");

    while(1)
    {
        /* Receive 12 characters from RFID */
        for(i = 0; i < 12; i++)
        {
            card[i] = uart0_rx();
        }

        card[12] = '\0';

        /* Check RFID card */
        if(check_card(card))
        {
            /* Authorized */
            lcd_cmd(0x01);
            lcd_string("ACCESS GRANTED");

            /* Send authorization to Node 1 and Node 2 */
            can1_tx(0x101, 1, 0x01);

            delay_ms(3000);
        }
        else
        {
            /* Unauthorized */
            lcd_cmd(0x01);
            lcd_string("ACCESS DENIED");

            /* Send unauthorized status */
            can1_tx(0x101, 1, 0x00);

            delay_ms(3000);
        }

        /* Ready for next card */
        lcd_cmd(0x01);
        lcd_string("SCAN RFID");
    }
}
