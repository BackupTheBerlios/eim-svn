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
#ifndef xmpp_header_h_
#define xmpp_header_h_

#include "egxp/egxp.h"

#include "xmpp_struct.h"
#include "xmpp_opcode.h"
#include "xmpp_callback.h"
#include "xmpp_jid.h"
#include "xmpp_auth.h"
#include "xmpp_message.h"

#define XMPP_REGISTER "__XMPP_REGISTER__"

#define XMPP_GET(_eg) \
       XMPP(egxp_extension_get_from_string (_eg, XMPP_REGISTER))

/**
 * Register the xmpp protocol
 *  - initialize the xmpp structure
 *  - register opcode and protocol node
 * @param eg: The Egpx structure
 * @return the Xmpp object
 */
Xmpp * xmpp_register (Egxp * eg);


/**
 * Initialize the xmpp structure.
 */
Xmpp * xmpp_new (Egxp * eg);


/**
 * Free memory
 */
void xmpp_free (Xmpp * x);


/**
 * Set the user name
 * @param x: The xmpp object
 * @param name: The name of the user
 */

#endif
