#include <stdio.h>
#include <stdlib.h>

#include <Ecore.h>

#include "egxp/egxp.h"
#include "xmpp.h"


int timer_cb (void * user_data) {
  ecore_main_loop_quit ();
}

int main (int argc, char ** argv) {
  
  /**
   * usage
   */
  if (argc != 5) {
    printf("usage:\n\t%s <name> <host_addr> <port_number> <password>\n",argv[0]);
    return 1;
  }

  /* create Egxp  */
  Egxp * eg = egxp_new ();
  
  /* initialize protocol */
  Xmpp * xm = xmpp_register (eg);
  
  
  /* initialize ecore connection */
  ecore_con_init();
  /* after 3 second we quit the ecore loop */
  ecore_timer_add (8, timer_cb, NULL);
  printf("Quit automaticly (after 8 seconds)\n");
  
  /* define the connection */
  eg->connection = egxp_connection_new (argv[2], atoi (argv[3]), 0);
  if (egxp_connection_connect (eg->connection) == 0) {
    printf("Impossible to connect to %s %s\n", argv[2], argv[3]);
  } else {
    printf("We are connected to %s:%s\n", argv[2], argv[3]);
  }
  
  /* define the jid */
  xm->jid = xmpp_jid_new (argv[1], argv[2], "eim");
  
  /* now we can send a message to the server */
  

  /* ecore loop */
  ecore_main_loop_begin();
  /* shutdown */
  ecore_con_shutdown();
  
  /* free Egxp */
  egxp_free (eg);
  
  return 0;
}
