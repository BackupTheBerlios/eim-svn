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
