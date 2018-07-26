#include "state_machine.h"

extern MqttClient mqtt_user;
extern U32_t Pub_timer;

ret_codes_t mqttkeep_state(void)
{
	int Mqtt_ping_conn = true;
	static int Keep_failed_Counter = 0;

#if GSM_SIM900

	EF_int_GSM_FlushQueue_MQTT();


	if(GSM_reset_flag)
	{
		return reset ;
	}
#endif
#if WIFI_ESP

	EF_int_WIFI_FlushQueue_MQTT();
#endif

	Pub_timer = 20;

	Mqtt_ping_conn = MqttClient_Ping(&mqtt_user);

	if(!Mqtt_ping_conn == false)
	{
		if(Keep_failed_Counter > 1)
		{
			Keep_failed_Counter = 0;
			return fail;
		}
		Keep_failed_Counter++;
		return repeat;
	}
	Keep_failed_Counter = 0;
	return ok;
}
