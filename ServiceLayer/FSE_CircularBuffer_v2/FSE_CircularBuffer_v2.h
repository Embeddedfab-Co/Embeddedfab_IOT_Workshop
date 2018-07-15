/*
 * FSE_CircularBuffer_v2.h
 *
 *  Created on: Aug 21, 2017
 *      Author: root
 */

#ifndef SERVICELAYER_FSE_CircularBuffer_v2_FSE_CircularBuffer_v2_H_
#define SERVICELAYER_FSE_CircularBuffer_v2_FSE_CircularBuffer_v2_H_



#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define FSE_CB_BUFFER_SIZE_V2 	7
#define ELEMENT_SIZE_V2			7

typedef struct FSE_CircularBuffer_v2 FSE_CircularBuffer_v2;

struct FSE_CircularBuffer_v2{

	uint8_t buffer[FSE_CB_BUFFER_SIZE_V2][ELEMENT_SIZE_V2];
	uint8_t elementSize[FSE_CB_BUFFER_SIZE_V2];
	uint8_t head;
	uint8_t size;
	uint8_t tail;
	bool (*isFull)(FSE_CircularBuffer_v2 * const me);
	bool (*isEmpty)(FSE_CircularBuffer_v2 * const me);
	uint8_t (*getSize)(FSE_CircularBuffer_v2 * const me);
	void (*enqueue)(FSE_CircularBuffer_v2 * const me, uint8_t * pvalue, uint8_t len);
	void (*dequeue)(FSE_CircularBuffer_v2 * const me, uint8_t * pvalue, uint8_t * len);
	void (*peek)(FSE_CircularBuffer_v2 * const me, uint8_t *pvalue, uint8_t * len);
};

void FSE_CircularBuffer_v2_ctor(FSE_CircularBuffer_v2 * const me);



#endif /* SERVICELAYER_FSE_CircularBuffer_v2_FSE_CircularBuffer_v2_H_ */
