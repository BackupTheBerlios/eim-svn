#include <assert.h>
#include <stdio.h>

#include "xmpp_im_contact.h"

XmppIM_Contact * xmpp_im_contact_new (Xmpp_JID * jid, char * name) {
#ifdef XMPPIM_DEBUG
  printf("TRACE:xmpp_im_contact_new\n");
#endif
  assert (jid);
  
  XmppIM_Contact * tmp = XMPPIM_CONTACT(malloc(sizeof (XmppIM_Contact)));
  
  tmp->jid = jid;
  tmp->name = strdup (name);
  tmp->groups = ecore_list_new ();
  
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
  assert (ecore_list_is_empty (c->groups));
}


void xmpp_im_contact_display (void *contact, void * user_data) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_contact_display\n");
#endif
  
  XmppIM_Contact * c = XMPPIM_CONTACT(contact);
  
  assert (c);
  
  printf("Surname %s\n", c->name);
}
