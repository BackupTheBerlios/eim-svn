#include <stdio.h>
#include <assert.h>

#include "egxp.h"



int main (int argc, char ** argv) {
  /* create the protocol grammar */
  Egxp * ph = egxp_new ();
  Egxp_Node * n1 = NULL;
  Egxp_Node * n2 = NULL;
  Egxp_Node * n3 = NULL;
  Egxp_ConditionalNode * c1 = NULL;
  
  /* define basics grammar */
  egxp_opcode_add (ph->opcodes, "stream");
  egxp_opcode_add (ph->opcodes, "jabber:iq:auth");
  
  egxp_opcode_add (ph->opcodes, "iq");
  egxp_opcode_add (ph->opcodes, "type");
  egxp_opcode_add (ph->opcodes, "get");
  egxp_opcode_add (ph->opcodes, "set");
  

  /* display information about opcode */
  egxp_opcode_display (ph->opcodes);

  /* define the protocol */
  ph->root = egxp_node_new (egxp_opcode_get_id (ph->opcodes, "stream"));
  
  /* add the iq part as example */
  n1 = egxp_node_new (egxp_opcode_get_id (ph->opcodes, "iq"));
  egxp_node_add_child_node (ph->root, n1);
  egxp_node_set_cb (n11, NULL, NULL);

  /* add iq type = get */
  c1 = egxp_conditional_node_new_with_condition (n1, egxp_condition_new (egxp_opcode_get_id (ph->opcodes, "type"),
									 egxp_opcode_get_id (ph->opcodes, "get")));
  egxp_conditional_node_set_cb (c1, NULL, NULL);
  
  /* add iq type = set */
  c1 = egxp_conditional_node_new_with_condition (n1, egxp_condition_new (egxp_opcode_get_id (ph->opcodes, "type"),
									 egxp_opcode_get_id (ph->opcodes, "set")));
  egxp_conditional_node_set_cb (c1, NULL, NULL);

  /* free opcode */
  egxp_free (ph);
  
  return 0;
}
