
#include "state_machine.h"

int Mqtt_Wait_status = true;
//extern word16 mqttclient_get_packetid(void);
//extern MqttClient mqtt_user;
//extern MqttTopic topics[1];

ret_codes_t mqttwaitmsg_state(void)
{

	if(GSM_reset_flag)
	{
		return reset ;
	}

	int size = sizeof(SUBSCRIBE_TOPICS_NAME )+ SUBSCRIBE_TOPICS_EX;
	//	int size = 0;
	Mqtt_Wait_status = EF_Int_Mqtt_read(&size);

	if(Mqtt_Wait_status != false)
	{

		EF_int_GSM_FlushQueue_MQTT();
		EF_int_GSM_FlushQueue_AT();
	}

	return repeat;

}
