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

#include "egxp/egxp.h"
#include "xmpp.h"
#include "xmpp_callback.h"


void xmpp_callback_stream_begin_cb (Egxp_Message * msg, void * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_callback_stream_begin_cb\n");
#endif 
  assert (msg && eg);
  
  /* get the xmpp protocol */
  Xmpp * xm = XMPP( egxp_extension_get_from_string (EGXP(eg), XMPP_REGISTER));
  assert (xm);

  /* technically we should control childs of stream tag. But for
     now we just try to authenticate our client NO-SASL */
  
  /* check if there is a authentification object */
  if (xm->auth == NULL) xm->auth = xmpp_auth_new ();

  /* try to set the stream id */
  xm->auth->stream_id = egxp_message_get_attribute (msg, XMPP_ATT_ID);
  
  /* now we can try to send the first message to be authenticied */
  xmpp_auth_msg_no_sasl (xm);
}
