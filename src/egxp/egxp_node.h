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

/****************************************************************/
/****************************************************************/
/****************************************************************/
Egxp_Node * egxp_node_new (const int tag);

void egxp_node_free (Egxp_Node * n);

void egxp_node_set_cb (Egxp_Node * n, egxp_callback_ptr * begin, egxp_callback_ptr * end);


void egxp_node_add_condition (Egxp_Node* cn, Egxp_Condition * cond);


void egxp_node_add_child (Egxp_Node * parent, Egxp_Node * child);

#endif
