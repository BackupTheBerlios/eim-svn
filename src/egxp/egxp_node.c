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
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <Ecore_Data.h>

#include "egxp_child_node.h"
#include "egxp_conditional_node.h"
#include "egxp_node.h"

Egxp_Node * egxp_node_new (const unsigned int tag) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_new\n");
#endif 

  Egxp_Node * tmp = EGXP_NODE(malloc(sizeof(Egxp_Node)));
  
  tmp->tag = tag;
  
  tmp->child = NULL;
  tmp->conditions = NULL;
  
  return tmp;
}


void egxp_node_free (Egxp_Node *n) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_free\n");
#endif 

  assert (n);
  
  if (n->child) egxp_child_node_free (n->child);
  if (n->conditions) ecore_list_destroy (n->conditions);
  free (n);
}


void egxp_node_set_cb (Egxp_Node * n, egxp_callback_ptr * begin, egxp_callback_ptr * end) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_set_callback\n");
#endif 

  assert (n);
  
  /* check if the child node is created */
  if (n->child == NULL) n->child = egxp_child_node_new ();
  
  /* set the attributes */
  n->child->begin_func = begin;
  n->child->end_func = end;
}


void egxp_node_add_child_node (Egxp_Node * parent, Egxp_Node * child) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_add_child_node\n");
#endif
  assert (parent && child);

  /* check if the child node is created */
  if (parent->child == NULL) parent->child = egxp_child_node_new ();

  /* add the node to the child element */
  egxp_child_node_add_node (parent->child, child);  
}


void egxp_node_add_conditional_node (Egxp_Node * parent, Egxp_ConditionalNode * child) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_add_conditional_node\n");
#endif
  assert (parent && child);

  if (parent->conditions == NULL) {
    parent->conditions = ecore_list_new ();
    ecore_list_set_free_cb (parent->conditions, egxp_conditional_node_free);
  }
  
  ecore_list_append (parent->conditions, child);
}
