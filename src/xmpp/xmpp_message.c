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

#include "egxp/egxp_message.h"

#include "xmpp_opcode.h"
#include "xmpp_message.h"



int xmpp_message_stream (Xmpp * x) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_message_stream\n");
#endif
  
  assert (x);
  
  /**
   * Make the stream message
   */
  Egxp_Message * message = egxp_message_new (XMPP_TAG_STREAM);
  egxp_message_add_attribute (message, 
			      egxp_message_attribute_new (XMPP_ATT_XMLNS, 
							  XMPP_VALUE_STREAM_XMLNS));
  egxp_message_add_attribute (message, 
			      egxp_message_attribute_new (XMPP_ATT_XMLNS_STREAM, 
							  XMPP_VALUE_STREAM_XMLNS_STREAM));
  egxp_message_add_attribute (message, 
			      egxp_message_attribute_new (XMPP_ATT_VERSION, 
							  XMPP_VALUE_STREAM_VERSION));
  egxp_message_add_attribute (message, 
			      egxp_message_attribute_new (XMPP_ATT_TO, 
							  x->jid->host));
  
  /* send message */
  /* get reference to the connection */
  Egxp_Connection * conn = EGXP_EXTENSION(x)->parent->connection;
  egxp_connection_send_message (conn, message, 0);

  return 1;
}

Egxp_Message * xmpp_message_iq (char * type, char * id, char * to) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_message_iq\n");
#endif
  assert (type && id);
  
  /* create the iq */
  Egxp_Message * msg = egxp_message_new (XMPP_TAG_IQ);
  egxp_message_add_attribute (msg, egxp_message_attribute_new (XMPP_ATT_TYPE,
							       type));
  /* id */
  egxp_message_add_attribute (msg, egxp_message_attribute_new (XMPP_ATT_ID,
							       id));
  /* to */
  if (to) 
    egxp_message_add_attribute (msg, egxp_message_attribute_new (XMPP_ATT_TO,
								 to));
  
  return msg;
}


Egxp_Message * xmpp_message_query (char * xmlns) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_message_query\n");
#endif 
  assert (xmlns);
  
  /* build the query message */
  Egxp_Message * message = egxp_message_new (XMPP_TAG_QUERY);
  /* set the xmlns attribute */
  egxp_message_add_attribute (message, 
			      egxp_message_attribute_new (XMPP_ATT_XMLNS, 
							  xmlns));
  return message;
}
