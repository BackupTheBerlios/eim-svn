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

#define XMPP_ATT_XMLNS          "xmlns"
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




/**
 * Add the xmpp opcode inside the opcode variable
 * @param opcode: use to store xmpp opcode
 */
void xmpp_opcode_init (Egxp * eg);


#endif
