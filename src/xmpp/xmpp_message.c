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
  
  /* to xml */
  char * buf = egxp_message_to_xml (message, 0);
  
  /* free message */
  egxp_message_free (message);

  // to be continued ...
  
  /* free buffer */
  FREE(buf);
}
