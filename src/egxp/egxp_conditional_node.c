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
#include <Ecore_Data.h>

#include "egxp_child_node.h"
#include "egxp_node.h"
#include "egxp_conditional_node.h"

Egxp_ConditionalNode * egxp_conditional_node_new (Egxp_Node * parent) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_new\n");
#endif
  assert (parent);
  
  /* create and initialize the structure */
  Egxp_ConditionalNode * tmp = EGXP_CONDITIONALNODE(malloc (sizeof(Egxp_ConditionalNode)));
  tmp->parent = parent;
  tmp->conditions = NULL;
  tmp->child = NULL;
  
  /* add this conditional node to the parent */
  egxp_node_add_conditional_node (tmp->parent, tmp);
  

  return tmp;
}


Egxp_ConditionalNode * egxp_conditional_node_new_with_condition (Egxp_Node * parent, Egxp_Condition * cond) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_new_with_condition\n");
#endif
  assert(parent && cond);

  Egxp_ConditionalNode * tmp = egxp_conditional_node_new (parent);
  egxp_conditional_node_add_condition (tmp, cond);
  
  return tmp;
}

void egxp_conditional_node_free (Egxp_ConditionalNode * c) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_free\n");
#endif
  assert (c);
  
  /* free the structure */
  if (c->child) egxp_child_node_free (c->child);
  if (c->conditions) ecore_list_destroy (c->conditions);
  free (c);
}


void egxp_conditional_node_add_condition (Egxp_ConditionalNode * cn, Egxp_Condition * cond) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_add_condition\n");
#endif
  
  assert (cn && cond);
  
  /* check if the conditions lists is created */
  if (cn->conditions == NULL) {
    cn->conditions = ecore_list_new ();
    ecore_list_set_free_cb (cn->conditions, free);
  }
  
  /* append the condition */
  ecore_list_append (cn->conditions, cond);
}

void egxp_conditional_node_set_cb (Egxp_ConditionalNode * n, egxp_callback_ptr * begin, egxp_callback_ptr * end) {
  #ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_set_callback\n");
#endif 

  assert (n);
  
  /* check if the child node is created */
  if (n->child == NULL) n->child = egxp_child_node_new ();
  
  /* set the attributes */
  n->child->begin_func = begin;
  n->child->end_func = end;
}


void egxp_conditional_node_add_child_node (Egxp_ConditionalNode * parent, Egxp_Node * child) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_add_child_node\n");
#endif
  assert (parent && child);

  /* check if the child node is created */
  if (parent->child == NULL) parent->child = egxp_child_node_new ();

  /* add the node to the child element */
  egxp_child_node_add_node (parent->child, child);
}
