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

#ifndef EGXP_NODE_STRUCT_H_
#define EGXP_NODE_STRUCT_H_

#include <Ecore_Data.h>

#include "egxp_message.h"

/**
 * Defines the callback types supported by egxp
 */
typedef void (*egxp_callback_ptr)(Egxp_Message *, void*);



typedef struct _Egxp_Condition Egxp_Condition;
#define EGXP_CONDITION(o) ((Egxp_Condition*)o)
struct _Egxp_Condition {
  unsigned int key; /* the id of the key */
  unsigned int value; /* the id of the value */
};


/**
 * This structure is really more simple
 */
typedef struct _Egxp_Node Egxp_Node;
#define EGXP_NODE(o) ((Egxp_Node*)o)
struct _Egxp_Node {
  /* the tag */
  int tag;
  
  /* the parent */
  Egxp_Node * parent;
  
  /* the callback */
  egxp_callback_ptr begin_cb;
  egxp_callback_ptr end_cb; 
  
  /* conditions are inside a list */
  Ecore_List * conditions;
  
  /* the child. It's a hash<tag_id, list<Egxp_NodeBase*>> */
  Ecore_Hash * childs;
};

#endif
