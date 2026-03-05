

#ifndef CAN_IF_CAN_IF_H_
#define CAN_IF_CAN_IF_H_

#include "main.h"

/* ----- API ----- */

void can_if_init(void);

/* ----- called from CAN RX interrupt callback ----- */
void can_if_process_rx(CAN_RxHeaderTypeDef *hdr, uint8_t *data);

/* ----- periodic status transmit ----- */
void can_if_periodic_tx(void);

/* ----- command flags for state machine ----- */
uint8_t can_if_up_cmd(void);
uint8_t can_if_down_cmd(void);

/* ----- LED timer exported for app layer ----- */
extern uint32_t data_led_timer;


#endif /* CAN_IF_CAN_IF_H_ */
