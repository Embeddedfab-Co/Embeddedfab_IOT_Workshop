/*
 * FSE_CircularBuffer.h
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */

#ifndef SERVICELAYER_FSE_CIRCULARBUFFER_FSE_CIRCULARBUFFER_H_
#define SERVICELAYER_FSE_CIRCULARBUFFER_FSE_CIRCULARBUFFER_H_



#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "../../MQTTLayer/mqtt_client_cfg.h"

#define FSE_CB_BUFFER_SIZE 2

#if MQTT_RECEIVE_FRAME_SERVER
#define ELEMENT_SIZE 80
#else
#define ELEMENT_SIZE 40
#endif

typedef struct FSE_CircularBuffer FSE_CircularBuffer;

struct FSE_CircularBuffer{

	uint8_t buffer[FSE_CB_BUFFER_SIZE][ELEMENT_SIZE];
	uint8_t elementSize[FSE_CB_BUFFER_SIZE];
	uint8_t head;
	uint8_t size;
	uint8_t tail;
	bool (*isFull)(FSE_CircularBuffer * const me);
	bool (*isEmpty)(FSE_CircularBuffer * const me);
	uint8_t (*getSize)(FSE_CircularBuffer * const me);
	void (*enqueue)(FSE_CircularBuffer * const me, uint8_t * pvalue, uint8_t len);
	void (*dequeue)(FSE_CircularBuffer * const me, uint8_t * pvalue, uint8_t * len);
	void (*peek)(FSE_CircularBuffer * const me, uint8_t *pvalue, uint8_t * len);
};

void FSE_CircularBuffer_ctor(FSE_CircularBuffer * const me);



#endif /* SERVICELAYER_FSE_CIRCULARBUFFER_FSE_CIRCULARBUFFER_H_ */
