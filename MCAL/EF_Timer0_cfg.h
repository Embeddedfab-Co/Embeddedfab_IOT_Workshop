 /***************************************************************
 *  Source File: EF_Timer_cfg.h
 *
 *  Description: Timer driver for ATMEGA32
 *
 *  History:     Version 1.0  - INIT Version
 *  Date   :     25/08/2014
 *  -------------------------------------------------------
 *  Author :     EmbeddedFab.
 *
 *  Copyright (C) <2014>  <EmbeddedFab>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>

 **************************************************************/

#ifndef TIMER0_CFG_H
#define TIMER0_CFG_H
#include <avr/io.h>
#include "../Utilities/std_types.h"

/**************************************************
 * Definitions
 *************************************************/
#define TIMER0_CONTROL_REG		TCCR0		/* Timer Control Register       */
#define TIMER0_REG				TCNT0		/* Timer Register     		    */
#define TOIE0_MASK				0x01		/* Timer2 Interrupt Enable mask */
#define TOV0_MASK				0x01		/* Timer2 Over Flow flag  mask  */
#define TOIE_MASK0      		TOIE0_MASK	/* Interrupt Enable bit mask    */
#define TOV_MASK0       		TOV0_MASK   /* Over Flow flag bit mask      */
#define TIMER0_OFV_VECTOR       TIMER0_OVF_vect

#define TIMER0_CLK_STOP			0x00		/* Timer Stopped			    */
#define TIMER0_CLK_DIV1			0x01		/* Timer clocked at F_CPU       */
#define TIMER0_CLK_DIV8			0x02		/* Timer clocked at F_CPU/8	    */
#define TIMER0_CLK_DIV64		0x03		/* Timer clocked at F_CPU/64    */
#define TIMER0_CLK_DIV256		0x04		/* Timer clocked at F_CPU/256   */
#define TIMER0_CLK_DIV1024		0x05		/* Timer clocked at F_CPU/1024  */

#define TIMER0_PRESCALE_MASK		0x07		/* Timer Prescaler Bit-Mask	    */


/* default prescale settings for the timer,these settings are applied
 *  when calling timerInit */

#define TIMER0PRESCALE		TIMER0_CLK_DIV1024	/* timer 1 prescaler default        */
#define TIMER0CYCLES		CYCLES0_PER_V_MLI_S	/* cycles per variable Mili seconds */
#define SYSTEMTICKTIME		20

//#define TIMER_PRESCALE		8

#if (TIMER0PRESCALE == TIMER0_CLK_DIV1)
#define TIMER0_PRESCALE		1
#elif (TIMER0PRESCALE == TIMER0_CLK_DIV8)
#define TIMER0_PRESCALE		8
#elif (TIMER0PRESCALE == TIMER0_CLK_DIV64)
#define TIMER0_PRESCALE		64
#elif (TIMER0PRESCALE == TIMER0_CLK_DIV256)
#define TIMER0_PRESCALE		256
#elif (TIMER0PRESCALE == TIMER0_CLK_DIV1024)
#define TIMER0_PRESCALE		1024
#endif

/*   Timer_Counts = ( F_timer/(F_required) ) - 1 = ( F_timer * T_required ) - 1 */
#define CYCLES0_PER_US       ((F_CPU/ TIMER0_PRESCALE )/1000000 ) 		/* system tick is 1 micro */
#define CYCLES0_PER_5_MLI_S  ((F_CPU/ TIMER0_PRESCALE )/200) 				/* system tick is 5 ms    */
#define CYCLES0_PER_10_MLI_S ((F_CPU/ TIMER0_PRESCALE )/100) 				/* system tick is 10 ms   */
#define CYCLES0_PER_20_MLI_S ((F_CPU/ TIMER0_PRESCALE )/50) 				/* system tick is 20 ms   */
#define CYCLES0_PER_V_MLI_S  ((F_CPU/ TIMER0_PRESCALE )/SYSTEMTICKTIME) 	/* system tick variable   */



#define MAX_U8_t		255			/* Max. counts of Timer 8 bit Register  */
#define MAX_U16_t		65535		/* Max. counts of Timer 16 bit Register */


#endif

