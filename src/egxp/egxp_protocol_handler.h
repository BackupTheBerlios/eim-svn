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
#ifndef egxp_protocol_handler_header_h_
#define egxp_protocol_handler_header_h_

#include <expat.h>
#include <Ecore_Con.h>

#include "egxp_message.h"
#include "egxp_node_struct.h"

struct _Egxp;

typedef struct _Egxp_ProtocolHandler Egxp_ProtocolHandler;
#define EGXP_PROTOCOLHANDLER(o) ((Egxp_ProtocolHandler*)o)
struct _Egxp_ProtocolHandler {
  
  /* the current message */
  Egxp_Message * current_msg;

  /* the XML Parser */
  XML_Parser parser;

  /* the protocol stack */
  Egxp_Node * protocol_stack;
};


/**
 * Allocate the protocol handler structure
 *  - initialize the XML Parser and set Egxp struct as a user data of
 *    the xml parser.
 * @param e: the Egxp structure sets as user data for the xml parser
 */
Egxp_ProtocolHandler * egxp_protocol_handler_new (struct _Egxp * e);


/**
 * Free the protocol handler
 * @param ph: the protocol handler to be freed.
 */
void egxp_protocol_handler_free (Egxp_ProtocolHandler * ph);



/**
 * This method check if there is a child inside the node parameter which has 
 * same properties than the message.
 * 
 * @param node : the node
 * @param m: the message.
 */
Egxp_Node * egxp_protocol_handler_get_node (Egxp_Node * node, 
                                            Egxp_Message * message,
                                            Egxp_Opcode * opcode);



/**
 * This method check if all elements of the conditions list are present 
 * in the message attributes. If the conditions list is null, we conclude that
 * the conditions list is equals to the message attributes.
 * @param conditions: a list of Egxp_Condition object
 * @param message: The message use to check the condition list
 * @param opcode: The list of opcode defined.
 * @return 1 is the condition list is equals, otherwise return 0.
 */
char egxp_protocol_handler_condition_equals (Ecore_List * conditions, 
					     Egxp_Message * message, 
					     Egxp_Opcode * opcode);


/**
 * Check if the node is equal to the message. Use the egxp_protocol_handler_condition_equals
 * to check if the condition list is equal.
 * @param node: The node to test
 * @param message: The message to test
 * @param opcode: The list of opcode defined
 * @return 1 is the node and message are equals
 */
char egxp_protocol_handler_equals(Egxp_Node * node, 
				  Egxp_Message * message, 
				  Egxp_Opcode * opcode);


/**
 * This method should be useb by the ecore asynchronous mechanism in order to
 * give xml data to the parser.
 * @param data: Should be the Egxp type
 * @param type: Type of the event (not used for now)
 * @param ev: The event given by the ecore mechanism
 * @return 1 (we need to take a look inside the ecore documentation ...)
 */
int egxp_protocol_handler_receive_server_cb (void *data, int type, Ecore_Con_Event_Server_Data *ev);

#endif
