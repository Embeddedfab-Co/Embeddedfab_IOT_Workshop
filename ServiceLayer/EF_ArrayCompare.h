/*
 * EF_Sort.h
 *
 *  Created on: Mar 4, 2018
 *      Author: root
 */

#ifndef EF_SORT_H_
#define EF_SORT_H_
#include "../Utilities/std_types.h"


typedef struct
{
	U8_t *IncomingArr;
	U8_t *ComparingArr;
	U8_t *StartingArr;
	U8_t *expectedArr;
	U8_t Startinglenght;
	U8_t expectedlenght;
	U8_t Timeout;
}Arr_Compare_Start_Until_cfg;

BOOLEAN EF_ArryCompare(	U8_t *IncomingArr , U8_t *ComparingArr , U8_t Arr_lenght);
BOOLEAN EF_ArryCompareUntil(U8_t *IncomingArr , U8_t *ComparingArr , U8_t *expectedArr ,U8_t expectedlenght , U8_t Timeout);
BOOLEAN EF_ArryCompareStartUntil(Arr_Compare_Start_Until_cfg *ArrayCmpStUn);
BOOLEAN EF_BOOLEAN_ArrySearch(unsigned char *IncomingArr , unsigned char *SearchArr , unsigned int len);

#endif /* EF_SORT_H_ */
