/*
   $Id$

   Copyright (C) 2005 Joël Vennin < joel.vennin _@_ gmail _dot_ com >
   Part of the Eim Project http://eim.berlios.de

   Eim is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   Eim is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Eim; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef egxp_conditional_node_header_h_
#define egxp_conditional_node_header_h_

#include "egxp_node_struct.h"


/**
 * Initialize a conditional node.
 *  - you need to specify the parent.
 * @param parent: The "parent"
 */
Egxp_ConditionalNode * egxp_conditional_node_new (Egxp_Node * parent);

Egxp_ConditionalNode * egxp_conditional_node_new_with_condition (Egxp_Node * parent, Egxp_Condition * cond);


/**
 * Free the memory of the ConditionalNode Structure
 */
void egxp_conditional_node_free (Egxp_ConditionalNode * c);


/**
 * Add a condition to the condition list
 * - If the condition list is not created, we create it.
 * @param cn: the conditional node
 * @param cond: the condition to add
 */
void egxp_conditional_node_add_condition (Egxp_ConditionalNode * cn, Egxp_Condition * cond);


/**
 * Add the callback function to the node
 * @param begin:
 * @param end:
 */
void egxp_conditional_node_set_cb (Egxp_ConditionalNode * n, egxp_callback_ptr * begin, egxp_callback_ptr * end);


/**
 * Add a node to the node
 * @param parent: the parent node
 * @param end: the child node
 */
void egxp_conditional_node_add_child_node (Egxp_ConditionalNode * parent, Egxp_Node * child);

#endif
