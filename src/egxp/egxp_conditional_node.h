#ifndef egxp_conditional_node_header_h_
#define egxp_conditional_node_header_h_

#include "egxp_node_struct.h"


/**
 * Initialize a conditional node.
 *  - you need to specify the parent.
 * @param parent: The "parent"
 */
Egxp_ConditionalNode * egxp_conditional_node_new (Egxp_Node * parent);



void egxp_conditional_node_free (Egxp_ConditionalNode * c);

#endif
