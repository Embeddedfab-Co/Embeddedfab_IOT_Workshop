#include "state_machine.h"

ret_codes_t error_state(void)
{

	EF_int_GSM_FlushQueue_AT();
	EF_int_GSM_FlushQueue_MQTT();
	EF_Void_GSM_delay(2000);
	GSM_reset_flag = false;


	if(GSM_reset_flag)
	{
		return reset ;
	}
	return ok;

}
