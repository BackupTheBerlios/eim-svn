#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <Ecore_Data.h>

#include "egxp_child_node.h"
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


void egxp_node_set_callback (Egxp_Node * n, egxp_callback_ptr * begin, egxp_callback_ptr * end) {
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
