/*
 * EF_SleepMode_cfg.h
 *
 *  Created on: Feb 25, 2018
 *      Author: root
 */

#ifndef EF_SLEEPMODE_CFG_H_
#define EF_SLEEPMODE_CFG_H_

//#define POWERDOWN_SLEEPMODE
//#define POWERSAVE_SLEEPMODE
#define IDLE_SLEEPMODE
//#define ADC_NOISE_REDUCTION_SLEEPMODE
//#define STANDBY_SLEEPMODE
//#define EXTENDEDSTANDBY_SLEEPMODE

typedef struct SleepMode
{
	unsigned char Mode ;
	unsigned char Wakeup_device ;
	struct{
		unsigned int HH ;                 //every count = 14ms
		unsigned int MM ;                 //every count = 14ms
		unsigned int SS ;                 //every count = 14ms

	}Time;
}Sleep_Mode_cfg;


#endif /* EF_SLEEPMODE_CFG_H_ */
