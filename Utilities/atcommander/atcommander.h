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

#define AT_COMMANDER_MAX_REQUEST_LENGTH 128
#define AT_COMMANDER_RETRY_DELAY_MS 	100
#define AT_COMMANDER_MAX_RESPONSE_LENGTH 25
#define AT_COMMANDER_MAX_RETRIES		 4


//#if (GSM_SIM900 == true)
//#define EF_ATCOMMADER_GSM_SIM900
//#endif



typedef struct {
	int response_delay_ms;
}AtCommanderPlatform;



typedef struct {
	AtCommanderPlatform platform;
//	void (*baud_rate_initializer)(uint8_t *uart_cfg);
	void (*write_function)( uint8_t);
	int (*read_function)(unsigned char *buf);
	void (*delay_function)(uint32_t);
//	void (*log_function)(const char *, ...);

	int connected;
	int size;
	char* Data;
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

#if WIFI_ESP
int at_commander_IPStart_Request(AtCommanderConfig* config);
int at_commander_close_echo_config(AtCommanderConfig* config);
int atcommander_set_UART(AtCommanderConfig* config);
int at_commander_mode_set(AtCommanderConfig* config);
int at_commander_rounterconn_set(AtCommanderConfig* config);
int at_commander_dhcp_set(AtCommanderConfig* config);
int at_commander_IPSend_Request(AtCommanderConfig* config);

#endif

#endif /* _ATCOMMANDER_H_ */
