/* mqttexample.h
 *
 * Copyright (C) 2006-2016 wolfSSL Inc.
 *
 * This file is part of wolfMQTT.
 *
 * wolfMQTT is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfMQTT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

#ifndef WOLFMQTT_EXAMPLE_H
#define WOLFMQTT_EXAMPLE_H

#include "mqtt_client.h"
#include "../MQTTSocket/mqttnet.h"

/* Default Configurations */
#define DEFAULT_CMD_TIMEOUT_MS  	3000
#define DEFAULT_CON_TIMEOUT_MS  	5000
#define DEFAULT_MQTT_QOS       	 	MQTT_QOS_0
#define DEFAULT_KEEP_ALIVE_SEC  	600

#define MQTT_USERNAMR 				"sXswAFtkpn"
#define MQTT_PASSWORD				"93OT3R2BS4JY96S1"

#define DEFAULT_CLIENT_ID       	"MQTT"

#define WOLFMQTT_TOPIC_NAME     	 "channels/537822/publish/fields/field3/DGAJEZCGD29CCQ6C"
#define DEFAULT_TOPIC_NAME     	 	 WOLFMQTT_TOPIC_NAME

#define SUBSCRIBE_TOPICS_NAME        "channels/537822/subscribe/fields/field2/VQL45642JQHF3WJY"
#define SUBSCRIBE_TOPICS     		 SUBSCRIBE_TOPICS_NAME

#define SUBSCRIBE_TOPICS_EX     	 3


//#define MQTT_USERNAMR 				"BBFF-f2ayu6nAdk0OPN0RI4hCER3H0myiCP"
//#define MQTT_PASSWORD				""
//
//#define DEFAULT_CLIENT_ID       	"sXswAFtkpn"
//
//#define WOLFMQTT_TOPIC_NAME     	 "/v1.6/devices/label_ds"
//#define DEFAULT_TOPIC_NAME     	 	 WOLFMQTT_TOPIC_NAME
//
//#define SUBSCRIBE_TOPICS_NAME        "/v1.6/devices/ef_switch/ef_my-switch/lv"
//#define SUBSCRIBE_TOPICS     		 SUBSCRIBE_TOPICS_NAME

#define PUBLISH_MESSAGE     	 	"50"


#define PRINT_BUFFER_SIZE       	10
#define MSG_BUFFER_SIZE	        	75
#define MAX_PACKET_ID           	((1 << 16) - 1)

#define MQTT_RECEIVE_FRAME_SERVER 	false

#if MQTT_RECEIVE_FRAME_SERVER
#define MSG_RXBUFFER_SIZE	        80
#else
#define MSG_RXBUFFER_SIZE	        40


#endif

#endif /* WOLFMQTT_EXAMPLE_H */
