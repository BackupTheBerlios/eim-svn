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
  tmp->protocol_stack = e->root;
  assert (tmp->protocol_stack != NULL);

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
  Egxp_Node * node = NULL;

  assert (eg && ph);

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
  
  /* manage protocol */
  assert (ph->protocol_stack);
  
  /* try to get the Egxp_Node correspond to the tag id and parameter */
  node = egxp_protocol_handler_get_node (ph->protocol_stack, message, eg->opcodes);
  
  if (node == NULL) {
    /* do nothing */
  } else {
    /* update the hierarchy */
    ph->protocol_stack = node;
    
    /* take a look if it's possible to execute the callback */
    if (node->begin_cb) node->begin_cb (message, eg);
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



Egxp_Node * egxp_protocol_handler_get_node (Egxp_Node * node, Egxp_Message * message, Egxp_Opcode * opcode) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_get_node\n");
#endif
  
  assert (node && message);
  Egxp_Node * ntmp = NULL;
  if (node->childs == NULL) return NULL;
  
  /* get the good list */
  Ecore_DList * ltmp = ecore_hash_get (node->childs,
                                       (int*)egxp_opcode_get_id (opcode, message->tagname));
  if (ltmp == NULL) return NULL;
  
  /* go to the first node */
  ecore_dlist_goto_first(ltmp);
  while ( (ntmp = ecore_dlist_next(ltmp)) != NULL) {
    /* check if all conditions of the ntmp is inside the message */
    if (ntmp->conditions == NULL) {
      return ntmp;
    }else {
      Egxp_Condition * cond = NULL;
      char condition_ok = 1;
      ecore_list_goto_first (ntmp->conditions);
      /* browse all condition of the node */
      while ( (cond = ecore_list_next (ntmp->conditions)) != NULL) {
        char * attr_val = egxp_message_get_attribute (message, (char*)egxp_opcode_get_string (opcode, cond->key));
        /* if we have not found a condition */
        if (attr_val == NULL) {
          condition_ok = 0;
          break;
        }
        
        /* check now if the value is the correct value */
        if( cond->value == egxp_opcode_get_id (opcode, attr_val)) {
          FREE (attr_val);
          continue;
        } else {
          FREE (attr_val);
          condition_ok = 0;
          break;
        }
      } 

      /* check if the node is ok */
      if (condition_ok) return ntmp;
    }
  }
  
  /* not found */
  return NULL;
}
