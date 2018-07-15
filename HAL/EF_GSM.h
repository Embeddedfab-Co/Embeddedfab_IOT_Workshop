
#ifndef EF_GSM_H_
#define EF_GSM_H_
#include "EF_GSM_cfg.h"
#include "../Utilities/std_types.h"
#include "../Utilities/atcommander/atcommander.h"

enum
{
	GSM_MQTT_FSEQUEUE = 0,
	GSM_AT_FSEQUEUE = 1
};

#define Mqtt_Sub_Read_expected_frame(Frame) "200"#Frame


/****************************************************************************
 * Function    : EF_void_GSM_Init .
 *
 * DESCRIPTION : INIT the GSM module .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_void_GSM_Init(void);
/****************************************************************************
 * Function    : EF_Void_GSM_WriteArray .
 *
 * DESCRIPTION : Send Array over GSM .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: Array length.
 ******************************************************************************/
unsigned char EF_U8_t_GSM_WriteArray(U8_t *BUFFER , U8_t Len);
/****************************************************************************
 * Function    : EF_Void_GSM_WriteByte .
 *
 * DESCRIPTION : Send byte over GSM  .
 *
 * PARAMETERS  : pointer to void UART port  : byte.
 *
 * Return Value: None.
 ******************************************************************************/

void EF_Void_GSM_WriteByte(U8_t data);
/****************************************************************************
 * Function    : EF_Void_GSM_ReadArray .
 *
 * DESCRIPTION : Receive Array over GSM .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_GSM_ReadArray(U8_t *BUFFER , U8_t Len);
/****************************************************************************
 * Function    : EF_Void_GSM_ReadByte .
 *
 * DESCRIPTION : Send byte over GSM  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_GSM_ReadByte();
/****************************************************************************
 * Function    : EF_Void_GSM_connect .
 *
 * DESCRIPTION : Send byte over GSM  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_GSM_connect(const char* host, unsigned short port);
/****************************************************************************
 * Function    : EF_Void_GSM_disconnect .
 *
 * DESCRIPTION : Send byte over GSM  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: Byte received.
 ******************************************************************************/
int EF_Void_GSM_disconnect();
/****************************************************************************
 * Function    : EF_U8_t_GSM_ReadArrayFromQueue .
 *
 * DESCRIPTION : Receive Array form ISR over GSM .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
unsigned char EF_U8_t_GSM_FSEQueuereadArray(U8_t *BUFFER );
/****************************************************************************
 * Function    : EF_int_GSM_FlushQueue_AT .
 *
 * DESCRIPTION : Receive Array form ISR over GSM .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
void EF_int_GSM_FlushQueue_AT(void);
/****************************************************************************
 * Function    : EF_int_GSM_FlushQueue_MQTT .
 *
 * DESCRIPTION : Receive Array form ISR over GSM .
 *
 * PARAMETERS  : Array.
 *
 * Return Value: Length.
 ******************************************************************************/
void EF_int_GSM_FlushQueue_MQTT(void);
/****************************************************************************
 * Function    : EF_void_GSM_FSE_mqtt_QueueUpdate .
 *
 * DESCRIPTION : Receive Array form Queue and send it to FSE .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
int  EF_void_GSM_FSE_mqtt_QueueUpdate();

/****************************************************************************
 * Function    : EF_void_GSM_FSE_at_QueueUpdate .
 *
 * DESCRIPTION : Receive Array form Queue and send it to FSE .
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
int  EF_void_GSM_FSE_at_QueueUpdate();
/****************************************************************************
 * Function    : EF_Void_GSM_ReadByteFromQueue .
 *
 * DESCRIPTION : read byte form queue over GSM  .
 *
 * PARAMETERS  : None.
 *
 * Return Value: true or false..
 ******************************************************************************/
int  EF_Void_GSM_ReadByteFromQueue(unsigned char *data , int len);

/****************************************************************************
 * Function    : EF_U8_t_GSM_SendDataArray .
 *
 * DESCRIPTION : Send data Array over GSM .
 *
 * PARAMETERS  : Array  : length.
 *
 * Return Value: Array length.
 ******************************************************************************/
int EF_U8_t_GSM_SendDataArray(U8_t *BUFFER , U8_t Len , int timeout);
/****************************************************************************
 * Function    : EF_int_GSM_WaitReadByteFromFSEQueue .
 *
 * DESCRIPTION : read byte form FSEQuee
 *
 * PARAMETERS  : None.
 *
 * Return Value: true or false.
 ******************************************************************************/
int EF_int_GSM_WaitReadByteFromFSEQueue(unsigned char *data);
/****************************************************************************
 * Function    : EF_Void_GSM_delay .
 *
 * DESCRIPTION : This Func AT Command required  .
 *
 * PARAMETERS  : delay in ms.
 *
 * Return Value: None.
 ******************************************************************************/

void EF_Void_GSM_delay(uint32_t delay_ms);
/****************************************************************************

						AT Command mode CONFIG API

		ENTER_ATCOMMAND_CONFIG should be defined in atcommander.h

 ******************************************************************************/

#if GSM_SIM900
/****************************************************************************
 * Function    : EF_Void_GSM_atcommander_init .
 *
 * DESCRIPTION : This FUNC INIT GSM for at command
 * 					you should call timer INIT and UART INIT.
 * 					before enter this function
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_GSM_atcommander_init(AtCommanderConfig *device);
/****************************************************************************
 * Function    : EF_Void_GSM_Connection_Config .
 *
 * DESCRIPTION : This FUNC config GSM
 *
 * PARAMETERS  : None.
 *
 * Return Value: None.
 ******************************************************************************/
void EF_Void_GSM_Connection_Config();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_CallReady_GetResponse .
 *
 * DESCRIPTION : Get CallReady
 * 				 INIT connected to zero .
 *
 * CmdCfg used :
 * 				GSM_ATCOMMAND_CALLREADY_DONE_RESPONED 	(\r\nCall Ready\r\n)
 *
 * PARAMETERS  : pointer to AtCommanderConfig structure.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
//int EF_Int_GSM_atcommander_CallReady_GetResponse(char * response);
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_CallReady_SetRequest .
 *
 * DESCRIPTION : Get CallReady
 *
 * CmdCfg used :
 * 				GSM_ATCOMMAND_CALLREADY_QUERY 			(AT+CCALR?\r\n)
 * 				GSM_ATCOMMAND_CALLREADY_QUERY_RESPONSE 	(+CCALR: 1)
 *
 * PARAMETERS  : NONE.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
//int EF_Int_GSM_atcommander_CallReady_SetRequest();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_CloseEcho_SetRequest .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : GSM_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 GSM_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 GSM_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_GSM_atcommander_CloseEcho_SetRequest();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_IPSendEcho_SetRequest .
 *
 * DESCRIPTION : Exit AT Command mode
 *
 * CmdCfg used : GSM_ATCOMMAND_CLOSEECHO_QUERY				(ATE0\r\n)
 * 				 GSM_ATCOMMAND_ECHO_RESPONSE	    		(ATE0)
 * 				 GSM_ATCOMMAND_OK_RESPONSE					(OK)
 *
 * PARAMETERS  : AtCommanderConfig structure to at command parameters
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_GSM_atcommander_IPSendEcho_SetRequest();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_SimConncetion_GetResponse .
 *
 * DESCRIPTION : Get SIM connection
 * 				 INIT connected to zero .
 *
 * CmdCfg used :
 * 				GSM_ATCOMMAND_SIM_READY_RESPONSE 			(+CPIN: READY)
 * 				GSM_ATCOMMAND_SIM_NOT_INSERTED_RESPONSE 	(+CPIN: NOT INSERTED)
 *
 * PARAMETERS  : pointer to response.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
//int EF_Int_GSM_atcommander_SimConncetion_GetResponse(char * response);
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_SimConncetion_SetRequest .
 *
 * DESCRIPTION : Get SIM connection
 * 				 INIT connected to zero .
 *
 * CmdCfg used :
 * 				GSM_ATCOMMAND_SIMCONNECTION_QUERY 			(AT+CPIN?\r\n)
 * 				GSM_ATCOMMAND_SIM_READY_QUERY_RESPONSE	 	(+CPIN: READY)
 *
 * PARAMETERS  : NONE.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_GSM_atcommander_SimConncetion_SetRequest();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_IPStart_SetRequest .
 *
 * DESCRIPTION : open socket with server

 *
 * CmdCfg used :
 * 				GSM_ATCOMMAND_IPSTART_SET
 * 				GSM_ATCOMMAND_IPSTART_SET_RESPONSE
 *
 * PARAMETERS  : NONE.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_GSM_atcommander_IPStart_SetRequest();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_IPSend_SetRequest .
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
int EF_Int_GSM_atcommander_IPSend_SetRequest(unsigned char len);
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_IPClose_SetRequest .
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
int EF_Int_GSM_atcommander_IPClose_SetRequest();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_IPSend_getResponse .
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
//int EF_Int_GSM_atcommander_IPSend_GetResponse();
/****************************************************************************
 * Function    : EF_Int_GSM_atcommander_SIMInternet_SetRequest .
 *
 * DESCRIPTION : check internet connection .
 *
 * CmdCfg used :
 * 				GSM_ATCOMMAND_SIMINTERNET_QUERY
 * 				GSM_ATCOMMAND_SIMINTERNET_QUERY_RESPONSE
 *
 * PARAMETERS  : NONE.
 *
 * Return Value: true if command sent false if not.
 ******************************************************************************/
int EF_Int_GSM_atcommander_SIMInternet_SetRequest();

int EF_Int_Mqtt_read(int *size);


#endif



#endif /* EF_GSM_H_ */
