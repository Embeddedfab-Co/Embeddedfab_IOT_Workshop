#include "state_machine.h"

ret_codes_t error_state(void)
{
#if GSM_SIM900

	EF_int_GSM_FlushQueue_AT();
	EF_int_GSM_FlushQueue_MQTT();

	if(GSM_reset_flag)
	{
		return reset ;
	}
#endif
	return ok;

}
