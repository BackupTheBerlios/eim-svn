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
#ifndef xmpp_message_header_h_
#define xmpp_message_header_h_

#include "egxp/egxp_message.h"
#include "xmpp_struct.h"

/**
 * It defines the messages send to the server.
 * @param x: The Xmpp structure
 */
int xmpp_message_stream (Xmpp * x);


/**
 * This function is an helper function to 
 * build preconfigured iq message.
 * @param type: "set", "get" or "result" must not be null
 * @param id: "id of the query" must not be null
 * @param to: "the destination"
 * @return the build message
 */
Egxp_Message * xmpp_message_iq (char * type, char * id, char * to);


/**
 * This function is a helper function to build a preconfigured
 * query message.
 * @param xmlns: The xmlns value
 * @return the query build message
 */
Egxp_Message * xmpp_message_query (char * xmlns);

#endif
