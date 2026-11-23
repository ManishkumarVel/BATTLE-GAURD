void gsm_code(void)
{
	UART1_STR("AT\r\n");
	delay_ms(200);
	UART1_STR("AT+CMGF=1\r\n");
	delay_ms(200);
	UART1_STR("AT+CMGS=\"+916379106432\"\r\n");
	delay_ms(200);
	UART1_STR("UNAUTHORISED PERSON ACCESS MR MANISH...\r\n");
	delay_ms(200);
	UART1_TX(0X1A);
	delay_ms(200);
}

