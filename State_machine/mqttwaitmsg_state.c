
#include "state_machine.h"

int Mqtt_Wait_status = true;
//extern word16 mqttclient_get_packetid(void);
//extern MqttClient mqtt_user;
//extern MqttTopic topics[1];

ret_codes_t mqttwaitmsg_state(void)
{

#if GSM_SIM900

	if(GSM_reset_flag)
	{
		return reset ;
	}
#endif

	int size = sizeof(SUBSCRIBE_TOPICS_NAME )+ SUBSCRIBE_TOPICS_EX;
	Mqtt_Wait_status = EF_Int_Mqtt_read(&size);

	if(Mqtt_Wait_status != false)
	{

#if GSM_SIM900
		EF_int_GSM_FlushQueue_MQTT();
		EF_int_GSM_FlushQueue_AT();
#endif
#if WIFI_ESP

		EF_int_WIFI_FlushQueue_MQTT();
		EF_int_WIFI_FlushQueue_AT();
#endif
	}

	return repeat;

}
