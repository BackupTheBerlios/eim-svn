#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "xmpp/xmpp.h"
#include "xmpp_im.h"


int main (int argc, char ** argv) {

  /**
   * create a set of contact
   * Add it to the group
   */
  XmppIM_Contact * contact;
  Xmpp_JID * jid;
  XmppIM_Roster * roster;
  XmppIM_RosterGroup * group;
  
  roster = xmpp_im_roster_new ();

  char tmp[40];
  int i, j;
  for (i = 0; i < 3; i++) {
    sprintf(tmp, "user%d", i);
    jid = xmpp_jid_new (tmp, "host", "resource");
    sprintf(tmp, "surname%d", i);
    contact = xmpp_im_contact_new (jid, tmp);
    xmpp_im_roster_add_contact (roster, contact);
  
    for (j = 0; j < 3; j++) {
      sprintf(tmp, "group %d", j);
      xmpp_im_roster_add_contact_to_group (roster, contact, tmp);
    }  
  }
  
  xmpp_im_roster_display (roster);

  xmpp_im_roster_free (roster);

  return 0;
}
