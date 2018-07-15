/*
 * main_cfg.h
 *
 *  Created on: Apr 1, 2018
 *      Author: root
 */

#ifndef MAIN_CFG_H_
#define MAIN_CFG_H_

#include "Utilities/EF_SpechialTIMER.h"

#define GSM_SIM900 						true

#define NRF_24                  		true
#define MQTTCLIENT                 	 	true

#define MQTT_AT_DELAY					400

#define MQTT_CON_DELAY					100
#define MQTT_PUB_DELAY					4000000
#define MQTT_KEEPALIVE_DELAY			5000
#define MQTT_LED_DELAY					3

#define EMBEDDEDFAB_IP					"104.196.119.142"
#define ECLIPSE_IP						"198.41.30.241"
#define UBIDOTS_IP						"50.23.124.68"
#define THINGSPEAK_IP					"52.45.80.142"

#define SERVER_IP						THINGSPEAK_IP

#define EMBEDDEDFAB_PORT				1885
#define ECLIPSE_PORT					1883
#define UBIDOTS_PORT					1883
#define THINGSPEAK_PORT					1883

#define SERVER_PORT						UBIDOTS_PORT

#define WATING_MQTT_MSG_TIMER_ID 		INPUT_CAPTURE_ID


#define RF_CHNL_1          				76
#define RF_CHNL_2          				92
#define RF_CHNL_3         	 			113
//role button/pin
#define LEDOUTPAUSE       				1000
/* Receiver Scan */
#define CHNL_SCN_ID		  				CHNL_ID



#endif /* MAIN_CFG_H_ */
