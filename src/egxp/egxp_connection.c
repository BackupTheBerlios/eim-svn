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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "egxp_connection.h"

Egxp_Connection * egxp_connection_new (char * address, unsigned int port, unsigned char use_ssl) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_connection_new\n");
#endif
  assert (address);
  
  Egxp_Connection * tmp = EGXP_CONNECTION (malloc (sizeof(Egxp_Connection)));
 
  tmp->server = NULL;
  tmp->host_addr = strdup (address);
  tmp->use_ssl = use_ssl;
  tmp->port = port;
  
  return tmp;
}


void egxp_connection_free (Egxp_Connection *c) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_connection_free\n");
#endif 
  assert (c);
  /* free the addr */
  IF_FREE (c->host_addr);
  /* disconnect from the server */
  egxp_connection_disconnect (c);
  /* free this object */
  FREE (c);
}

unsigned int egxp_connection_connect (Egxp_Connection *c) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_connection_connect: %s:%d\n", c->host_addr, c->port);
#endif
  assert (c);

  /* call disconnect to be sure that we are currently connected */
  if (c->server) egxp_connection_disconnect (c);
  
  /* set the connection flags */
  int flags = ECORE_CON_REMOTE_SYSTEM;
  if (c->use_ssl) flags = flags | ECORE_CON_USE_SSL;
 
  /* try to connect */
  c->server = ecore_con_server_connect(flags, c->host_addr,
				       c->port, NULL);
  /* test if the connection is ok*/
  if (c->server == NULL) return 0;
  
  /* on success */
  return 1;
}


void egxp_connection_send_message (Egxp_Connection *c, Egxp_Message * msg, unsigned int end_tag) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_connection_send_message\n");
#endif
  assert (c && msg);

  // to xml
  char * buf = egxp_message_to_xml (msg, end_tag);
  printf("LOG egxp_connection_send_message: %s\nsize: %d\n", buf, strlen (buf));
  
  // free message
  egxp_message_free (msg);
  
  // send it !
  ecore_con_server_send (c->server, buf, strlen (buf));
  
  // free message
  FREE (buf);
}


void egxp_connection_disconnect (Egxp_Connection * c) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_connection_disconnect\n");
#endif

  assert (c);

  if (c->server) {
    /* warning FIXME, i don't how close connection work ... */
    printf("egxp_connection_disconnect:: FIXME %s\n", __FILE__);
    ecore_con_server_del (c->server);
    c->server = NULL;
  }
}
