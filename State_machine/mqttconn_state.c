#include "state_machine.h"
MqttConnect mqtt_information;

word16 keep_alive_sec = DEFAULT_KEEP_ALIVE_SEC;
char clean_session = 1;
const char* client_id = DEFAULT_CLIENT_ID;
int enable_lwt = 0;

extern MqttClient mqtt_user;
int Mqtt_Con_status = true;
extern U32_t Pub_timer;
extern int Init_flag ;
extern MqttNet mqtt_Socket;

static int mqttclient_message_cb(MqttClient *client, MqttMessage *msg,
		byte msg_new, byte msg_done)
{
	word32 len;
	byte buf[MSG_RXBUFFER_SIZE + 1];

	(void)client; /* Supress un-used argument */

	if (msg_new) {
		/* Determine min size to dump */
		len = msg->topic_name_len;
		if (len > PRINT_BUFFER_SIZE) {
			len = PRINT_BUFFER_SIZE;
		}
		XMEMCPY(buf, msg->topic_name, len);
		buf[len] = '\0'; /* Make sure its null terminated */

	}

	/* Print message payload */
	len = msg->buffer_len;
	if (len > PRINT_BUFFER_SIZE) {
		len = PRINT_BUFFER_SIZE;
	}
	XMEMCPY(buf, msg->buffer, len);
	buf[len] = '\0'; /* Make sure its null terminated */


	if (msg_done) {
	}

	/* Return negative to terminate publish processing */
	return MQTT_CODE_SUCCESS;
}

unsigned char MQTT_Tx_Array[MSG_BUFFER_SIZE] = {0};
unsigned char MQTT_Rx_Array[MSG_RXBUFFER_SIZE] = {0};


static void EF_void_MQTT_Conn(int num , ret_codes_t *state)
{
	static int retries = 0;

#if GSM_SIM900

	if(GSM_reset_flag)
	{
		*state = reset;
		return  ;
	}
#endif

	MqttClient_Init(&mqtt_user , &mqtt_Socket , mqttclient_message_cb ,MQTT_Tx_Array,sizeof(MQTT_Tx_Array),MQTT_Rx_Array,sizeof(MQTT_Rx_Array) ,MQTT_AT_DELAY);

#if GSM_SIM900

	EF_int_GSM_FlushQueue_MQTT();
#endif

#if WIFI_ESP

	EF_int_WIFI_FlushQueue_MQTT();
#endif

	mqtt_information.username = MQTT_USERNAMR;
	mqtt_information.password = MQTT_PASSWORD;
	mqtt_information.keep_alive_sec = keep_alive_sec;
	mqtt_information.clean_session = clean_session;
	mqtt_information.client_id = client_id;
	mqtt_information.enable_lwt = enable_lwt;
	Pub_timer = 1;




#if GSM_SIM900
	MqttClient_NetDisconnect(&mqtt_user );
	MqttClient_NetConnect(&mqtt_user , SERVER_IP , SERVER_PORT , MQTT_CON_DELAY , false , NULL);
#endif
#if WIFI_ESP
	MqttClient_NetDisconnect(&mqtt_user );
	MqttClient_NetConnect(&mqtt_user , SERVER_IP , SERVER_PORT , MQTT_CON_DELAY , false , NULL);
#endif


	Mqtt_Con_status = MqttClient_Connect(&mqtt_user ,&mqtt_information);

	if(Mqtt_Con_status == 0)
	{
		*state = ok;
		retries = 0;
		return ;
	}
	else
	{
		*state = repeat;
	}

	if(retries > num)
	{
		*state = fail;
	}


	retries++;
#if GSM_SIM900

	MqttClient_NetDisconnect(&mqtt_user );
	MqttClient_NetConnect(&mqtt_user , SERVER_IP , SERVER_PORT , MQTT_CON_DELAY , false , NULL);
	MqttClient_Disconnect(&mqtt_user);
#endif
#if WIFI_ESP

	MqttClient_NetDisconnect(&mqtt_user );
	MqttClient_NetConnect(&mqtt_user , SERVER_IP , SERVER_PORT , MQTT_CON_DELAY , false , NULL);
	MqttClient_Disconnect(&mqtt_user);
#endif




}

ret_codes_t mqttconn_state(void)
{
	ret_codes_t conn_state = repeat;
	EF_void_MQTT_Conn(1 , &conn_state);
	return conn_state;
}
