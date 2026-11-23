/*can_header.h -- reconstructed to match the can2_msg struct and
  can2_init/can2_tx/can2_rx calls used in main_project.c. If you already
  have your own working version of this file, use that instead -- this
  is only here so the upload compiles standalone. */
#ifndef __CAN_HEADER_H_
#define __CAN_HEADER_H_

typedef struct
{
	unsigned int id;
	unsigned int rtr;
	unsigned int dlc;
	unsigned int byteA;
	unsigned int byteB;
} can2_msg;

void can2_init(void);
void can2_tx(can2_msg m1);
void can2_rx(can2_msg *m1);

#endif
