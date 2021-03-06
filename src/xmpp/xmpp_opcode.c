/*
   $Id$

   Copyright (C) 2005 Jo�l Vennin < joel.vennin _@_ gmail _dot_ com >
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
#include "xmpp_auth.h"
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
  egxp_opcode_add (eg->opcodes, XMPP_TAG_IQ);
  egxp_opcode_add (eg->opcodes, XMPP_TAG_QUERY);
  
  egxp_opcode_add (eg->opcodes, XMPP_ATT_XMLNS);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_XMLNS_STREAM);
  
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_XMLNS);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_XMLNS_STREAM);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_VERSION);
  
  
  egxp_opcode_add (eg->opcodes, XMPP_ATT_TYPE);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_TO);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_XMLNS);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_VERSION);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_ID);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_JID);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_FROM);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_NAME);

  
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_IQ_GET);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_IQ_SET);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_IQ_RESULT);
  
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_QUERY_AUTH);
  
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_IQ_AUTH_1);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_IQ_AUTH_2);

  
  /* define presence tag & value */
  egxp_opcode_add (eg->opcodes, XMPP_TAG_PRESENCE);
  egxp_opcode_add (eg->opcodes, XMPP_TAG_PRESENCE_STATUS);
  egxp_opcode_add (eg->opcodes, XMPP_TAG_PRESENCE_PRIORITY);
  egxp_opcode_add (eg->opcodes, XMPP_TAG_PRESENCE_SHOW);
  
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_PRESENCE_SHOW_AWAY);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_PRESENCE_SHOW_CHAT);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_PRESENCE_SHOW_DND);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_PRESENCE_SHOW_XA);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_PRESENCE_SHOW_ONLINE);
  


  /********************/
  /********************/
  /*  Protocol Init   */
  /********************/
  /********************/
  /* define stream */
  Egxp_Node * stream = egxp_node_new (egxp_opcode_get_id (eg->opcodes, XMPP_TAG_STREAM));
  egxp_node_add_condition (stream, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_XMLNS),
						       egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_STREAM_XMLNS)));
  
  egxp_node_add_condition (stream, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_XMLNS_STREAM),
						       egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_STREAM_XMLNS_STREAM)));
  
  egxp_node_set_cb (stream, xmpp_callback_stream_begin_cb, NULL);
  egxp_node_add_child (eg->root, stream);

  /*************************************************************************************/
  /* define iq type='result' id='auth_1' */
  /*************************************************************************************/  
  Egxp_Node * iq = xmpp_opcode_iq (eg->opcodes, XMPP_VALUE_IQ_RESULT, XMPP_VALUE_IQ_AUTH_1);
  egxp_node_set_cb (iq, NULL, xmpp_auth_auth_1_cb);
  egxp_node_add_child (stream, iq);
}



Egxp_Node * xmpp_opcode_iq (Egxp_Opcode * opcodes, char * type, char * id) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_opcode_iq\n");
#endif 
  assert (opcodes);

  Egxp_Node * iq = egxp_node_new (egxp_opcode_get_id (opcodes, XMPP_TAG_IQ));
  egxp_node_add_condition (iq, egxp_condition_new (egxp_opcode_get_id (opcodes, XMPP_ATT_TYPE),
						       egxp_opcode_get_id (opcodes, type)));
  if(id) egxp_node_add_condition (iq, egxp_condition_new (egxp_opcode_get_id (opcodes, XMPP_ATT_ID),
						       egxp_opcode_get_id (opcodes, id)));
  return iq;
}
