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
#ifndef xmpp_core_header_h_
#define xmpp_core_header_h_

#include "egxp/egxp.h"

/**
 * Here we define the xmpp opcodes
 */
#define XMPP_TAG_STREAM "stream:stream"
#define XMPP_TAG_IQ     "iq"
#define XMPP_TAG_QUERY  "query"

#define XMPP_TAG_USERNAME       "username"
#define XMPP_TAG_PASSWORD       "digest"
#define XMPP_TAG_RESOURCE       "resource"

#define XMPP_ATT_XMLNS_STREAM   "xmlns:stream"

#define XMPP_VALUE_STREAM_XMLNS          "jabber:client"
#define XMPP_VALUE_STREAM_XMLNS_STREAM   "http://etherx.jabber.org/streams"
#define XMPP_VALUE_STREAM_VERSION        "1.0"



#define XMPP_ATT_TYPE           "type"
#define XMPP_ATT_TO             "to"
#define XMPP_ATT_XMLNS          "xmlns"
#define XMPP_ATT_VERSION        "version"
#define XMPP_ATT_ID             "id"
#define XMPP_ATT_JID            "jid"
#define XMPP_ATT_FROM           "from"
#define XMPP_ATT_NAME           "name"

#define XMPP_VALUE_IQ_GET       "get"
#define XMPP_VALUE_IQ_SET       "set"
#define XMPP_VALUE_IQ_RESULT    "result"

#define XMPP_VALUE_QUERY_AUTH   "jabber:iq:auth"

#define XMPP_VALUE_IQ_AUTH_1    "auth_1"
#define XMPP_VALUE_IQ_AUTH_2    "auth_2"


/**
 * Define presence opcode.
 */
#define XMPP_TAG_PRESENCE               "presence"
#define XMPP_TAG_PRESENCE_STATUS        "status"
#define XMPP_TAG_PRESENCE_PRIORITY      "priority"
#define XMPP_TAG_PRESENCE_SHOW          "show"

#define XMPP_VALUE_PRESENCE_SHOW_AWAY   "away"
#define XMPP_VALUE_PRESENCE_SHOW_CHAT   "chat"
#define XMPP_VALUE_PRESENCE_SHOW_DND    "dnd"
#define XMPP_VALUE_PRESENCE_SHOW_XA     "xa"
#define XMPP_VALUE_PRESENCE_SHOW_ONLINE "online"



/**
 * Add the xmpp opcode inside the opcode variable
 * @param opcode: use to store xmpp opcode
 */
void xmpp_opcode_init (Egxp * eg);


/**
 * It is an helper function to reduce code size. It create an Egxp_Node 
 * with specific value.
 * @param opcodes: the opcodes structure used to get id.
 * @param type: The type of the iq message (get, set, result)
 * @param id: The id of the message. If the id is null the id condition is not added.
 */
Egxp_Node * xmpp_opcode_iq (Egxp_Opcode * opcodes, char * type, char * id);
#endif
