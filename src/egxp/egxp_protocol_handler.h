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
#ifndef egxp_protocol_handler_header_h_
#define egxp_protocol_handler_header_h_

#include <expat.h>
#include "egxp_message.h"

struct _Egxp;

typedef struct _Egxp_ProtocolHandler Egxp_ProtocolHandler;
#define EGXP_PROTOCOLHANDLER(o) ((Egxp_ProtocolHandler*)o)
struct _Egxp_ProtocolHandler {
  
  /* the current message */
  Egxp_Message * current_msg;

  /* the XML Parser */
  XML_Parser parser;
};


/**
 * Allocate the protocol handler structure
 *  - initialize the XML Parser and set Egxp struct as a user data of
 *    the xml parser.
 * @param e: the Egxp structure sets as user data for the xml parser
 */
Egxp_ProtocolHandler * egxp_protocol_handler_new (struct _Egxp * e);


/**
 * Free the protocol handler
 * @param ph: the protocol handler to be freed.
 */
void egxp_protocol_handler_free (Egxp_ProtocolHandler * ph);





#endif
