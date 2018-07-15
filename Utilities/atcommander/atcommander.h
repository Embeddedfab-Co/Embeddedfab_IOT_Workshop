/*
 *
 *  atcommander.h
 *
 */

#ifndef _ATCOMMANDER_H_
#define _ATCOMMANDER_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include "../../main_cfg.h"




#if (GSM_SIM900 == true)
#define EF_ATCOMMADER_GSM_SIM900
#endif

typedef struct {


#if GSM_SIM900
	char* request_format;
	char* expected_response;
#endif


}AtCommand;


typedef struct {
	int response_delay_ms;

#if GSM_SIM900
	AtCommand set_closeecho_command;
	AtCommand get_ok_command;
	AtCommand set_simconncetion_command;
	AtCommand set_ipstart_command;
	AtCommand set_ipsend_command;
	AtCommand set_ipclose_command;
	AtCommand set_siminternet_command;
	AtCommand get_ipstart_1_command;
	AtCommand get_ipstart_2_command;
	AtCommand set_ipsendecho_command;
	AtCommand set_powerdown_command;
	AtCommand set_ipmux_command;


#endif


}AtCommanderPlatform;



typedef struct {
	AtCommanderPlatform platform;
//	void (*baud_rate_initializer)(uint8_t *uart_cfg);
	void (*write_function)( uint8_t);
	int (*read_function)(unsigned char *buf);
	void (*delay_function)(uint32_t);
//	void (*log_function)(const char *, ...);

	int connected;
//	unsigned long baud;
//	int device_baud;
//	void* device;
}AtCommanderConfig;





#if GSM_SIM900

//int at_commander_CallReady_Response(AtCommanderConfig* config,char * response);
//int at_commander_CallReady_Request(AtCommanderConfig* config);
//int at_commander_SIMConnection_Response(AtCommanderConfig* config,char * response);
int at_commander_SIMConnection_Request(AtCommanderConfig* config);
int at_commander_IPStart_Request(AtCommanderConfig* config);
int at_commander_IPClose_Request(AtCommanderConfig* config);
int at_commander_IPSendEcho_Request(AtCommanderConfig* config);
int at_commander_IPSend_Request(AtCommanderConfig* config);
//int at_commander_IPSend_Response(AtCommanderConfig* config);
int at_commander_SIMInternet_Request(AtCommanderConfig* config);
int at_commander_close_echo_config(AtCommanderConfig* config);

#endif

#endif /* _ATCOMMANDER_H_ */
