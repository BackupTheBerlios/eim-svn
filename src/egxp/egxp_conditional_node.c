#include <assert.h>
#include <stdlib.h>
#include <Ecore_Data.h>
#include "egxp_conditional_node.h"

Egxp_ConditionalNode * egxp_conditional_node_new (Egxp_Node * parent) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_new\n");
#endif
  assert (parent);
  
  Egxp_ConditionalNode * tmp = EGXP_CONDITIONALNODE(malloc (sizeof(Egxp_ConditionalNode)));
  tmp->parent = parent;
  tmp->conditions = NULL;
  tmp->child = NULL;
  return tmp;
}


void egxp_conditional_node_free (Egxp_ConditionalNode * c) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_conditional_node_free\n");
#endif
  assert (c);
  
  if (c->child) egxp_child_node_free (c->child);
  if (c->conditions) ecore_list_destroy (c->conditions);
  free (c);
}
