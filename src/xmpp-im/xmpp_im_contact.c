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
#include <stdio.h>

#include "xmpp_im_contact.h"

XmppIM_Contact * xmpp_im_contact_new (Xmpp_JID * jid, char * name) {
#ifdef XMPPIM_DEBUG
  printf("TRACE:xmpp_im_contact_new\n");
#endif
  assert (jid);

  /* create the contact variable */
  XmppIM_Contact * tmp = XMPPIM_CONTACT(malloc(sizeof (XmppIM_Contact)));
  
  /* set default variable */
  tmp->jid = jid;
  tmp->name = strdup (name);
  tmp->groups = ecore_list_new ();
  tmp->presence = -1; // not available
  
  return tmp;
}


void xmpp_im_contact_free (XmppIM_Contact * contact) {
#ifdef XMPPIM_DEBUG
  printf("TRACE:xmpp_im_contact_free\n");
#endif
  assert( contact != NULL);

  /* unregister the contact from his group list */
  xmpp_im_contact_remove_all_group (contact);
  /* remove jid */
  xmpp_jid_free (contact->jid);
  /* free name */
  IF_FREE (contact->name);
  /* remove the list of attached groups */
  ecore_list_destroy (contact->groups);
  
  FREE (contact);
}


void xmpp_im_contact_remove_all_group (XmppIM_Contact * c) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_contact_remove_all_group\n");
#endif
  assert (c != NULL);
  
  /* browse the group list */
  ecore_list_goto_first(c->groups);
  XmppIM_RosterGroup * group_item;
  while((group_item = XMPPIM_ROSTERGROUP(ecore_list_next(c->groups))) != NULL) {
    /* for each group remove this contact */
    xmpp_im_roster_group_remove_contact (group_item, c);
  }
  
  /* the list must be empty */
  ecore_list_clear (c->groups);
  assert (ecore_list_is_empty (c->groups));
}


void xmpp_im_contact_display (void *contact, void * user_data) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_contact_display\n");
#endif
  
  XmppIM_Contact * c = XMPPIM_CONTACT(contact);
  
  assert (c);
  char * tmp = xmpp_jid_get_full (c->jid);
  printf("Surname %s jid: %s\n", c->name, tmp);
  FREE (tmp);
}
