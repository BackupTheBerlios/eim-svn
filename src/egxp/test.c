#include <stdio.h>
#include <assert.h>

#include "egxp.h"

#define OP_1 "op1"
#define OP_2 "op2"


void test_opcode (Egxp_Opcode * opcodes) {
  egxp_opcode_add (opcodes, OP_1);
  egxp_opcode_add (opcodes, OP_2);
}



int main (int argc, char ** argv) {
  /* create the protocol grammar */
  Egxp * eg = egxp_new ();
  Egxp_Node * n1 = NULL;
  Egxp_Node * n2 = NULL;
  
  /******************************************************/
  /******************************************************/
  /*          CREATE THE BASICS OPCODES                 */
  /******************************************************/
  /******************************************************/
  
  test_opcode (eg->opcodes);

  /* define basics grammar */
  egxp_opcode_add (eg->opcodes, "stream");
  egxp_opcode_add (eg->opcodes, "jabber:iq:auth");
  
  egxp_opcode_add (eg->opcodes, "iq");
  egxp_opcode_add (eg->opcodes, "type");
  egxp_opcode_add (eg->opcodes, "get");
  egxp_opcode_add (eg->opcodes, "set");
  

  egxp_opcode_print (eg->opcodes);
  
  

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
  egxp_message_add_attribute (mesg1, egxp_message_attribute_new ("fr", "sd"));
  egxp_message_add_attribute (mesg1, egxp_message_attribute_new ("dfr", "sd"));
  egxp_message_add_attribute (mesg1, egxp_message_attribute_new ("ffr", "sd"));
  egxp_message_add_attribute (mesg1, egxp_message_attribute_new ("gfr", "sd"));
  /* test if it's possible to get the node from the egxp protocol handler */
  n1 = egxp_protocol_handler_get_node (eg->protocol_handler->protocol_stack,
                                       mesg1, eg->opcodes);
  printf("Get stream node from protocol handler(it should not be null): %p\n", n1); 
  
  
  eg->protocol_handler->current_msg = mesg1;
  
  /* free the message */
  //  egxp_message_free (mesg1);
  
  

  /* create a iq message with one attributes */
  Egxp_Message * mesg2 = egxp_message_new ("iq");
  egxp_message_add_attribute (mesg2, egxp_message_attribute_new ("type", "get"));
  egxp_message_add_attribute (mesg2, egxp_message_attribute_new ("atype", "eget"));
  egxp_message_add_attribute (mesg2, egxp_message_attribute_new ("ntype", "aget"));
  egxp_message_add_attribute (mesg2, egxp_message_attribute_new ("dtype", "gfget"));
  /* test if it's possible to get the node from the egxp protocol handler */
  printf("Get iq node from protocol handler(it should not be null): %p\n",
         egxp_protocol_handler_get_node (n1, mesg2, eg->opcodes));
  
  egxp_message_add_child (mesg1, mesg2);

  /* free the message */
  // egxp_message_free (mesg1);
  
  int i;
  for (i = 0; i < 1000 ; i++) {
    char * buf = egxp_message_to_xml (mesg1, 1);
    printf("%s\n%d\n", buf, strlen (buf));
    free (buf);
  }
  
  /* free opcode */
  egxp_free (eg);
  
  return 0;
}
