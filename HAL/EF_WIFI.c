



#include "EF_WIFI.h"
#include "stdlib.h"
#include "string.h"
#include "avr/interrupt.h"
#include "../MCAL/EF_UART.h"
#include "util/delay.h"
#include "../Utilities/EF_SpechialTIMER_cfg.h"
#include "../ServiceLayer/FSE_CircularBuffer_v2/FSE_CircularBuffer_v2.h"
#include "../Utilities/EF_Uart_queue/Uart_queue.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#if WIFI_ESP

extern volatile U8_t mqtt_flag ;
extern volatile U8_t at_flag ;
UART_cfg_str uart_WIFI = {WIFI_UART_BAUDRATE_INIT,NUMBER_OF_BITS_8,ONE_STOP_BIT,NO_PARITY,TRUE,FALSE,TRUE,TRUE};

static int Queue_1st_config = false ;
AtCommanderConfig WIFI_Atcommand_Config ;
extern FSE_CircularBuffer_v2 nrf_spi_buf;
extern FSE_CircularBuffer_v2 mqtt_sub_buf;


/****************************************************************************
 * Function    : EF_void_WIFI_Init .
 *
 * DESCRIPTION : INIT the WIFI module .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_void_WIFI_Init(void)
{

	EF_Void_WIFI_atcommander_init(&WIFI_Atcommand_Config);

#ifdef FRIST_ENTER_ATCOMMAND_CONFIG
	UART_cfg_str atcommand_uart = {WIFI_UART_BAUDRATE_DEFAULT,NUMBER_OF_BITS_8,ONE_STOP_BIT,NO_PARITY,TRUE,FALSE,TRUE,TRUE};
	EF_void_UART_Init(&atcommand_uart);
	EF_Void_WIFI_atcommander_ConfigATmodeUart();
#endif

	if(Queue_1st_config == false)
	{

		FSE_CircularBuffer_v2_ctor(&nrf_spi_buf);

		FSE_CircularBuffer_v2_ctor(&mqtt_sub_buf);
		Queue_1st_config = true;
	}


	EF_void_UART_Init(&uart_WIFI);
	EF_u8_TimerCreate(WATING_MQTT_MSG_TIMER_ID , 3000);
	EF_u8_TimerCreate(WIFI_MQTT_TIMER_DELAY , ATMODE_TIMEOUT);


	EF_Void_WIFI_Connection_Config();
}
/****************************************************************************
 * Function    : EF_Void_WIFI_WriteArray .
 *
 * DESCRIPTION : Send Array over WIFI .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: Array length.
 ******************************************************************************/
unsigned char EF_U8_t_WIFI_WriteArray(U8_t *BUFFER , U8_t Len)
{
	return EF_U8_t_UART_SendArray(BUFFER,Len);
}
/****************************************************************************
 * Function    : EF_Void_WIFI_WriteByte .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : pointer to void UART port  : byte.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_WIFI_WriteByte(U8_t data)
{
	EF_BOOLEAN_UART_PutChar(data);
}
/****************************************************************************
 * Function    : EF_Void_WIFI_ReadArray .
 *
 * DESCRIPTION : Receive Array over WIFI .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_WIFI_ReadArray(U8_t *BUFFER , U8_t Len)
{
	EF_void_UART_GetArray(BUFFER,Len);
}
/****************************************************************************
 * Function    : EF_Void_WIFI_ReadByte .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_WIFI_ReadByte()
{
	U8_t return_data;
	EF_BOOLEAN_UART_GetChar(&return_data);
	return return_data;
}

/****************************************************************************
 * Function    : EF_Void_WIFI_connect .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/

int EF_Void_WIFI_connect(const char* host, unsigned short port)
{

	int rc = sprintf(WIFI_Atcommand_Config.Data,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n" ,host, port);

	WIFI_Atcommand_Config.size = rc;
	WIFI_Atcommand_Config.platform.response_delay_ms = 150;

	EF_void_TimerChangeTimeOut(WIFI_AT_TIMER_TIMEOUT,WIFI_AT_COMMANDER_TIMEOUT);
	EF_void_TimerStart(WIFI_AT_TIMER_TIMEOUT);
	while(!EF_Int_WIFI_atcommander_ipstart_SetRequest()&& !EF_BOOLEAN_TimerCheck(WIFI_AT_TIMER_TIMEOUT));
	EF_void_TimerStop(WIFI_AT_TIMER_TIMEOUT);
	EF_void_TimerReset(WIFI_AT_TIMER_TIMEOUT);

	//	EF_Int_WIFI_atcommander_ipstart_SetRequest();
	return 0 ;
}
/****************************************************************************
 * Function    : EF_Void_WIFI_disconnect .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_WIFI_disconnect()
{
	//	EF_Int_WIFI_atcommander_IPClose_SetRequest();
	return 0;
}

/****************************************************************************
 * Function    : EF_int_WIFI_FlushQueue_AT .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
void EF_int_WIFI_FlushQueue_AT(void)
{
	EF_int_Uart_ClearArray_AT();

}
/****************************************************************************
 * Function    : EF_int_WIFI_FlushQueue_MQTT .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
void EF_int_WIFI_FlushQueue_MQTT(void)
{
	EF_int_Uart_ClearArray_MQTT();

}

/****************************************************************************
 * Function    : EF_void_WIFI_FSE_at_QueueUpdate .
 *
 * DESCRIPTION : Receive Array form Queue and send it to FSE .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
int  EF_void_WIFI_FSE_at_QueueUpdate()
{
	return EF_void_UART_FSE_at_QueueUpdate();
}
/****************************************************************************
 * Function    : EF_void_WIFI_FSE_mqtt_QueueUpdate .
 *
 * DESCRIPTION : Receive Array form Queue and send it to FSE .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
int  EF_void_WIFI_FSE_mqtt_QueueUpdate()
{
	return EF_void_UART_FSE_mqtt_QueueUpdate();
}
/****************************************************************************
 * Function    : EF_U8_t_WIFI_FSEQueuereadArray .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
unsigned char EF_U8_t_WIFI_FSEQueuereadArray(U8_t *BUFFER )
{
	return EF_U8_t_UART_FSEQueuereadArray(BUFFER);
}

/****************************************************************************
 * Function    : EF_U8_t_WIFI_FSEQueuereadByte .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array , len.
 *
 * Return Value: Length.
 ******************************************************************************/
unsigned char EF_U8_t_WIFI_FSEQueuereadByte(U8_t *BUFFER , unsigned char length )
{
	int rc = -1;
	rc = (int)EF_U8_t_UART_FSEQueuereadByte(BUFFER,length);
	if(rc == 0)
	{
		return 0;
	}
	else
	{
		return 1;

	}

}
/****************************************************************************
 * Function    : EF_Void_WIFI_ReadByteFromQueue .
 *
 * DESCRIPTION : read byte form queue over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: true or false..
 ******************************************************************************/
int  EF_Void_WIFI_ReadByteFromQueue(unsigned char *data , int len)
{
	unsigned char rc = 0;


	rc = EF_U8_t_UART_FSEQueuereadByte(data, len);

	if (rc == 0)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

/****************************************************************************
 * Function    : EF_int_WIFI_WaitReadByteFromFSEQueue .
 *
 * DESCRIPTION : read byte form FSEQuee
 *
 * PARAMETERS  : None.
 *
 * Return Value: true or false.
 ******************************************************************************/
int EF_int_WIFI_WaitReadByteFromFSEQueue(unsigned char *data)
{
	int rc = 0;




	rc = EF_U8_t_WIFI_FSEQueuereadArray(data );




	return rc;
}


/****************************************************************************
 * Function    : EF_U8_t_WIFI_SendDataArray .
 *
 * DESCRIPTION : Send data Array over WIFI .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: Array length.
 ******************************************************************************/
int EF_U8_t_WIFI_SendDataArray(U8_t *BUFFER , U8_t Len , int timeout)
{



	EF_Int_WIFI_atcommander_IPSend_SetRequest(Len , timeout / 8);

	EF_int_Uart_ClearFSQQueue_MQTT();
	EF_int_Uart_ClearFSQQueue_AT();

	EF_U8_t_WIFI_WriteArray(BUFFER,Len);

	EF_void_TimerChangeTimeOut(WIFI_MQTT_TIMER_DELAY,timeout);
	EF_void_TimerStart(WIFI_MQTT_TIMER_DELAY);
	while(!EF_BOOLEAN_TimerCheck(WIFI_MQTT_TIMER_DELAY) && mqtt_flag == false);
	mqtt_flag = false;
	EF_void_TimerStop(WIFI_MQTT_TIMER_DELAY);
	EF_void_TimerReset(WIFI_MQTT_TIMER_DELAY);

	EF_void_WIFI_msg_received();


	return (int)Len;


}
/****************************************************************************
 * Function    : EF_Void_WIFI_delay .
 *
 * DESCRIPTION : This Func AT Command required  .
 *
 * PARAMETERS  : delay in ms.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_WIFI_delay(uint32_t delay_ms)
{
	EF_void_TimerChangeTimeOut(WIFI_AT_TIMER_DELAY,delay_ms);
	EF_void_TimerStart(WIFI_AT_TIMER_DELAY);


	while(!EF_BOOLEAN_TimerCheck(WIFI_AT_TIMER_DELAY) );
	EF_void_TimerStop(WIFI_AT_TIMER_DELAY);
	EF_void_TimerReset(WIFI_AT_TIMER_DELAY);
}
/****************************************************************************

						AT Command mode CONFIG API

		ENTER_ATCOMMAND_CONFIG should be defined in atcommander.h

 ******************************************************************************/

#ifdef FRIST_ENTER_ATCOMMAND_CONFIG
/****************************************************************************
 * Function    : EF_Void_WIFI_atcommander_ConfigATmodeUart .
 *
 * DESCRIPTION : Set baud rate for Ethernet module at first time
 *
 * PARAMETERS  : NONE.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Void_WIFI_atcommander_ConfigATmodeUart()
{
	at_commander_close_echo_config(&WIFI_Atcommand_Config);
	atcommander_set_UART(&WIFI_Atcommand_Config);
	_delay_ms(100);
	return 0;
}
#endif
/****************************************************************************
 * Function    : EF_Void_WIFI_atcommander_init .
 *
 * DESCRIPTION : This FUNC INIT WIFI for at command
 * 					you should call timer INIT and UART INIT.
 * 					before enter this function
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_WIFI_atcommander_init(AtCommanderConfig *device)
{
	device->connected = true;
	device->platform.response_delay_ms = WIFI_AT_COMMANDER_DELAY;
	EF_u8_TimerCreate(WIFI_AT_TIMER_DELAY , device->platform.response_delay_ms);
	EF_u8_TimerCreate(WIFI_AT_TIMER_TIMEOUT , ATMODE_TIMEOUT);
	if(device)
	{
		device->write_function = EF_Void_WIFI_WriteByte;
		device->read_function = EF_int_WIFI_WaitReadByteFromFSEQueue;
		device->delay_function = EF_Void_WIFI_delay;
		device->Data = WIFI_ATCOMMAND_IPSTART_SET;

	}

}
/****************************************************************************
 * Function    : EF_Void_WIFI_Connection_Config .
 *
 * DESCRIPTION : This FUNC config WIFI
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_WIFI_Connection_Config()
{

	/********************************Echo close************************************/

	EF_void_TimerChangeTimeOut(WIFI_AT_TIMER_TIMEOUT,WIFI_AT_COMMANDER_TIMEOUT);
	EF_void_TimerStart(WIFI_AT_TIMER_TIMEOUT);
	while(!EF_Int_WIFI_atcommander_CloseEcho_SetRequest()&& !EF_BOOLEAN_TimerCheck(WIFI_AT_TIMER_TIMEOUT));
	EF_void_TimerStop(WIFI_AT_TIMER_TIMEOUT);
	EF_void_TimerReset(WIFI_AT_TIMER_TIMEOUT);

	EF_void_TimerChangeTimeOut(WIFI_AT_TIMER_TIMEOUT,WIFI_AT_COMMANDER_TIMEOUT);
	EF_void_TimerStart(WIFI_AT_TIMER_TIMEOUT);
	while(!EF_Int_WIFI_atcommander_mode_SetRequest()&& !EF_BOOLEAN_TimerCheck(WIFI_AT_TIMER_TIMEOUT));
	EF_void_TimerStop(WIFI_AT_TIMER_TIMEOUT);
	EF_void_TimerReset(WIFI_AT_TIMER_TIMEOUT);


	while(!EF_Int_WIFI_atcommander_routerconn_SetRequest());




}
/****************************************************************************
 * Function    : EF_Int_WIFI_atcommander_IPSend_SetRequest .
 *
 * DESCRIPTION : Send data

 *
 * CmdCfg used :
 * 				GSM_ATCOMMAND_IPSEND_SET
 * 				GSM_ATCOMMAND_IPSEND_SET_RESPONSE
 *
 * PARAMETERS  : NONE.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_WIFI_atcommander_IPSend_SetRequest(unsigned char len , int timeout)
{


	int rc = sprintf((char *)WIFI_Atcommand_Config.Data
			,"AT+CIPSEND=%d\r\n" , len);

	WIFI_Atcommand_Config.size = rc;
	WIFI_Atcommand_Config.platform.response_delay_ms = timeout;

	EF_int_WIFI_FlushQueue_AT();

	return at_commander_IPSend_Request(&WIFI_Atcommand_Config);
}

/****************************************************************************
 * Function    : EF_Int_WIFI_atcommander_CloseEcho_SetRequest .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : WIFI_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 WIFI_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 WIFI_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_WIFI_atcommander_CloseEcho_SetRequest()
{
	EF_int_WIFI_FlushQueue_AT();
	WIFI_Atcommand_Config.platform.response_delay_ms = WIFI_AT_COMMANDER_DELAY;

	return at_commander_close_echo_config(&WIFI_Atcommand_Config);
}
/****************************************************************************
 * Function    : EF_Int_WIFI_atcommander_mode_SetRequest .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : WIFI_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 WIFI_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 WIFI_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_WIFI_atcommander_mode_SetRequest()
{
	EF_int_WIFI_FlushQueue_AT();
	WIFI_Atcommand_Config.platform.response_delay_ms = WIFI_AT_COMMANDER_DELAY;

	return at_commander_mode_set(&WIFI_Atcommand_Config);
}
/****************************************************************************
 * Function    : EF_Int_WIFI_atcommander_routerconn_SetRequest .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : WIFI_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 WIFI_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 WIFI_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_WIFI_atcommander_routerconn_SetRequest()
{
	EF_int_WIFI_FlushQueue_AT();
	WIFI_Atcommand_Config.platform.response_delay_ms = 1000;
	return at_commander_rounterconn_set(&WIFI_Atcommand_Config);
}
/****************************************************************************
 * Function    : EF_Int_WIFI_atcommander_dhcp_SetRequest .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : WIFI_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 WIFI_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 WIFI_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_WIFI_atcommander_dhcp_SetRequest()
{
	EF_int_WIFI_FlushQueue_AT();
	WIFI_Atcommand_Config.platform.response_delay_ms = WIFI_AT_COMMANDER_DELAY;

	return at_commander_dhcp_set(&WIFI_Atcommand_Config);
}
/****************************************************************************
 * Function    : EF_Int_WIFI_atcommander_ipstart_SetRequest .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : WIFI_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 WIFI_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 WIFI_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_WIFI_atcommander_ipstart_SetRequest()
{
	EF_int_WIFI_FlushQueue_AT();
	WIFI_Atcommand_Config.platform.response_delay_ms = WIFI_AT_COMMANDER_DELAY;

	return at_commander_IPStart_Request(&WIFI_Atcommand_Config);
}
/****************************************************************************
 * Function    : EF_void_handle_WIFI_Frame .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : WIFI_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 WIFI_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 WIFI_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/

int EF_void_WIFI_msg_received()
{

	int flag = 0;
	unsigned char incoming_arr[40];
	unsigned char data[40];
	int counter = -1;
	memset(incoming_arr ,0 , sizeof(incoming_arr));
	memset(data ,0 , sizeof(data));
	int rc = EF_int_Uart_FSEQueuereadArray_mqtt_1(incoming_arr);

	if(rc)
	{

		for(int index = 0 ; index < rc ; index ++)
		{


			if(flag == 1)
			{
				counter++;
				data[counter] = incoming_arr[index];
			}
			if(incoming_arr[index] == ':')
			{
				flag = 1;
			}
		}
	}

	EF_mqtt_FSEenqueue(data , counter+1);



	return counter+1;
}

#endif
