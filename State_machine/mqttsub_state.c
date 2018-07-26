#include "state_machine.h"
#include "../Utilities/EF_Uart_queue/Uart_queue.h"

extern word16 mqttclient_get_packetid();
extern MqttClient mqtt_user;
int Mqtt_Sub_status = 0;
extern MqttQoS qos;
MqttTopic topics[1];



ret_codes_t mqttsub_state(void)
{

	MqttSubscribe subscribe;
	static int Sub_failed_Counter = 0;

#if GSM_SIM900

	if(GSM_reset_flag)
	{
		return reset ;
	}
#endif

	topics[0].topic_filter = SUBSCRIBE_TOPICS;
	topics[0].qos = qos;

	memset(&subscribe, 0, sizeof(MqttSubscribe));
	subscribe.packet_id = mqttclient_get_packetid();
	subscribe.topic_count = sizeof(topics)/sizeof(MqttTopic);
	subscribe.topics = topics;
	Mqtt_Sub_status = MqttClient_Subscribe(&mqtt_user, &subscribe);

	if(Mqtt_Sub_status == MQTT_CODE_SUCCESS)
	{
		Sub_failed_Counter = 0;
#if GSM_SIM900

		EF_int_GSM_FlushQueue_AT();
#endif
#if WIFI_ESP

		EF_int_WIFI_FlushQueue_AT();
#endif
		return ok;
	}
	else
	{
		if(Sub_failed_Counter > 1)
		{
			Sub_failed_Counter = 0;
			return fail;
		}
		Sub_failed_Counter++;
		return repeat;

	}


}
