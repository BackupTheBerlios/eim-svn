/*
   $Id$

   Copyright (C) 2005 Jo�l Vennin < joel.vennin _@_ gmail _dot_ com >
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
