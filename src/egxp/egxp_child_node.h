#ifndef egxp_childnode_header_h_
#define egxp_childnode_header_h_

#include "egxp_node_struct.h"

/**
 * Create an initialize a new child node
 */
Egxp_ChildNode * egxp_child_node_new ();


/**
 * Free a child node
 */
void egxp_child_node_free (Egxp_ChildNode * cn);


/**
 * Add a node to the child node.
 *  - if the hash map is not allocated we initialize it.
 * @param cn: the child node
 * @param c: the node to add in the hash list
 */
void egxp_child_node_add_node (Egxp_ChildNode * cn, Egxp_Node * c);


#endif
