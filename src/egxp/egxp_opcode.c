#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "egxp_opcode.h"

Egxp_Opcode * egxp_opcode_new () {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_new\n");
#endif
  Egxp_Opcode * tmp = EGXP_OPCODE(malloc (sizeof(Egxp_Opcode)));

  /* initialize the hash map */
  tmp->string_id = ecore_hash_new (ecore_str_hash, ecore_str_compare);
  ecore_hash_set_free_value (tmp->string_id,(Ecore_Free_Cb) free);
  
  tmp->id_string = NULL;
  tmp->id = 0;
  tmp->need_update = 0;

  return tmp;
}


void egxp_opcode_free (Egxp_Opcode * op) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_free\n");
#endif
  assert (op);
  
  /* free only the initial pointer */
  free (op->id_string);

  // static string, so it's forbidden to destroy if (op->id_string) free (op->id_string);
  ecore_hash_destroy (op->string_id);
  free (op);
}


unsigned int egxp_opcode_add (Egxp_Opcode * op, const char * name) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_add\n");
#endif

  assert (op && name);
  
  /* allocate the memory for the id */
  unsigned int * id = (unsigned int*) malloc (sizeof (unsigned int));
  *id = op->id++;
  
  /* add the new element */
  ecore_hash_set (op->string_id, (char*)name, id);

  /* the id_string must be updated */
  op->need_update = 1;
  
  return *id;
}


void egxp_internal_copy (void *node, void *user_data) {
  assert (node && user_data);
  EGXP_OPCODE(user_data)->id_string[*((int*)ECORE_HASH_NODE(node)->value)] = ECORE_HASH_NODE(node)->key;
}

void egxp_opcode_update (Egxp_Opcode * op) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_update\n");
#endif
  
  assert (op);

  /* check if it is necessary to update it */
  if (! op->need_update) return;
  
  /* realloc the id_string */
  op->id_string = (char **) realloc (op->id_string, op->id * sizeof(char *));
  memset (op->id_string, 0, op->id * sizeof(char *));
  
  /* now copy each element from the string_id to id_string */
  ecore_hash_for_each_node (op->string_id, ECORE_FOR_EACH (egxp_internal_copy), op);

  /* ok, it's done ! */
  op->need_update = 0;
}


const char * egxp_opcode_get_string (Egxp_Opcode * op, const unsigned int id) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_get_string\n");
#endif

  assert (op);
  
  if (op->need_update == 1) egxp_opcode_update (op);

  if ( id >= op->id ) return NULL; 
  return op->id_string[id];
}


const unsigned int * egxp_opcode_get_id (const Egxp_Opcode *op, const char * name) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_get_id\n");
#endif
  assert (op && name);

  return ((int*)ecore_hash_get (op->string_id, (char*)name));
}


void egxp_opcode_display (Egxp_Opcode * op) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_display\n");
#endif
  int i;
  assert (op);
  
  /* bad, need to change it */
  if (op->need_update == 1) egxp_opcode_update (op);
  
  printf("Opcode List:\n");

  /* display each element, normaly we must not make
     a direct access */
  for (i = 0; i < op->id; ++i) {
    printf("\tOPCODE: %s  -- VALUE: %d\n", 
	   op->id_string[i], i);
  }
}
