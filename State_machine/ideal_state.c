#include "state_machine.h"

//=========================================================================================================
//============================================== RF =======================================================
//=========================================================================================================

#if NRF_24
uint8_t bufferin[NRF24L01_PAYLOAD] = {"tiger"};
uint8_t bufferout[NRF24L01_PAYLOAD] = {"tiger"};
uint8_t data_recvd_pipe = 0;
/* nrf24l01 variables */
#endif

extern U32_t Pub_timer;
extern byte s8UDP_Buffer[MSG_BUFFER_SIZE] ;
extern word16 json_length;
extern FSE_CircularBuffer_v2 mqtt_sub_buf;
extern FSE_CircularBuffer_v2 nrf_spi_buf;
extern char rf_chanel ;

char Mqtt_pub_topic_name[] = DEFAULT_TOPIC_NAME;

#if NRF_24

static int32_t encode_json_data(byte * pRecvBuf)
{

	char dataframe[3] = {0};
	char incomingbyte = 0;
	int index = 0;
	int Temperature = 0;
	int32_t rc = 0 ;


	for(int i = 0 ; i < 32 ; i ++)
	{
		if(bufferout[i] == 't')
		{
			incomingbyte='t';
			memset(dataframe , 0 ,sizeof(dataframe));
			index = 0;
		}
		else if(bufferout[i] == 'l')
		{
			incomingbyte = 'l';
			Temperature = atoi(dataframe);
			memset(dataframe , 0 ,sizeof(dataframe));
			index = 0;
		}
		else if(bufferout[i] == 'h')
		{
			incomingbyte = 'h';
			//node_report.Lux = atoi(dataframe);
			memset(dataframe , 0 ,sizeof(dataframe));
			index = 0;
			break;
		}

		if(incomingbyte == 't' && bufferout[i] != 't' )
		{
			dataframe[index] = bufferout[i];
			index++;
		}
		else if(incomingbyte == 'l' && bufferout[i] != 'l' )
		{
			dataframe[index] = bufferout[i];

			if(dataframe[0] == 'b')
			{
				strcpy(Mqtt_pub_topic_name , BBETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
			else if(dataframe[0] == 'g')
			{
				strcpy(Mqtt_pub_topic_name , GBETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
			else if(dataframe[0] == 'd')
			{
				strcpy(Mqtt_pub_topic_name , DBETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
			else if(dataframe[0] == 'f')
			{
				strcpy(Mqtt_pub_topic_name , FBETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
			else if(dataframe[0] == 'i')
			{
				strcpy(Mqtt_pub_topic_name , IBETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
			else if(dataframe[0] == 'a')
			{
				strcpy(Mqtt_pub_topic_name , ABETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
			else if(dataframe[0] == 'j')
			{
				strcpy(Mqtt_pub_topic_name , JBETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
			else if(dataframe[0] == 'e')
			{
				strcpy(Mqtt_pub_topic_name , EBETA_TOPIC_NAME);
				rc = sprintf((char *)pRecvBuf,(const char *)"{\"value\":%d}" ,  Temperature);
			}
		}

	}


	return rc;
}
#endif


static word16 EF_void_ideal(ret_codes_t *state)
{
	int length = 0;
	EF_void_TimerChangeTimeOut(WATING_MQTT_MSG_TIMER_ID,MQTT_PUB_DELAY);
	EF_void_TimerStart(WATING_MQTT_MSG_TIMER_ID);


	static U32_t counter_loop = 0 ;
	static U32_t timer_loop = 0 ;
#if GSM_SIM900

	if(GSM_reset_flag)
	{
		*state = reset;
		return 0 ;
	}
#endif

	*state = repeat;

#if NRF_24
	Pub_timer = 10;

	if(!nrf_spi_buf.isEmpty(&nrf_spi_buf))   //if data is ready
	{
		/* read buffer */
		memset(bufferout , 0 , sizeof(bufferout));
		uint8_t length_queue = 0;
		nrf_spi_buf.dequeue(&nrf_spi_buf ,bufferout, &length_queue);

		length = encode_json_data(s8UDP_Buffer);

		EF_void_TimerStop(WATING_MQTT_MSG_TIMER_ID);
		EF_void_TimerReset(WATING_MQTT_MSG_TIMER_ID);
		*state = ok;
		Pub_timer = 100;

		counter_loop = EF_u32_TimerGetCounterValue(WATING_MQTT_MSG_TIMER_ID);

		return length;

	}/* end of read data */

#endif
	if(!mqtt_sub_buf.isEmpty(&mqtt_sub_buf))   //if data is ready
	{
		/* read buffer */
		uint8_t Data_received[ELEMENT_SIZE_V2] ;
		memset(Data_received , 0 , sizeof(Data_received));
		uint8_t length_queue = 0;
		mqtt_sub_buf.dequeue(&mqtt_sub_buf ,Data_received, &length_queue);
		int Button = atoi((char*)Data_received);


		if(Button == 0)
		{
			PORTD |= (1 << 6);

		}
		else
		{
			PORTD &= ~(1 << 6);

		}

		counter_loop = EF_u32_TimerGetCounterValue(WATING_MQTT_MSG_TIMER_ID);

	}/* end of read data */




	if((EF_u32_TimerGetCounterValue(WATING_MQTT_MSG_TIMER_ID) - timer_loop) > Pub_timer)
	{
		/* Keep Alive */
		PORTD ^= (1 << 7);

		timer_loop = EF_u32_TimerGetCounterValue(WATING_MQTT_MSG_TIMER_ID);

	}

	if((EF_u32_TimerGetCounterValue(WATING_MQTT_MSG_TIMER_ID) - counter_loop) > MQTT_KEEPALIVE_DELAY)
	{
		PORTD |= (1 << 7);
		counter_loop = EF_u32_TimerGetCounterValue(WATING_MQTT_MSG_TIMER_ID);
		EF_nrf24l01_init(rf_chanel);
		*state = fail;
	}






	return length;
}

ret_codes_t ideal_state(void)
{
	ret_codes_t read_state =  repeat;
	json_length = EF_void_ideal(&read_state);

	return read_state;
}


