#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <Ecore.h>

#include "egxp/egxp.h"
#include "xmpp/xmpp.h"

#include "xmpp_im.h"

int timer_cb (void * user_data) {
  ecore_main_loop_quit ();
  return 1;
}


/**
 * Some test around the Roster structure
 */
void test_roster () {
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

}



/**
 * Test stuff:
 * - Egxp
 * - Xmpp
 * - XmppIM 
 */
int test_all (int argc, char ** argv) {
/**
   * usage
   */
  if (argc != 5) {
    printf("usage:\n\t%s <name> <host_addr> <port_number> <password>\n",argv[0]);
    return 1;
  }

  /* initialize ecore connection */
  ecore_init();
  ecore_con_init ();

  /* create Egxp  */
  Egxp * eg = egxp_new ();
  
  /* initialize protocol */
  Xmpp * xm = xmpp_register (eg);
  XmppIM * xmppim = xmpp_im_register (eg);

  /* after 3 second we quit the ecore loop */
  Ecore_Timer * timer = ecore_timer_add (15, timer_cb, NULL);
  printf("Quit automaticly (after 15 seconds)\n");
  
  /* define the connection */
  eg->connection = egxp_connection_new (argv[2], atoi (argv[3]), 0);
  if (egxp_connection_connect (eg->connection) == 0) { 
    printf("Impossible to connect to %s %s\n", argv[2], argv[3]);
  } else {
    printf("We are connected to %s:%s\n", argv[2], argv[3]);
  }
  
  /* define the jid */
  xm->jid = xmpp_jid_new (argv[1], argv[2], "eim");
  
  /* define the password */
  xm->auth = xmpp_auth_new_with_passwd (argv[4]);
  
  /* now we can send a message to the server */
  xmpp_message_stream (xm);

  /* ecore loop */
  ecore_main_loop_begin();
  
  /* free Egxp */
  egxp_message_print(eg->protocol_handler->current_msg);

  egxp_free (eg);
  
  /* shutdown */
  ecore_con_shutdown ();
  ecore_shutdown();

  return 0;
}




int main (int argc, char ** argv) {

  /* test roster */
  test_roster ();

  return test_all (argc, argv);
}
