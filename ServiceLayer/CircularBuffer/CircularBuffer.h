/*
 * CircularBuffer.h
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */

#ifndef SERVICELAYER_CIRCULARBUFFER_CIRCULARBUFFER_H_
#define SERVICELAYER_CIRCULARBUFFER_CIRCULARBUFFER_H_


#include <stdint.h>
#include <stdbool.h>
#include "../../MQTTLayer/mqtt_client_cfg.h"

#if MQTT_RECEIVE_FRAME_SERVER
#define CB_BUFFER_SIZE 40
#else
#define CB_BUFFER_SIZE 40
#endif


typedef struct CircularBuffer CircularBuffer;

struct CircularBuffer{

	uint8_t buffer[CB_BUFFER_SIZE];
	int head;
	int size;
	int tail;
	bool (*isFull)(CircularBuffer * const me);
	bool (*isEmpty)(CircularBuffer * const me);
	int (*getSize)(CircularBuffer * const me);
	void (*enqueue)(CircularBuffer * const me, uint8_t value);
	void (*dequeue)(CircularBuffer * const me, uint8_t * pvalue);
};

void CircularBuffer_ctor(CircularBuffer * const me);

#endif /* SERVICELAYER_CIRCULARBUFFER_CIRCULARBUFFER_H_ */
