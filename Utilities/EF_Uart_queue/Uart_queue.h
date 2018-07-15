/*
 * mqtt_queue.h
 *
 *  Created on: Mar 13, 2018
 *      Author: root
 */

#ifndef MQTT_QUEUE_H_
#define MQTT_QUEUE_H_
#include "../../ServiceLayer/CircularBuffer/CircularBuffer.h"
#include "../../ServiceLayer/FSE_CircularBuffer/FSE_CircularBuffer.h"

#define MQTTSTOPBYTE2ND 0x0A
#define MQTTSTOPBYTE1ST 0x0D
#define GSMSTARTBYTE 0xFF
#define MQTTBUFFERSIZE CB_BUFFER_SIZE
#define MQTT_TIMEOUT_ID MILLIS_200_TIMER_ID


enum
{
	UART_MQTT_FSEQUEUE = 0,
	UART_AT_FSEQUEUE = 1
};

enum
{
	UART_F_QUEUE = 0,
	UART_S_QUEUE = 1,
	UART_T_QUEUE = 2,
	UART_E_QUEUE = 3
};

enum
{
	FRAME_BEGIN 	= 0,
	FRAME_END	 	= 1
};

void EF_void_Uart_Queue_Init();
void EF_void_UartQueueUpdate();
int EF_void_UartFSE_at_QueueUpdate(void );
int EF_void_UartFSE_mqtt_QueueUpdate(void );
uint8_t EF_int_Uart_FSEQueuereadArray(unsigned char *data );
uint8_t EF_int_Uart_FSEQueuereadArray_mqtt(unsigned char *data );

void EF_int_Uart_ClearFSQQueue_AT();
void EF_int_Uart_ClearFSQQueue_MQTT();

uint8_t EF_uint8_t_Uart_FSEQueuereadByte(unsigned char *data ,int len);
//uint8_t EF_uint8_t_Uart_WaitFSEQueuereadByte(unsigned char *data ,unsigned char len);

#endif /* MQTT_QUEUE_H_ */
