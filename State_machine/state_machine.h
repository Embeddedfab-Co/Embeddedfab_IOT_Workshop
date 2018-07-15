/*
 * state_machine.h
 *
 *  Created on: 12 Jun 2018
 *      Author: root
 */

#ifndef STATE_MACHINE_STATE_MACHINE_H_
#define STATE_MACHINE_STATE_MACHINE_H_

#include "../main.h"

typedef enum state_codes{
    entry = 0,
    ideal,
	mqttconn,
	mqttpub,
	mqttsub,
	mqttkeep,
	mqttwait,
	error,

    /* the last entry is just for looping over the enum */
    STATE_LAST
}state_codes_t;

/* return codes */
typedef enum ret_codes{
    ok = 0,
    fail,
    repeat,
    reset,

    /* the last entry is just for looping over the enum */
    RET_LAST
}ret_codes_t;

typedef struct transition{
    state_codes_t dst_state;
}transition_t;

ret_codes_t entry_state(void);
ret_codes_t ideal_state(void);
ret_codes_t mqttconn_state(void);
ret_codes_t mqttpub_state(void);
ret_codes_t mqttsub_state(void);
ret_codes_t mqttkeep_state(void);
ret_codes_t mqttwaitmsg_state(void);
ret_codes_t error_state(void);

state_codes_t lookup_transitions(state_codes_t state_codes, ret_codes_t ret_codes);

extern volatile unsigned char GSM_reset_flag;


#endif /* STATE_MACHINE_STATE_MACHINE_H_ */
