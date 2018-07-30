/*
 * EF_WIFI_cfg.h
 *
 *  Created on: 2 May 2018
 *      Author: root
 */

#ifndef EF_WIFI_CFG_H_
#define EF_WIFI_CFG_H_


//#define ENTER_ATCOMMAND_CONFIG
//#define FRIST_ENTER_ATCOMMAND_CONFIG
#define WIFI_AT_COMMANDER_DEFAULT_RESPONSE_DELAY_MS 			100
#define WIFI_AT_COMMANDER_DEFAULT_RESPONSE_TIMEOUT_RETRIES 		4
#define WIFI_UART_BAUDRATE_DEFAULT 115200
#define WIFI_UART_BAUDRATE_INIT 9600
#define WIFI_MQTT_TIMER_DELAY THREE_SEC_TIMER_ID
#define WIFI_AT_TIMER_TIMEOUT TWO_MIN_TIMER_ID
#define WIFI_AT_TIMER_DELAY I2C_TIMER_ID
#define WIFI_AT_COMMANDER_DELAY  				WIFI_AT_COMMANDER_DEFAULT_RESPONSE_DELAY_MS
#define WIFI_AT_COMMANDER_TIMEOUT 			    WIFI_AT_COMMANDER_DEFAULT_RESPONSE_DELAY_MS * WIFI_AT_COMMANDER_DEFAULT_RESPONSE_TIMEOUT_RETRIES


/*********************************************************************
 * 					QUERY COMMANDS
 */
#define WIFI_ATCOMMAND_CLOSEECHO_QUERY       				"ATE0\r\n"

/*********************************************************************
 * 					RESPONED COMMANDS
 */
#define WIFI_ATCOMMAND_ECHO_RESPONSE  	 						"ATE0"
#define WIFI_ATCOMMAND_CONNECTED_RESPONSE   						"WIFI CONNECTED"
#define WIFI_ATCOMMAND_GOT_RESPONSE   							"WIFI GOT IP"
#define WIFI_ATCOMMAND_OK_RESPONSE   							"OK"
#define WIFI_ATCOMMAND_CONN_RESPONSE   							"+CWJAP"
#define WIFI_ATCOMMAND_IPSTART_SET_RESPONSE   					"CONNECT"
#define WIFI_ATCOMMAND_IPSTART_QUERY_1_RESPONSE  				"ERROR"
#define WIFI_ATCOMMAND_IPSTART_QUERY_2_RESPONSE  				"ALREADY CONNECTED"

/*********************************************************************
 * 					SET COMMANDS
 */

/*********************************************************************
 * 	MODE 		= TCP / UDP				.
 * 	IP 			= DIS IP				.
 * 	REMOTE PORT = 						. ("37.205.12.48")
 * 										  ("198.41.30.241")
 */
#define WIFI_ATCOMMAND_IPSTART_SET	\
		"AT+CIPSTART=\"TCP\",\"111.111.111.111\",1111\r\n"
/*********************************************************************
 * 	DATA 		= >
 */
#define WIFI_ATCOMMAND_IPSEND_SET	\
		"AT+CIPSEND=30\r\n"

/*********************************************************************
 * 	DATA 		= >
 */
#define WIFI_ATCOMMAND_MODE_SET	\
		"AT+CWMODE=1\r\n"
/*********************************************************************
 * 	DATA 		= >
 */
#define WIFI_ATCOMMAND_DHCP_SET	\
		"AT+CWDHCP=0,1\r\n"
/*********************************************************************
 * 	DATA 		= >
 */
#define WIFI_ATCOMMAND_ROUNTERCONN_SET	\
		"AT+CWJAP=\"EmbeddedFab\",\"Embeddedfab888\"\r\n"
/*********************************************************************
 * 	BAUDRATE = 115200	 (default).
 * 	DATABITS = 8	 	 (default).
 * 	STOPBITS = 1	 	 (default).
 * 	PARITY = NONE	 	 (default).
 * 	FLOWCONTROL = NFC	 (default).
 */
#define WIFI_ATCOMMAND_UART_SET	\
		"AT+UART=9600,8,1,0,0\r\n"

#endif /* EF_WIFI_CFG_H_ */
