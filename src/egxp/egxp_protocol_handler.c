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
#include <stdio.h>
#include "egxp.h"
#include "egxp_protocol_handler.h"


/**
 * XML Parser Callback
 */
void egxp_protocol_handler_start_element(void *userData, const char *name, const char **atts);
void egxp_protocol_handler_end_element(void *userData, const char *name);
void egxp_protocol_handler_char_data (void *userData, const XML_Char *s, int len);


Egxp_ProtocolHandler * egxp_protocol_handler_new (Egxp * e) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_new\n");
#endif 
  
  assert (e);
  
  /* create and initialize the protocol handler */
  Egxp_ProtocolHandler * tmp = EGXP_PROTOCOLHANDLER (malloc (sizeof(Egxp_ProtocolHandler)));
  tmp->current_msg = NULL;

  /* initialize the xml parser */
  tmp->parser = XML_ParserCreate(NULL);
  /* define the data pass as parameter during callback call. */
  XML_SetUserData(tmp->parser, e);
  /* define callback */
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
    /* free the root to be sure that we forget no message */
    egxp_message_free (egxp_message_root (ph->current_msg));
    ph->current_msg = NULL;
  }
  FREE (ph);
}




void egxp_protocol_handler_start_element(void *userData, const char *name, const char **atts) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_start_element : %s\n", name);
#endif
  assert (userData && name);
  
  /* cast the egxp variable */
  Egxp * eg = EGXP (userData);
  Egxp_ProtocolHandler * ph = eg->protocol_handler;
  int i;
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
    /* set the message as root message */
    ph->current_msg = message;
  } else {
    /* add the new message to the root node */
    egxp_message_add_child (ph->current_msg, message);
    /* the new message become the root */
    ph->current_msg = message;
  }
  
  /* manage protocol */
  assert (ph->protocol_stack);
  assert (ph->current_msg);
  
  /* try to get the Egxp_Node correspond to the tag id and parameter */
  node = egxp_protocol_handler_get_node (ph->protocol_stack, message, eg->opcodes);
  
  if (node != NULL) {
    /* update the hierarchy */
    ph->protocol_stack = node;
    
    /* take a look if it's possible to execute the callback */
    if (node->begin_cb) node->begin_cb (message, eg);
  }
}

void egxp_protocol_handler_end_element(void *userData, const char *name) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_end_element : %s\n", name);
#endif
  assert (userData && name);
  
  Egxp * eg = EGXP (userData);
  Egxp_ProtocolHandler * ph = eg->protocol_handler;
  
  assert (eg && ph);
  assert (ph->current_msg);
  
  /* check if the current message is equal to the current protocol stack node */
  if (egxp_protocol_handler_equals (ph->protocol_stack, ph->current_msg, eg->opcodes)) {
    
#ifdef EGXP_DEBUG
    printf("TRACE: egxp_protocol_handler_end_element -> matches opcode : %s\n", name);
#endif   
    
    /* if equals we can call the callback associated to the end and update the protocol_stack */
    if (ph->protocol_stack->end_cb != NULL) ph->protocol_stack->end_cb (ph->current_msg, eg);
    
    /* goto the parent node */
    ph->protocol_stack = ph->protocol_stack->parent;
  
    /* go to the parent message and destroy the current message */
    Egxp_Message * old = ph->current_msg;
    ph->current_msg = old->parent;
    
    /* remove the old message */
    egxp_message_free (old);
  } else {

#ifdef EGXP_DEBUG
    printf("TRACE: egxp_protocol_handler_end_element -> NOT matches opcode : %s\n", name);
#endif   
    
    /* if there is no parent we destroy the current message */
    if (ph->current_msg->parent == NULL) {
      egxp_message_free (ph->current_msg);
      ph->current_msg = NULL;
    }
    /* other wise we continue */
    else ph->current_msg = ph->current_msg->parent;
  }
}


void egxp_protocol_handler_char_data (void *userData, const XML_Char *s, int len) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_char_data\n");
#endif
  assert (userData && len >= 0);
  /* cast the egxp variable */
  Egxp * eg = EGXP (userData);
  Egxp_ProtocolHandler * ph = eg->protocol_handler;
  
  assert (eg && ph && ph->current_msg);
  
  /* append data to the message */
  egxp_message_append_data ( ph->current_msg, (char*) s, len);
}




char egxp_protocol_handler_condition_equals (Ecore_List * conditions, Egxp_Message * message, Egxp_Opcode * opcode) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_condition_equals\n");
#endif
  assert (message && opcode);
  
  /* if the node has no condition we can conclude that they are equals */
  if (conditions == NULL) return 1;
  
  /* compare the condition list */
  Egxp_Condition * cond = NULL;
  ecore_list_goto_first (conditions);
  /* browse all condition of the node */
  while ( (cond = ecore_list_next (conditions)) != NULL) {
    char * attr_val = egxp_message_get_attribute (message, (char*)egxp_opcode_get_string (opcode, cond->key));
    /* if we have not found a condition */
    if (attr_val == NULL) {
      return 0;
    }
    /* check now if the value is the correct value */
    if( cond->value == egxp_opcode_get_id (opcode, attr_val)) {
      FREE (attr_val);
      continue;
    } else {
      FREE (attr_val);
      return 0;
    }
  }
  return 1;
}


char egxp_protocol_handler_equals (Egxp_Node * node, Egxp_Message * message, Egxp_Opcode * opcode) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_equals\n");
#endif
  assert (node && message && opcode);

  /* check if the tag are equals */
  if (node->tag != egxp_opcode_get_id (opcode, message->tagname)) {
    return 0;
  }
 
  /* return true if the conditions are equals */
  return egxp_protocol_handler_condition_equals (node->conditions, message, opcode);
}



Egxp_Node * egxp_protocol_handler_get_node (Egxp_Node * node, Egxp_Message * message, Egxp_Opcode * opcode) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_get_node\n");
#endif
  
  assert (node && message && opcode);
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
    if (egxp_protocol_handler_condition_equals (ntmp->conditions, message, opcode)) {
      return ntmp;
    }
  }
  
  /* not found */
  return NULL;
}



int egxp_protocol_handler_receive_server_cb (void *data, int type, Ecore_Con_Event_Server_Data *ev) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_protocol_handler_receive_server_cb\n");
#endif
  
  assert (data != NULL);
  
  Egxp * eg =  EGXP (data);
  Egxp_ProtocolHandler * ph = eg->protocol_handler;
  XML_Parser parser =  ph->parser;
  
  assert (eg && ph && parser);

  char * tmp_buf = (char*) malloc ((ev->size +1) * sizeof (char));
  tmp_buf[ev->size] = '\0';
  strncpy (tmp_buf, (char*)ev->data, ev->size); 
  printf("Got server data %p [%d] (%s)\n", ev->server, ev->size, tmp_buf);
  free (tmp_buf);
  
  if (XML_Parse(parser, (char*) ev->data, ev->size, 0) == XML_STATUS_ERROR) {
    fprintf(stderr, "%s at line %d\n",
	    XML_ErrorString(XML_GetErrorCode(parser)),
	    XML_GetCurrentLineNumber(parser));
    return 1;
  }
  
  return 1;
}
