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
  printf("TRACE: egxp_node_new\n");
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
  
  if (n->conditions) ecore_list_destroy (n->conditions);
  if (n->childs) ecore_hash_destroy (n->childs);
  FREE (n);
}



void egxp_node_set_cb (Egxp_Node * n, egxp_callback_ptr begin, egxp_callback_ptr end) {
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
   
  /* check if the node is already attached to a parent. If it is already 
     attached we generate an error */
  assert (cn->parent == NULL);

  /* check if the conditions lists is created */
  if (cn->conditions == NULL) {
    cn->conditions = ecore_list_new ();
    ecore_list_set_free_cb (cn->conditions, (Ecore_Free_Cb)egxp_condition_free);
  }
  
  /* append the condition */
  ecore_list_append (cn->conditions, cond);
}


void egxp_node_add_in_order (Ecore_DList * l, Egxp_Node * n) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_add_in_order\n");
#endif

  assert (l && n);
  Egxp_Node * pn = NULL;

  /* before doing anything, check if there is condition,
     if not we add it to the end if the list */
  if (n->conditions == NULL || ecore_list_nodes (l) == 0) {
    ecore_dlist_append (l, n);
    return;
  }
  
  
  /* go to the first node */
  ecore_dlist_goto_first(l);
  
  while((pn = EGXP_NODE(ecore_dlist_next(l))) != NULL) {
    if (pn->conditions == NULL || 
        ecore_dlist_nodes (n->conditions) > ecore_dlist_nodes(pn->conditions)) {
      ecore_dlist_previous(l);
      ecore_dlist_insert (l, n);
      return;
    }
  }
  
  ecore_dlist_append (l, n);
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
    ecore_hash_set_free_value (parent->childs, (Ecore_Free_Cb)ecore_dlist_destroy);
  }
  
  /* try to get the list for the special tag */
  Ecore_DList * ltmp = ECORE_DLIST (ecore_hash_get (parent->childs, (int*)child->tag));
  
  if (ltmp == NULL) {
    /* doesn't exist, so create it */
    ltmp = ecore_dlist_new ();
    ecore_dlist_set_free_cb (ltmp,(Ecore_Free_Cb)egxp_node_free);
    
    /* append the list to the hash, hash is indexed by the tag id */
    ecore_hash_set (parent->childs, (int*)child->tag, ltmp);
  }
  
  /* now append the child to the list */
  egxp_node_add_in_order (ltmp, child);

  /* set the parent for the child */
  child->parent = parent;
}


Egxp_Node * egxp_node_get_child (Egxp_Node * node, int id) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_get_child\n");
#endif
  
  assert (node && id>=0);
  Egxp_Node * ntmp = NULL;
  if (node->childs == NULL) return NULL;

  /* get the good list */
  Ecore_DList * ltmp = ecore_hash_get (node->childs, (int*)id);

  /* if no child return NULL */
  if (ltmp == NULL) return NULL;

  /* go to the first node */
  return ecore_dlist_goto_last(ltmp);
}


void __print_childs (void * node, void * user_data) {
  Ecore_DList * list = ECORE_DLIST (ECORE_HASH_NODE(node)->value);
  ecore_dlist_for_each (list, ECORE_FOR_EACH (egxp_node_print), user_data);
  //egxp_node_print (value, EGXP_OPCODE (user_data));
}


void egxp_node_print (Egxp_Node * n, Egxp_Opcode * op) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_node_print\n");
#endif
  assert (n && op);
  printf("Tag name: %s -- CB begin: %p -- CB end: %p\n", egxp_opcode_get_string(op, n->tag), n->begin_cb, n->end_cb);
  
  if (n->conditions) ecore_list_for_each (n->conditions, ECORE_FOR_EACH (egxp_condition_print), op);
  if (n->childs) ecore_hash_for_each_node (n->childs, ECORE_FOR_EACH (__print_childs), op);
}
