#include "state_machine.h"

MqttQoS qos = DEFAULT_MQTT_QOS;
extern MqttClient mqtt_user;

extern byte s8UDP_Buffer[MSG_BUFFER_SIZE] ;
extern word16 json_length;
extern U32_t Pub_timer ;

static int mPacketIdLast;

extern FSE_CircularBuffer_v2 nrf_spi_buf;

#if NRF_24

extern uint8_t bufferin[NRF24L01_PAYLOAD] ;
extern uint8_t bufferout[NRF24L01_PAYLOAD] ;
#endif

extern char Mqtt_pub_topic_name[] ;



word16 mqttclient_get_packetid(void)
{
	mPacketIdLast = (mPacketIdLast >= MAX_PACKET_ID) ? 1 : mPacketIdLast + 1;
	return (word16)mPacketIdLast;
}

static void EF_void_Mqtt_Pub(ret_codes_t *state )
{
	static int Pub_failed_Counter = 0;

#if GSM_SIM900

	if(GSM_reset_flag)
	{
		*state = reset;
		return  ;
	}
#endif

	MqttPublish publish;
	memset(&publish, 0, sizeof(MqttPublish));
	publish.retain = 0;
	publish.qos = qos;
	publish.duplicate = 0;
	publish.topic_name = Mqtt_pub_topic_name;
	publish.packet_id = mqttclient_get_packetid();

#if NRF_24
	publish.buffer = (byte*)s8UDP_Buffer;
	publish.total_len = (word16)json_length;
#else
	publish.buffer = (byte*)PUBLISH_MESSAGE;
	publish.total_len = (word16)sizeof(PUBLISH_MESSAGE);
#endif
	int Mqtt_Pub_status = true;

	Mqtt_Pub_status = MqttClient_Publish(&mqtt_user, &publish);
	if(Mqtt_Pub_status == MQTT_CODE_SUCCESS)
	{
		Pub_failed_Counter = 0;
		*state = ok;
		return ;

	}
	else
	{
		*state = repeat;
#if NRF_24

		if(!nrf_spi_buf.isFull(&nrf_spi_buf))
		{
			nrf_spi_buf.enqueue(&nrf_spi_buf ,bufferout, ELEMENT_SIZE_V2);
		}
#endif
		if(Pub_failed_Counter > 1)
		{
			Pub_failed_Counter = 0;
			*state = fail;
		}
		Pub_failed_Counter++;
	}


}


ret_codes_t mqttpub_state(void)
{
	ret_codes_t pub_state = repeat;
	EF_void_Mqtt_Pub(&pub_state);
	return pub_state;
}
