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
#ifndef xmpp_jid_header_h_
#define xmpp_jid_header_h_

/**
 * Here we define the Jid structure and a set of function
 * to handle the jid
 */

typedef struct _Xmpp_JID Xmpp_JID;
#define XMPP_JID(o) ((Xmpp_JID*)o)
struct _Xmpp_JID {
  char * user;
  char * host;
  char * resource;
};


/**
 * Create a new JID
 * @param user: The user name
 * @param host: The host name
 * @param resource: The resource
 */
Xmpp_JID * xmpp_jid_new (char * user, char * host, char * resource);

/**
 * Free the structure
 */
void xmpp_jid_free (Xmpp_JID * jid);


#endif
