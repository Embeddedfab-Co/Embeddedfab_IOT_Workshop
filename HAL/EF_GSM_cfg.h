

#ifndef EF_GSM_CFG_H_
#define EF_GSM_CFG_H_

//#define ENTER_ATCOMMAND_CONFIG
//#define FRIST_ENTER_ATCOMMAND_CONFIG
#define AT_COMMANDER_DEFAULT_RESPONSE_DELAY_MS 100
#define GSM_UART_BAUDRATE_DEFAULT 115200
#define GSM_UART_BAUDRATE_INIT 9600
#define GSM_MQTT_TIMER_DELAY THREE_SEC_TIMER_ID
#define GSM_AT_TIMER_TIMEOUT TWO_MIN_TIMER_ID
#define GSM_AT_TIMER_DELAY I2C_TIMER_ID

/*********************************************************************
 * 					QUERY COMMANDS
 */
#define GSM_ATCOMMAND_CLOSEECHO_QUERY       			"ATE0\r\n"
#define GSM_ATCOMMAND_CALLREADY_QUERY   				"AT+CCALR?\r\n"
#define GSM_ATCOMMAND_SIMCONNECTION_QUERY   			"AT+CPIN?\r\n"
#define GSM_ATCOMMAND_IPCLOSE_QUERY   					"AT+CIPCLOSE\r\n"
#define GSM_ATCOMMAND_SIMINTERNET_QUERY					"AT+CGATT?\r\n"

/*********************************************************************
 * 					RESPONED COMMANDS
 */
#define GSM_ATCOMMAND_OK_RESPONSE   							"OK"

#define GSM_ATCOMMAND_ECHO_RESPONSE  	 						"ATE0"
#define GSM_ATCOMMAND_CALLREADY_QUERY_RESPONSE   				"+CCALR: 1"
#define GSM_ATCOMMAND_SIM_READY_RESPONSE   						"+CPIN: READY"
#define GSM_ATCOMMAND_SIM_READY_QUERY_RESPONSE   				"+CPIN: READY"
#define GSM_ATCOMMAND_SIMINTERNET_QUERY_RESPONSE   				"+CGATT: 1"
#define GSM_ATCOMMAND_IPSTART_SET_RESPONSE   					"CONNECT OK"
#define GSM_ATCOMMAND_IPSTART_QUERY_1_RESPONSE  				"ERROR"
#define GSM_ATCOMMAND_IPSTART_QUERY_2_RESPONSE  				"ALREADY CONNECT"
#define GSM_ATCOMMAND_IPSEND_SET_RESPONSE   					">"
#define GSM_ATCOMMAND_IPCLOSE_SET_RESPONSE   					"CLOSE OK"
#define GSM_ATCOMMAND_POWERDOWN_SET_RESPONSE   					"NORMAL"

/*********************************************************************
 * 					SET COMMANDS
 */

/*********************************************************************
 * 	MODE 		= TCP / UDP				.
 * 	IP 			= DIS IP				.
 * 	REMOTE PORT = 						. ("37.205.12.48")
 * 										  ("198.41.30.241")
 */
#define GSM_ATCOMMAND_IPSTART_SET	\
		"AT+CIPSTART=\"TCP\",\"111.111.111.111\",1111\r\n"
/*********************************************************************
 * 	DATA 		= >
 */
#define GSM_ATCOMMAND_IPSEND_SET	\
		"AT+CIPSEND=30\r\n"

/*********************************************************************
 * 	DATA 		= >
 */
#define GSM_ATCOMMAND_IPSENDECHO_SET	\
		"AT+CIPSPRT=2\r\n"

#endif
