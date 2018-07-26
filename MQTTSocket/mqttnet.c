/* mqttuart.c
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

/* Include the autoconf generated config.h */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "mqttnet.h"
#include "../MQTTLayer/mqtt_client_cfg.h"
#include "../main_cfg.h"


#include "../HAL/EF_GSM.h"
#include "../HAL/EF_WIFI.h"


/* TODO: Add includes for UART HW */

/* Include the example code */


/* this code is a template for using UART for communication */
#if 1

/* Local context for callbacks */
typedef struct _UartContext {
	int uartPort;

	/* TODO: Add any other context info you want */

} UartContext;

/* Private functions */
static int NetInit(void)
{

#if GSM_SIM900
	EF_void_GSM_Init();
#endif
#if WIFI_ESP
	EF_void_WIFI_Init();
#endif

	return 0;
}

static int NetConnect( const char* host, word16 port,
		int timeout_ms)
{


#if GSM_SIM900

	EF_Void_GSM_connect(host , port);
#endif
#if WIFI_ESP
	EF_Void_WIFI_connect(host , port);

#endif
	return 0;

}

static int NetWrite( const byte* buf, int buf_len,
		int timeout_ms)
{
#if GSM_SIM900

	return  (int)EF_U8_t_GSM_SendDataArray((U8_t *)buf,buf_len , timeout_ms);
#endif
#if WIFI_ESP
	return  (int)EF_U8_t_WIFI_SendDataArray((U8_t *)buf,buf_len , timeout_ms);

#endif

}

static int NetRead( byte* buf, int buf_len,
		int timeout_ms)
{
#if GSM_SIM900

	return (int )EF_Void_GSM_ReadByteFromQueue(buf , buf_len );
#endif
#if WIFI_ESP
	return (int )EF_Void_WIFI_ReadByteFromQueue(buf , buf_len );

#endif

}

static int NetDisconnect()
{
#if GSM_SIM900

	EF_Void_GSM_disconnect();
#endif
#if WIFI_ESP
	EF_Void_WIFI_disconnect();

#endif
	return 0;
}

/* Public Functions */
int MqttClientNet_Init(MqttNet* net)
{
	if (net) {
		XMEMSET(net, 0, sizeof(MqttNet));
		net->init = NetInit;
		net->connect = NetConnect;
		net->read = NetRead;
		net->write = NetWrite;
		net->disconnect = NetDisconnect;
		net->context = WOLFMQTT_MALLOC(sizeof(UartContext));
	}
	return 0;
}

int MqttClientNet_DeInit(MqttNet* net)
{
	if (net) {
		if (net->context) {
			WOLFMQTT_FREE(net->context);
		}
		XMEMSET(net, 0, sizeof(MqttNet));
	}
	return 0;
}

#endif
