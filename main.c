
#include "State_machine/state_machine.h"

static ret_codes_t (* const state[])(void) = { entry_state, ideal_state, mqttconn_state, mqttpub_state
		, mqttsub_state , mqttkeep_state, mqttwaitmsg_state , error_state};

//*********************************************************************************************************
//============================================== Main =====================================================
//*********************************************************************************************************
int main(void)
{
	state_codes_t cur_state = entry;
	ret_codes_t rc;
	ret_codes_t (* state_fun)(void);
	// Loop forever, processing the osn-screen animation.  All other work is
	// done in the interrupt handlers.
	while(1)
	{
		state_fun = state[cur_state];
		rc = state_fun();
		cur_state = lookup_transitions(cur_state, rc);
	}
}
//*********************************************************************************************************
//========================================== Main End =====================================================
//*********************************************************************************************************
