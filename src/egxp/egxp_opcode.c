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


int egxp_opcode_add (Egxp_Opcode * op, const char * name) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_add\n");
#endif

  assert (op && name);
  
  /* allocate the memory for the id */
  int * id = (int*) malloc (sizeof (int));
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


const char * egxp_opcode_get_string (Egxp_Opcode * op, const int id) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_get_string\n");
#endif

  assert (op);
  
  if (op->need_update == 1) egxp_opcode_update (op);

  if ( id >= op->id ) return NULL; 
  return op->id_string[id];
}


const int egxp_opcode_get_id (const Egxp_Opcode *op, const char * name) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_opcode_get_id\n");
#endif
  assert (op && name);

  int * tmp = ecore_hash_get (op->string_id, (char*)name);
  if (!tmp) {
    printf("ERROR: opcode %s seems to has no id\n"); 
    assert (0);
    return -1;
  }
  
  return *tmp;
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
