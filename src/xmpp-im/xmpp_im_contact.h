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
#ifndef xmpp_im_contact_headers
#define xmpp_im_contact_headers


#include <Ecore_Data.h>

#include "xmpp/xmpp_jid.h"
#include "xmpp_im_struct.h"

/**
 * Create a new contact.
 * @param jid: The jid of the user
 * @param name: The name of the user
 */
XmppIM_Contact * xmpp_im_contact_new (Xmpp_JID * jid, char * name);


/**
 * Free the parameters.
 */
void xmpp_im_contact_free (XmppIM_Contact * contact);


/**
 * Remove all group of the contact. This function update the group
 * contact list of each group.
 * @param c: the contact
 */
void xmpp_im_contact_remove_all_group (XmppIM_Contact * c);



/**
 * Display information about contact in the stdout stream
 * @param c: the contact to display
 */
void xmpp_im_contact_display (void *c, void * user_data);

#endif
