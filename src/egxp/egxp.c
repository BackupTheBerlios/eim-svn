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
#include "egxp.h"

Egxp * egxp_new () {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_new\n");
#endif
  Egxp * tmp = EGXP(malloc (sizeof(Egxp)));
  /* define the opcode */
  tmp->opcodes = egxp_opcode_new ();
  
  /* the root of the protocol */
  tmp->root = egxp_node_new (egxp_opcode_get_id (tmp->opcodes, 
						      "__ROOT__"));
    
  /* initialize the user data */
  tmp->user_data = NULL;
  
  /* define the protocol handler */
  tmp->protocol_handler = egxp_protocol_handler_new (tmp);

  /* initialzie extension */
  tmp->extensions = NULL;

  return tmp;
}


void egxp_free (Egxp * e) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_free\n");
#endif
  assert (e);
  /* free opcode */
  egxp_opcode_free (e->opcodes);
  /* free node */
  if (e->root) egxp_node_free(e->root);
  /* free protocol handler */
  if (e->protocol_handler) egxp_protocol_handler_free (e->protocol_handler);
  /* free extension */
  if (e->extensions) ecore_hash_destroy (e->extensions);
  
  free (e);
}


void egxp_extension_free (void * e) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_extension_free\n");
#endif
  assert (e);
  
  Egxp_Extension * ext = EGXP_EXTENSION(e);
  ext->destroy (e);
}

void egxp_extension_register (Egxp * e, int id, void * ext) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_extension_register\n");
#endif
  assert (e && ext);

  if (e->extensions == NULL) {
    e->extensions = ecore_hash_new (ecore_direct_hash, ecore_direct_compare);
    ecore_hash_set_free_value (e->extensions, egxp_extension_free);
  }
  
  ecore_hash_set (e->extensions, (int*)id, ext);
}


void * egxp_extension_get (Egxp *e, int id) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_extension_get\n");
#endif
  assert (e && id);
  assert (e->extensions);

  return ecore_hash_get (e->extensions, (int*)id);
}
