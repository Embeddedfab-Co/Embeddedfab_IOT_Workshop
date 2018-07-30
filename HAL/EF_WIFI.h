/*
 * EF_WIFI.h
 *
 *  Created on: 2 May 2018
 *      Author: root
 */

#ifndef EF_WIFI_H_
#define EF_WIFI_H_
#include "EF_WIFI_cfg.h"
#include "../Utilities/std_types.h"
#include "../Utilities/atcommander/atcommander.h"

#if WIFI_ESP

enum
{
	WIFI_MQTT_FSEQUEUE = 0,
	WIFI_AT_FSEQUEUE = 1
};



/****************************************************************************
 * Function    : EF_void_WIFI_Init .
 *
 * DESCRIPTION : INIT the WIFI module .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_void_WIFI_Init(void);
/****************************************************************************
 * Function    : EF_Void_WIFI_WriteArray .
 *
 * DESCRIPTION : Send Array over WIFI .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: Array length.
 ******************************************************************************/
unsigned char EF_U8_t_WIFI_WriteArray(U8_t *BUFFER , U8_t Len);
/****************************************************************************
 * Function    : EF_Void_WIFI_WriteByte .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : pointer to void UART port  : byte.
 *
 * Return Value: None.
 ******************************************************************************/

void EF_Void_WIFI_WriteByte(U8_t data);
/****************************************************************************
 * Function    : EF_Void_WIFI_ReadArray .
 *
 * DESCRIPTION : Receive Array over WIFI .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_WIFI_ReadArray(U8_t *BUFFER , U8_t Len);
/****************************************************************************
 * Function    : EF_Void_WIFI_ReadByte .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_WIFI_ReadByte();
/****************************************************************************
 * Function    : EF_Void_WIFI_connect .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_WIFI_connect(const char* host, unsigned short port);
/****************************************************************************
 * Function    : EF_Void_WIFI_disconnect .
 *
 * DESCRIPTION : Send byte over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_WIFI_disconnect();
/****************************************************************************
 * Function    : EF_U8_t_WIFI_ReadArrayFromQueue .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
unsigned char EF_U8_t_WIFI_FSEQueuereadArray(U8_t *BUFFER );
/****************************************************************************
 * Function    : EF_int_WIFI_FlushQueue_AT .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
void EF_int_WIFI_FlushQueue_AT(void);
/****************************************************************************
 * Function    : EF_int_WIFI_FlushQueue_MQTT .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
void EF_int_WIFI_FlushQueue_MQTT(void);
/****************************************************************************
 * Function    : EF_U8_t_WIFI_ReadArrayFromQueueLen .
 *
 * DESCRIPTION : Receive Array form ISR over WIFI .
 *
 * PARAMETERS  : Array , len.
 *
 * Return Value: Length.
 ******************************************************************************/
unsigned char EF_U8_t_WIFI_FSEQueuereadByte(U8_t *BUFFER , unsigned char length );

/****************************************************************************
 * Function    : EF_void_WIFI_FSE_at_QueueUpdate .
 *
 * DESCRIPTION : Receive Array form Queue and send it to FSE .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
int  EF_void_WIFI_FSE_at_QueueUpdate();
/****************************************************************************
 * Function    : EF_void_WIFI_FSE_mqtt_QueueUpdate .
 *
 * DESCRIPTION : Receive Array form Queue and send it to FSE .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
int  EF_void_WIFI_FSE_mqtt_QueueUpdate();
/****************************************************************************
 * Function    : EF_Void_WIFI_ReadByteFromQueue .
 *
 * DESCRIPTION : read byte form queue over WIFI  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: true or false..
 ******************************************************************************/
int  EF_Void_WIFI_ReadByteFromQueue(unsigned char *data , int len);

/****************************************************************************
 * Function    : EF_U8_t_WIFI_SendDataArray .
 *
 * DESCRIPTION : Send data Array over WIFI .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: Array length.
 ******************************************************************************/
int EF_U8_t_WIFI_SendDataArray(U8_t *BUFFER , U8_t Len , int timeout);
/****************************************************************************
 * Function    : EF_int_WIFI_WaitReadByteFromFSEQueue .
 *
 * DESCRIPTION : read byte form FSEQuee
 *
 * PARAMETERS  : None.
 *
 * Return Value: true or false.
 ******************************************************************************/
int EF_int_WIFI_WaitReadByteFromFSEQueue(unsigned char *data);
/****************************************************************************
 * Function    : EF_Void_WIFI_delay .
 *
 * DESCRIPTION : This Func AT Command required  .
 *
 * PARAMETERS  : delay in ms.
 *
 * Return Value: None.
 ******************************************************************************/

void EF_Void_WIFI_delay(uint32_t delay_ms);
/****************************************************************************

						AT Command mode CONFIG API

		ENTER_ATCOMMAND_CONFIG should be defined in atcommander.h

 ******************************************************************************/

/****************************************************************************
 * Function    : EF_Void_WIFI_atcommander_ConfigATmodeUart .
 *
 * DESCRIPTION : Set baud rate for Ethernet module at first time
 *
 * PARAMETERS  : NONE.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Void_WIFI_atcommander_ConfigATmodeUart();
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
int EF_Int_WIFI_atcommander_CloseEcho_SetRequest();

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
void EF_Void_WIFI_atcommander_init(AtCommanderConfig *device);
/****************************************************************************
 * Function    : EF_Void_WIFI_Connection_Config .
 *
 * DESCRIPTION : This FUNC config WIFI
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_WIFI_Connection_Config();
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
int EF_Int_WIFI_atcommander_IPSend_SetRequest(unsigned char len , int timeout);
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
int EF_Int_WIFI_atcommander_mode_SetRequest();
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
int EF_Int_WIFI_atcommander_routerconn_SetRequest();
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
int EF_Int_WIFI_atcommander_dhcp_SetRequest();
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
int EF_Int_WIFI_atcommander_ipstart_SetRequest();
/****************************************************************************
 * Function    : EF_void_WIFI_msg_received .
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
int EF_void_WIFI_msg_received();

int EF_Int_Mqtt_read(int *size);


#endif



#endif /* EF_WIFI_H_ */
