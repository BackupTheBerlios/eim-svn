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
#include "egxp.h"
#include "egxp_protocol_handler.h"


/**
 * XML Parser Callback
 */
void egxp_protocol_handler_start_element(void *userData, const char *name, const char **atts);
void egxp_protocol_handler_end_element(void *userData, const char *name);
void egxp_protocol_handler_char_data (void *userData, const XML_Char *s, int len);


Egxp_ProtocolHandler * egxp_protocol_handler_new (struct _Egxp * e) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_new\n");
#endif 
  
  assert (e);
  
  /* create and initialize the protocol handler */
  Egxp_ProtocolHandler * tmp = EGXP_PROTOCOLHANDLER (malloc (sizeof(Egxp_ProtocolHandler)));
  tmp->current_msg = NULL;

  /* initialize the xml parser */
  tmp->parser = XML_ParserCreate(NULL);
  XML_SetUserData(tmp->parser, e);
  XML_SetElementHandler(tmp->parser, 
			egxp_protocol_handler_start_element, 
			egxp_protocol_handler_end_element);
  XML_SetCharacterDataHandler(tmp->parser,  egxp_protocol_handler_char_data);

  /* initialize the protocol stack */
  tmp->protocol_stack = NULL;
  
  return tmp;
}

void egxp_protocol_handler_free (Egxp_ProtocolHandler * ph) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_free\n");
#endif 
  
  assert (ph);
  
  /* need to free the parser */
  if (ph->parser) XML_ParserFree(ph->parser);

  /* do we need to free the message ? */
  if (ph->current_msg) {
    egxp_message_free (ph->current_msg);
  }
  
  free (ph);
}







void egxp_protocol_handler_start_element(void *userData, const char *name, const char **atts) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_start_element\n");
#endif
  assert (userData && name);
  
  /* cast the egxp variable */
  Egxp * eg = EGXP (userData);
  Egxp_ProtocolHandler * ph = eg->protocol_handler;
  int i;
  char use_callback = 0;

  assert (eg && ph);

  /* really hard stuff here, we need to keep in a stack the protocol evolution
     in order to call the correct callback */

  /* we need to store the message hierarchy here (current_msg) */
  
  /* build the message with the specific id */
  /* NOTE we should update the egxp_message to use integer id */
  Egxp_Message * message = egxp_message_new ((char*) name);
  
  /* process attributes */
  for (i = 0; atts[i]; i += 2)
    egxp_message_add_attribute (message,
				egxp_message_attribute_new((char*)atts[i],(char*) atts[i+1]));
  
  /* attach the message */
  if (ph->current_msg == NULL) {
    ph->current_msg = message;
  } else {
    egxp_message_add_child (ph->current_msg, message);
    ph->current_msg = message;
  }

  /* need to detect which callback to call, if an element in not 
     inside the protocol */
  if (ph->protocol_stack == NULL) {
    /* if null it's because it's the first time we are here 
       so we need to check inside  protocol tree if the tag
       is the root.
    */
    assert (eg->root);
    
    if (!strcmp (egxp_opcode_get_string (eg->opcodes, eg->root->tag),
		 name)) {
      /* they are equals, we begin :p */
      ph->protocol_stack = eg->root;
      use_callback = 1;
    } else {
      /* seems to be an error */
    }
  } else {
    /* 
       we check if the protocol_stack element has the name as
       child node, if the tag name is present we are on the 
       good way, otherwise it seems that the implementation is 
       not completed
    */
    
  }

  
  /*
    if all is ok, we can call the callback associated to this
    message (check the use_callback value)
  */
  if (use_callback) {
    assert (ph->protocol_stack);
  }
}

void egxp_protocol_handler_end_element(void *userData, const char *name) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_end_element\n");
#endif
  assert (userData && name);

}

void egxp_protocol_handler_char_data (void *userData, const XML_Char *s, int len) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_char_data\n");
#endif
  assert (userData);
  
  
}
