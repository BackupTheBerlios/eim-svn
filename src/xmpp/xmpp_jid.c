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
#include <stdio.h>
#include <string.h>

#include <Ecore_Data.h>

#include "xmpp_jid.h"


Xmpp_JID * xmpp_jid_new (char * user, char * host, char * resource) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_new\n");
#endif 
  
  Xmpp_JID * tmp = XMPP_JID(malloc (sizeof(Xmpp_JID)));
  
  tmp->user = strdup (user);
  tmp->host = strdup (host);
  tmp->resource = strdup (resource);

  return tmp;
}

void xmpp_jid_free (Xmpp_JID * jid) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_free\n");
#endif 
  assert (jid);

  IF_FREE (jid->user);
  IF_FREE (jid->host);
  IF_FREE (jid->resource);

  FREE (jid);
}
