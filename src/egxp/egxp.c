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
  tmp->root = NULL;
  
  /* initialize the user data */
  tmp->user_data = NULL;
  
  /* define the protocol handler */
  tmp->protocol_handler = egxp_protocol_handler_new (tmp);

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
  
  free (e);
}
