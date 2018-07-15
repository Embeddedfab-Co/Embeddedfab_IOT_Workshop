/*
 * App.h
 *
 *  Created on: Mar 13, 2018
 *      Author: root
 */

#ifndef APP_H_
#define APP_H_
#include "main_cfg.h"

#include "MCAL/EF_UART.h"

#include "MQTTLayer/mqtt_client_cfg.h"
#include "avr/io.h"
#include "ServiceLayer/EF_ArrayCompare.h"
#include "util/delay.h"
#include "string.h"
#include "ServiceLayer/FSE_CircularBuffer_v2/FSE_CircularBuffer_v2.h"
#include "ServiceLayer/FSE_CircularBuffer/FSE_CircularBuffer.h"
#include "avr/wdt.h"
#include "MCAL/EF_Timer0.h"

#if NRF_24
#include "HAL/nrf24l01.h"
#include "HAL/nrf24l01registers.h"
#endif


#if	(GSM_SIM900 == true)
#include "HAL/EF_GSM.h"
#endif




#endif /* APP_H_ */
