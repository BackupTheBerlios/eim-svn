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

#include "egxp_condition.h"
#include "egxp_node.h"


Egxp_Node * egxp_node_new (const int tag) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node__base_new\n");
#endif 

  Egxp_Node * tmp = EGXP_NODE(malloc(sizeof(Egxp_Node)));
  
  /* initialize the node */
  tmp->tag = tag;
  tmp->parent = NULL;
  
  tmp->begin_cb = NULL;
  tmp->end_cb = NULL;
  
  tmp->conditions = NULL;
  
  tmp->childs = NULL;
  
  return tmp;
}



void egxp_node_free (Egxp_Node * n) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_free\n");
#endif 
  assert (n);
  
  if (n->conditions) ecore_hash_destroy (n->conditions);
  if (n->childs) ecore_hash_destroy (n->childs);
  free (n);
}



void egxp_node_set_cb (Egxp_Node * n, egxp_callback_ptr * begin, egxp_callback_ptr * end) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_set_cb\n");
#endif 
  
  assert (n);
  
  /* set the attributes */
  n->begin_cb = begin;
  n->end_cb = end;
}


void egxp_node_add_condition (Egxp_Node * cn, Egxp_Condition * cond) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_add_condition\n");
#endif
  
  assert (cn && cond);
  
  /* check if the conditions lists is created */
  if (cn->conditions == NULL) {
    cn->conditions = ecore_hash_new (ecore_direct_hash, ecore_direct_compare);
    ecore_hash_set_free_value (cn->conditions, (Ecore_Free_Cb)egxp_condition_free);
  }
  
  /* append the condition */
  ecore_hash_set (cn->conditions, (int*)cond->key, cond);
}


void egxp_node_add_child (Egxp_Node * parent, Egxp_Node * child) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_add_child\n");
#endif
  
  assert (parent && child);

  if (parent->childs == NULL) {
    /* create a hash */
    parent->childs = ecore_hash_new (ecore_direct_hash, ecore_direct_compare);
    /* destroy each element */
    ecore_hash_set_free_value (parent->childs, (Ecore_Free_Cb)ecore_list_destroy);
  }
  
  /* try to get the list for the special tag */
  Ecore_List * ltmp = ecore_hash_get (parent->childs, (int*)child->tag);
  
  if (ltmp == NULL) {
    /* doesn't exist, so create it */
    ltmp = ecore_list_new ();
    ecore_list_set_free_cb (ltmp,(Ecore_Free_Cb)egxp_node_free);
    
    /* append the list to the hash, hash is indexed by the tag id */
    ecore_hash_set (parent->childs, (int*)child->tag, ltmp);
  }
  
  /* now append the child to the list */
  ecore_list_append (ltmp, child);
  /* set the parent for the child */
  child->parent = parent;
}
