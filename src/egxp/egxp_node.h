#ifndef egxp_node_header_h_
#define egxp_node_header_h_

#include "egxp_node_struct.h"


/**
 * Create an initialize the structure
 * @param tag: the id of this node
 */
Egxp_Node * egxp_node_new (const unsigned int tag);


/**
 * Free the memory ...
 */
void egxp_node_free (Egxp_Node *n);


/**
 * Add the callback function to the node
 * @param begin:
 * @param end:
 */
void egxp_node_set_cb (Egxp_Node * n, egxp_callback_ptr * begin, egxp_callback_ptr * end);


/**
 * Add a node to the node
 * @param parent: the parent node
 * @param end: the child node
 */
void egxp_node_add_child_node (Egxp_Node * parent, Egxp_Node * child);


/**
 * Add a Conditional node to the node
 * @param parent: the parent node
 * @param end: the child node
 */
void egxp_node_add_conditional_node (Egxp_Node * parent, Egxp_ConditionalNode * child);


#endif
