#include <assert.h>
#include <stdlib.h>

#include <Ecore_Data.h>

#include "egxp_node.h"
#include "egxp_child_node.h"

Egxp_ChildNode * egxp_child_node_new () {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_child_node_new\n");
#endif
  
  Egxp_ChildNode * tmp = EGXP_CHILDNODE(malloc(sizeof(Egxp_ChildNode)));
  tmp->begin_func = NULL;
  tmp->end_func = NULL;
  tmp->childs = NULL;
  
  return tmp;
}


void egxp_child_node_free (Egxp_ChildNode * cn) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_child_node_free\n");
#endif

  assert(cn != NULL);
  if (cn->childs) ecore_hash_destroy (cn->childs);
  free (cn);
}


void egxp_child_node_add_node (Egxp_ChildNode * cn, Egxp_Node * c) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_child_node_add_node\n");
#endif

  assert (cn && c);

  /* if not defined we create it */
  if (cn->childs == NULL) {
    cn->childs = ecore_hash_new (ecore_direct_hash, ecore_direct_compare);
    ecore_hash_set_free_value (cn->childs, (Ecore_Free_Cb)egxp_node_free);
  }
  
  /* so now we can add it */
  ecore_hash_set (cn->childs, &c->tag, c);
}
