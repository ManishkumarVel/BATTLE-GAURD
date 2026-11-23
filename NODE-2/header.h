/*header.h -- shared across Node1 (RFID+GSM/TX), Node2 (LCD+Servo/RX),
  Node3 (LED+Buzzer/RX) for the BattleGuard project */
#ifndef __HEADER_H_
#define __HEADER_H_

typedef  unsigned int u32;
typedef  signed int s32;
typedef  unsigned char u8;
typedef  signed char s8;
typedef  unsigned short int u16;
typedef   signed short int s16;

typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN2_MSG;

/* ---- CAN message used to broadcast the access decision ---- */
#define ACCESS_MSG_ID   0x150
#define ACCESS_DENIED   0
#define ACCESS_GRANTED  1

/* ---- CAN driver (from can2_driver.c) ---- */
void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);

/* ---- UART0 driver (Node1: RFID reader) ---- */
void uart0_init(u32 baud);
void uart0_tx(u8 ch);
u8   uart0_rx(void);
void uart0_tx_string(s8 *s);

/* ---- UART1 driver (Node1: GSM module, alerts only) ---- */
void uart1_init(u32 baud);
void uart1_tx(u8 ch);
void uart1_tx_string(s8 *s);

/* ---- Servo driver via PWM1 (Node2) ---- */
void servo_init(void);
void servo_set_angle(u16 angle_deg); /* 0 - 180 */

#endif
