
#ifndef EF_SLEEPMODE_POWERSAVE_H_
#define EF_SLEEPMODE_POWERSAVE_H_
#include "EF_SpechialTIMER.h"
#include "EF_SleepMode_cfg.h"


enum
{
	INT,
	TWI,
	TIMER,
	WDT,
	ADc
};

enum
{
	IDLE,
	ADC_NOISE_REDUCTION,
	PWR_DOWN,
	PWR_SAVE,
	STANDBY,
	EXTENDED_STANDBY
};
void EF_void_SleepMode_Init(Sleep_Mode_cfg Sleepmode);
void EF_void_SleepMode_Wakeup_Timer();
void EF_void_SleepMode_Wakeup_INT(void);
void EF_void_SleepMode_Wakeup_TWI();
void EF_void_SleepMode_Wakeup_WDT();
void EF_void_SleepMode_Wakeup_ADC();



#endif /* EF_SLEEPMODE_POWERSAVE_H_ */
