#include <stdio.h>
#include <assert.h>

#include "egxp.h"



int main (int argc, char ** argv) {
  /* create the protocol grammar */
  Egxp * ph = egxp_new ();
  Egxp_Node * n1 = NULL;
  Egxp_Node * n2 = NULL;
  Egxp_Node * n3 = NULL;
  
  /* define basics grammar */
  egxp_opcode_add (ph->opcodes, "stream");
  egxp_opcode_add (ph->opcodes, "jabber:iq:auth");
  
  egxp_opcode_add (ph->opcodes, "iq");
  egxp_opcode_add (ph->opcodes, "type");
  egxp_opcode_add (ph->opcodes, "get");
  egxp_opcode_add (ph->opcodes, "set");
  

  /* display information about opcode */
  egxp_opcode_display (ph->opcodes);
  
  n1 = egxp_node_new (egxp_opcode_get_id (ph->opcodes, "stream"));
  egxp_node_add_child (ph->root, n1);
  
  /* add iq tag */
  n2 = egxp_node_new (egxp_opcode_get_id (ph->opcodes, "iq"));
  egxp_node_add_child (n1, n2);
  
  /* add iq tag + type=set */
  n2 = egxp_node_new (egxp_opcode_get_id (ph->opcodes, "iq"));
  egxp_node_add_condition (n2, egxp_condition_new (egxp_opcode_get_id (ph->opcodes, "type"),
							egxp_opcode_get_id (ph->opcodes, "set")));
  egxp_node_add_child (n1, n2);
  
  
  /* add iq tag + type=get */
  n2 = egxp_node_new (egxp_opcode_get_id (ph->opcodes, "iq"));
  egxp_node_add_condition (n2, egxp_condition_new (egxp_opcode_get_id (ph->opcodes, "type"),
							egxp_opcode_get_id (ph->opcodes, "get")));
  egxp_node_add_child (n1, n2);
  
  /* free opcode */
  egxp_free (ph);
  
  return 0;
}
