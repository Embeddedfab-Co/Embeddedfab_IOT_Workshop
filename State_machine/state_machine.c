#include "state_machine.h"


/* transitions lookup table */
transition_t state_transitions[STATE_LAST][RET_LAST] = {
    /*entry*/       	{mqttconn	,  error	,  		entry	 , error },         /* ok, fail, repeat , reset */
    /*ideal*/        	{mqttpub	,  mqttkeep	,    	mqttwait , error },         /* ok, fail, repeat , reset */
    /*mqttconn*/   		{mqttsub	,  entry	,   	mqttconn , error },   		/* ok, fail, repeat , reset */
    /*mqttpub*/     	{ideal		,  mqttconn	, 		mqttpub	 , error },       	/* ok, fail, repeat , reset */
    /*mqttsub*/     	{ideal		,  mqttconn	, 		mqttsub	 , error },   		/* ok, fail, repeat , reset */
    /*mqttkeep*/    	{ideal		,  mqttconn	, 		mqttkeep , error },   		/* ok, fail, repeat , reset */
    /*mqttwait*/    	{mqttconn	,  mqttconn	, 		ideal	 , error },   		/* ok, fail, repeat , reset */
    /*error*/    		{mqttconn	,  error	, 		error	 , error },   		/* ok, fail, repeat , reset */

};


state_codes_t lookup_transitions(state_codes_t state_codes, ret_codes_t ret_codes)
{
    switch(state_transitions[state_codes][ret_codes].dst_state){
        case    entry:
            state_codes = entry;
            break;
        case    ideal:
            state_codes = ideal;
            break;
        case    mqttconn:
            state_codes = mqttconn;
            break;
        case    mqttpub:
            state_codes = mqttpub;
            break;
        case    mqttsub:
            state_codes = mqttsub;
            break;
        case    mqttkeep:
            state_codes = mqttkeep;
            break;
        case    mqttwait:
            state_codes = mqttwait;
            break;
        case    error:
            state_codes = error;
            break;
        default:
            break;
    }

    return state_codes;
}
