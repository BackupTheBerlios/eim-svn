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

#include "egxp/egxp_node.h"

#include "xmpp_callback.h"
#include "xmpp_opcode.h"

void xmpp_opcode_init (Egxp * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_opcode_init\n");
#endif 
  assert (eg && eg->opcodes);

  /* *************** */
  /* register opcode */
  /* *************** */
  /*     stream      */
  egxp_opcode_add (eg->opcodes, XMPP_TAG_STREAM);
  
  egxp_opcode_add (eg->opcodes, XMPP_ATT_XMLNS);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_XMLNS_STREAM);
  
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_XMLNS);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_XMLNS_STREAM);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_VERSION);
  
  
  
  /********************/
  /********************/
  /*  Protocol Init   */
  /********************/
  /********************/
  /* define stream */
  Egxp_Node * stream = egxp_node_new (egxp_opcode_get_id (eg->opcodes, XMPP_TAG_STREAM));
  egxp_node_add_child (eg->root, stream);
  
  egxp_node_add_condition (stream, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_XMLNS),
						       egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_STREAM_XMLNS)));
  
  egxp_node_add_condition (stream, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_XMLNS_STREAM),
						       egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_STREAM_XMLNS_STREAM)));
  
  egxp_node_set_cb (stream, xmpp_callback_stream_begin_cb, NULL);
  
}
