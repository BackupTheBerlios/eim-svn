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
    // ???
  }
  
  free (ph);
}







void egxp_protocol_handler_start_element(void *userData, const char *name, const char **atts) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_start_element\n");
#endif
  assert (userData && name);
  
  /* really hard stuff here, we need to keep in a stack the protocol evolution
     in order to call the correct callback */

  /* we need to store the message hierarchy here (current_msg) */
  
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
