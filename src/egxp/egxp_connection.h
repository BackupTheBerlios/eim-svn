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
#ifndef egxp_connection_header_h_
#define egxp_connection_header_h_

#include <Ecore_Con.h>

#include "egxp_message.h"

/**
 * There is a set of function to handle connection properties
 */
typedef struct _Egxp_Connection Egxp_Connection;
#define EGXP_CONNECTION(o) ((Egxp_Connection*)o)
struct _Egxp_Connection {
  
  /* a reference on the server */
  Ecore_Con_Server * server;
  
  /* address to the host */
  char * host_addr;

  /* a flag to know if we use ssl connection */
  unsigned char use_ssl;
  
  /* the port to connect */
  unsigned int port;
};


/**
 * This method allocate a Egxp_Connection structure
 * @param address: The address use to connect
 * @param port: the port number
 * @param use_ssl: 1 if you want to connect in ssl mode, 0 otherwise.
 * @return Egxp_Connection structure.
 */
Egxp_Connection * egxp_connection_new (char * address, unsigned int port, unsigned char use_ssl);



/**
 * Free the Egxp_Connection structure.
 * @param c: The connection object
 */
void egxp_connection_free (Egxp_Connection *c);

/**
 * This method try to connection to the server.
 * @param c: The connection structure
 * @return 1 when success, 0 otherwise
 */
unsigned int egxp_connection_connect (Egxp_Connection *c);


/**
 * This method try to send a message. It destroy the message
 * object after send it.
 * @param c: The connection object
 * @param msg: The message
 * @param end_tag: if set to 1 we send the last </tag> of the message, if it's equals to zero it not send the last tag ... 
 */
void egxp_connection_send_message (Egxp_Connection *c, Egxp_Message * msg, unsigned int end_tag);


/**
 * Disconnect the server
 */
void egxp_connection_disconnect (Egxp_Connection * c);

#endif
