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

#ifndef egxp_header_h_
#define egxp_header_h_

#include <Ecore_Data.h>

#include "egxp_node_struct.h"
#include "egxp_node.h"
#include "egxp_opcode.h"
#include "egxp_condition.h"
#include "egxp_message.h"
#include "egxp_protocol_handler.h"


typedef struct _Egxp Egxp;
#define EGXP(o) ((Egxp*)o)
struct _Egxp {
  /* opcodes list */
  Egxp_Opcode * opcodes;
  
  /* root node */
  Egxp_Node * root;

  /* the protocol handler */
  Egxp_ProtocolHandler * protocol_handler;

  /* contains data */
  Ecore_Hash * extensions;

  /* specific user data */
  void * user_data;
};


typedef struct _Egxp_Extension Egxp_Extension;
#define EGXP_EXTENSION(o) ((Egxp_Extension*)o)
struct _Egxp_Extension {
  Ecore_Free_Cb destroy;
};


/**
 * Allocate the Egxp structure
 * - allocate the opcodes structures 
 * - set to null the opcode
 */
Egxp * egxp_new ();


/**
 * Free the egxp structure
 */
void egxp_free (Egxp * e);


/**
 * Register an extension. It allows to store data, so when you define 
 * other extension you can store you're structure inside
 */
void egxp_extension_register (Egxp * e, int id, void * ext);


/**
 * @return the extension
 */
void * egxp_extension_get (Egxp *e, int id);

#endif
