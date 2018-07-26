#include "state_machine.h"

char rf_chanel = RF_CHNL_1;

MqttNet mqtt_Socket;
MqttClient mqtt_user;

U32_t Pub_timer = 40;
byte s8UDP_Buffer[MSG_BUFFER_SIZE] ;
word16 json_length = 0 ;
int Init_flag = false;
#if NRF_24
FSE_CircularBuffer_v2 nrf_spi_buf;
#endif
FSE_CircularBuffer_v2 mqtt_sub_buf;


//=========================================================================================================
//============================================== MCAL Init ================================================
//=========================================================================================================

static void EF_void_MCAL_Init()
{

	_delay_ms(1000);
	DDRD |= (1 << 6) |(1 << 7) ;
	DDRA |= (1 << 1) | (1 << 2);


	EF_void_TimerInit();
	EF_void_Timer0_PORTinit();
	EF_void_Timer0_SetISRCallBack(EF_void_Timer0_ISR_Tasks);

#if NRF_24
	EF_nrf24l01_init(rf_chanel);
#endif

#if MQTTCLIENT
	MqttClientNet_Init(&mqtt_Socket);
#endif
}

//=========================================================================================================
//============================================== MQTT Init ================================================
//=========================================================================================================
static void EF_void_MQTT_Init()
{
#if MQTTCLIENT


	//************************************************************************************
#if GSM_SIM900

//	Pub_timer = 80;
//	PORTA |= (1 << 1);
//
//	EF_Void_GSM_delay(400);
//	PORTA &= ~(1 << 1);
//
//	EF_Void_GSM_delay(2000)
#endif

#endif

}

ret_codes_t entry_state(void)
{

	//************************************************************************************
	if(Init_flag == false)
	{
		EF_void_MCAL_Init();
		Init_flag = true;
	}
	//************************************************************************************
	EF_void_MQTT_Init();
	//************************************************************************************

	return ok;

}


