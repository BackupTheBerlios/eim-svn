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
#include <string.h>

#include "xmpp/xmpp_jid.h"

#include "xmpp_im_contact.h"
#include "xmpp_im_roster.h"


XmppIM_Roster * xmpp_im_roster_new () {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_new\n");
#endif
  
  XmppIM_Roster * tmp = XMPPIM_ROSTER(malloc (sizeof (XmppIM_Roster)));

  /* create and initialize the groups hash table */
  tmp->groups = ecore_hash_new (ecore_str_hash, 
				ecore_str_compare);
  ecore_hash_set_free_value (tmp->groups,
			     (Ecore_Free_Cb)xmpp_im_roster_group_free);
  
  
  /* create and initialize the users hash table */
  tmp->users = ecore_hash_new (ecore_str_hash, 
			       ecore_str_compare);
  ecore_hash_set_free_value (tmp->users, 
			     (Ecore_Free_Cb)xmpp_im_contact_free);
  ecore_hash_set_free_key (tmp->users,
			   (Ecore_Free_Cb) free);
  
  return tmp;
}


void xmpp_im_roster_update_from_message (XmppIM_Roster *r,
					 Egxp_Message *m) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_update_from_message\n");
#endif
}



void xmpp_im_roster_free (XmppIM_Roster * r) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_free\n");
#endif
  ecore_hash_destroy (r->users);
  ecore_hash_destroy (r->groups);
  FREE (r);
}


void xmpp_im_roster_add_group (XmppIM_Roster * r, XmppIM_RosterGroup * g) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_add_group\n");
#endif
  
  assert (r != NULL && g != NULL);
  
  /* add the group, the key is the groupname */
  ecore_hash_set(r->groups, g->groupname, g);
}


void xmpp_im_roster_add_contact (XmppIM_Roster * r, XmppIM_Contact * c) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_add_contact\n");
#endif

  assert (r != NULL && r->users != NULL && c != NULL);
  
  /**
   * We add the contact using it's jid.
   * The jid must be deleted when the contact is removed
   */
  ecore_hash_set (r->users, xmpp_jid_get_bar (c->jid), c);
}


void xmpp_im_roster_remove_contact (XmppIM_Roster * r, XmppIM_Contact * c) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_roster_remove_contact\n");
#endif

  assert (r != NULL && c != NULL);

  /* remove the contact from his groups */
  xmpp_im_contact_remove_all_group (c);
  
  /* remove the contact from the user hash */
  char * jid = xmpp_jid_get_bar (c->jid);
  XmppIM_Contact * tmp = XMPPIM_CONTACT (ecore_hash_remove (r->users, jid));
  FREE (jid);
  
  

  assert (tmp == c);
}



XmppIM_Contact * xmpp_im_roster_get_contact (XmppIM_Roster *r, char * jid) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_get_contact\n");
#endif


  assert (r != NULL && jid != NULL);
  assert (r->users != NULL);
  
  XmppIM_Contact * tmp = XMPPIM_CONTACT (ecore_hash_get (r->users, jid));
  return tmp;
}



XmppIM_RosterGroup * xmpp_im_roster_add_contact_to_group (XmppIM_Roster *r, XmppIM_Contact * c, char *groupname) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_add_contact_to_group\n");
#endif

  assert (r != NULL && c != NULL && groupname != NULL);
  assert (r->groups != NULL);

  /* get a reference to a group */
  XmppIM_RosterGroup * group = XMPPIM_ROSTERGROUP (ecore_hash_get (r->groups, groupname));
  
  /* if the group doesn't exist we create it */
  if (group == NULL) {
    group = xmpp_im_roster_group_new (groupname);
    xmpp_im_roster_add_group (r, group);    
  }
  
  /* now we can add the contact to the group */
  xmpp_im_roster_group_add_contact (group, c);
  
  return group;
}




/* use to debug */
static int _roster_group_num = 0;



XmppIM_RosterGroup * xmpp_im_roster_group_new (char * groupname) {
#ifdef XMPPIM_DEBUG
  _roster_group_num += 1;
  printf("TRACE: xmpp_im_roster_group_new: %d\n", _roster_group_num);
#endif
  
  XmppIM_RosterGroup * tmp = XMPPIM_ROSTERGROUP(malloc (sizeof (XmppIM_RosterGroup)));
  assert(tmp != NULL);
  
  /* allocate memory for the groupname  and the users list */
  tmp->groupname = strdup (groupname);
  tmp->users = ecore_list_new ();
  
  return tmp;
}


void xmpp_im_roster_group_free (XmppIM_RosterGroup * r) {
#ifdef XMPPIM_DEBUG
  _roster_group_num -= 1;
  printf("TRACE: xmpp_im_roster_group_free: %d\n", _roster_group_num);
#endif

  /* free the group name */
  IF_FREE(r->groupname);

  /* destroy the list, we don't free the contact because their owner is the roster */
  ecore_list_destroy (r->users);
  FREE (r);
}


void xmpp_im_roster_group_remove_contact (XmppIM_RosterGroup * rg, XmppIM_Contact * ec) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_group_remove_contact\n");
#endif

  assert (rg != NULL && ec != NULL);

  /* go to the beginning of the users list */
  ecore_list_goto_first(rg->users);
  XmppIM_Contact * contact_item;
  
  while((contact_item = XMPPIM_CONTACT(ecore_list_current(rg->users))) != NULL) {
    /* If we find the contact, we remove it from the list */
    if( contact_item == ec) {
      ecore_list_remove (rg->users);
      return;
    }
    /* advance inside the list */
    ecore_list_next (rg->users);
  }
}

void xmpp_im_roster_group_add_contact (XmppIM_RosterGroup * rg, XmppIM_Contact *ec) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_group_add_contact\n");
#endif
  
  assert (rg != NULL && ec != NULL && ec->groups != NULL);

  /* update the contact list group of the user*/
  ecore_list_append (ec->groups, rg);
  
  /* update the user group list of the group */
  ecore_list_append (rg->users, ec);
}


void xmpp_im_roster_group_display (void * node, void * user_data) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_group_display\n");
#endif

  XmppIM_RosterGroup * g = XMPPIM_ROSTERGROUP(ECORE_HASH_NODE(node)->value);
  
  assert (g != NULL);
  assert (g->users != NULL);

  printf("-- Group Name: %s\n", g->groupname);
  ecore_list_for_each (g->users, ECORE_FOR_EACH(xmpp_im_contact_display), NULL);
}

void xmpp_im_roster_display (XmppIM_Roster *r) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_display\n");
#endif
  
  assert (r != NULL);
  
  printf("--- Roster Information ---\n");
  ecore_hash_for_each_node (r->groups, ECORE_FOR_EACH(xmpp_im_roster_group_display), NULL);
}




void xmpp_im_roster_update_from_item_messages (XmppIM_Roster *r, Ecore_List * list) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_roster_update_from_item_messages\n");
#endif
  assert (r && list);
  
  Egxp_Message * msg_item;
  ecore_list_goto_first(list);
  while ((msg_item = EGXP_MESSAGE(ecore_list_next(list))) != NULL) {
    xmpp_im_contact_create_from_item_message(r, msg_item);
  }
  xmpp_im_roster_display(r);
}
