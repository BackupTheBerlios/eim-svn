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
#include <string.h>

#include "xmpp/xmpp_opcode.h"
#include "xmpp/xmpp_jid.h"
#include "xmpp_im_roster.h"
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


XmppIM_Contact * xmpp_im_contact_create_from_item_message (XmppIM_Roster * r, Egxp_Message * m) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_contact_create_from_item_message\n");
#endif
  assert (r && m);

  /* get the jid (bare) from the message */
  char * jid = egxp_message_get_attribute (m, XMPP_ATT_JID);
  assert (jid);

  /* check if we have already this contact */
  XmppIM_Contact * contact = xmpp_im_roster_get_contact(r, jid);

  if (contact == NULL) {
    Xmpp_JID * tmp_jid = xmpp_jid_new_from_bare (jid);
    /* get the name of the contact*/
    char * contact_name = egxp_message_get_attribute (m, XMPP_ATT_NAME);
    /* create a contact inside the contact variable */
    if(contact_name == NULL) {
      contact = xmpp_im_contact_new (tmp_jid, jid);
    } else {
      contact = xmpp_im_contact_new (tmp_jid, contact_name);
      free (contact_name);
    }
    xmpp_im_roster_add_contact(r, contact);
  }
  /* free the jid from the message */
  free(jid);
  
  /* process group */
  if (egxp_message_is_empty(m)) {
    /* select a default group in function of the jid */
    char * default_grp;
    if (! xmpp_jid_has_user (contact->jid)) default_grp = "__TRANSPORT__";
    else default_grp = "__GENERAL__";
    /* add the group to the contact */
    xmpp_im_roster_add_contact_to_group (r, contact, default_grp);
    return contact;
  }

  /* register the contact for each group  */
  Ecore_List * grp_list = egxp_message_get_childs (m, "group");
  ecore_list_goto_first(grp_list);
  Egxp_Message * msg_item;
  while((msg_item = EGXP_MESSAGE(ecore_list_next(grp_list))) != NULL) {
    /* the group name is inside the data */
    char * grp_name = egxp_message_get_data (msg_item);

    /* add the contact to the group */
    printf("DEBUG ---> xmpp_im_contact_create_from_item_message GRP NAME: %s\n", 
	   grp_name);
    xmpp_im_roster_add_contact_to_group (r, contact, grp_name);
    
    /* free the group name */
    free (grp_name);
  }

  /* free the list */
  ecore_list_destroy (grp_list);

  return contact;
}
