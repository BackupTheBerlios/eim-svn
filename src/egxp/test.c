#include <stdio.h>
#include <assert.h>

#include "egxp.h"



int main (int argc, char ** argv) {
  /* create the protocol grammar */
  Egxp * eg = egxp_new ();
  Egxp_Node * n1 = NULL;
  Egxp_Node * n2 = NULL;
  Egxp_Node * n3 = NULL;
  
  /******************************************************/
  /******************************************************/
  /*          CREATE THE BASICS OPCODES                 */
  /******************************************************/
  /******************************************************/
  

  /* define basics grammar */
  egxp_opcode_add (eg->opcodes, "stream");
  egxp_opcode_add (eg->opcodes, "jabber:iq:auth");
  
  egxp_opcode_add (eg->opcodes, "iq");
  egxp_opcode_add (eg->opcodes, "type");
  egxp_opcode_add (eg->opcodes, "get");
  egxp_opcode_add (eg->opcodes, "set");
  

  /* display information about opcode */
  egxp_opcode_display (eg->opcodes);
  
  

  /******************************************************/
  /******************************************************/
  /*             CREATE THE PROTOCOL                    */
  /******************************************************/
  /******************************************************/
  
  /* add stream to the root */
  n1 = egxp_node_new (egxp_opcode_get_id (eg->opcodes, "stream"));
  egxp_node_add_child (eg->root, n1);
  
  /* add iq tag */
  n2 = egxp_node_new (egxp_opcode_get_id (eg->opcodes, "iq"));
  egxp_node_add_child (n1, n2);
  
  /* add iq tag + type=set */
  n2 = egxp_node_new (egxp_opcode_get_id (eg->opcodes, "iq"));
  egxp_node_add_condition (n2, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, "type"),
                                                   egxp_opcode_get_id (eg->opcodes, "set")));
  egxp_node_add_child (n1, n2);
  
  /* add iq tag + type=get */
  n2 = egxp_node_new (egxp_opcode_get_id (eg->opcodes, "iq"));
  egxp_node_add_condition (n2, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, "type"),
                                                   egxp_opcode_get_id (eg->opcodes, "get")));
  egxp_node_add_child (n1, n2);
  

  /******************************************************/
  /******************************************************/
  /*            CREATE SOME MESSAGES                    */
  /******************************************************/
  /******************************************************/
  
  /* create a stream message without attribute */
  Egxp_Message * mesg1 = egxp_message_new ("stream");
  /* test if it's possible to get the node from the egxp protocol handler */
  n1 = egxp_protocol_handler_get_node (eg->protocol_handler->protocol_stack,
                                       mesg1, eg->opcodes);
  printf("Get stream node from protocol handler(it should not be null): %X\n", n1); 
  
  /* free the message */
  egxp_message_free (mesg1);
  
  

  /* create a iq message with one attributes */
  mesg1 = egxp_message_new ("iq");
  egxp_message_add_attribute (mesg1, egxp_message_attribute_new ("type", "get"));
  /* test if it's possible to get the node from the egxp protocol handler */
  printf("Get iq node from protocol handler(it should not be null): %X\n",
         egxp_protocol_handler_get_node (n1, mesg1, eg->opcodes));
  /* free the message */
  egxp_message_free (mesg1);
  
  
  /* free opcode */
  egxp_free (eg);
  
  return 0;
}
