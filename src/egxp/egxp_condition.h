#ifndef egxp_condition_header_h_
#define egxp_condition_header_h_

#include "egxp_node_struct.h"

/**
 * Create a egxp condition structure initialized with it parameters
 * @param key: the id of the key
 * @param value: the id of the value
 */
Egxp_Condition * egxp_condition_new (const unsigned int key, const unsigned int value); 

/**
 * Free the memory of the condition
 */
void egxp_condition_free (Egxp_Condition * condition);

/**
 * Test if the EgxpCondition is equal to the id and the value
 */
unsigned char egxp_condition_equals (Egxp_Condition * condition, const unsigned int key, const unsigned int value);

 
#endif
