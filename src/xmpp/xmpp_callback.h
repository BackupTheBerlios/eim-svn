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
#ifndef xmpp_opcode_header_h_
#define xmpp_opcode_header_h_

#include "egxp/egxp_node_struct.h"


/**
 * Stream begin callback.
 *  - try to get the stream id.
 *  - send a message to authenticiate.
 */
void xmpp_callback_stream_begin_cb (Egxp_Message * msg, void * eg);


#endif
