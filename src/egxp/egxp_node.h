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
#ifndef egxp_node_header_h_
#define egxp_node_header_h_

#include "egxp_node_struct.h"
#include "egxp_opcode.h"
/****************************************************************/
/****************************************************************/
/****************************************************************/

/**
 * Create a new node.
 * @param tag: The tag id for this node
 * @return: the newly created node
 */
Egxp_Node * egxp_node_new (const int tag);


/**
 * Free a node
 * @param n: Deallocate the memory used by the node
 */
void egxp_node_free (Egxp_Node * n);


/**
 * Set the callback to the node.
 * This callback are called when the node is processed by the protocol handler.
 * @param n: the node
 * @param begin: The begin callback
 * @param end: the end callback
 */
void egxp_node_set_cb (Egxp_Node * n, egxp_callback_ptr begin, egxp_callback_ptr end);


/**
 * Add condition to this node.
 * @param cn: The node
 * @param cond: The condition to add
 */
void egxp_node_add_condition (Egxp_Node* cn, Egxp_Condition * cond);


/**
 * Add a child to the node
 * @param parent: The parent node
 * @param child: The child to add to the parent
 */
void egxp_node_add_child (Egxp_Node * parent, Egxp_Node * child);


/**
 * Get a child with the same id as the parameter id.
 * If there is no child it return null, otherwise return the last
 * child of the list.
 * @return a child or null.
 */
Egxp_Node * egxp_node_get_child (Egxp_Node * node, int id);


/**
 * Display to standard output the contains of the Egxp Node sturcture
 */
void egxp_node_print (Egxp_Node * n, Egxp_Opcode * op);

#endif
