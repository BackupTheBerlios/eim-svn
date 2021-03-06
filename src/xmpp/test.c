#include <stdio.h>
#include <stdlib.h>

#include <Ecore.h>

#include "egxp/egxp.h"
#include "xmpp.h"


int timer_cb (void * user_data) {
  ecore_main_loop_quit ();
  return 1;
}


void test_jid () {
  int i;
  for (i = 0; i < 2000; i++) {
    Xmpp_JID * tmp = xmpp_jid_new_from_bare ("jol@amessage.de/essai");
    xmpp_jid_free (tmp);
  }
}


int test_xmpp (int argc, char ** argv) {
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
}

int main (int argc, char ** argv) {

  //test_jid ();
  
  return test_xmpp (argc, argv);
}
