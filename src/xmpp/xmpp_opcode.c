#include <assert.h>

#include "egxp/egxp_node.h"

#include "xmpp_opcode.h"

void xmpp_opcode_init (Egxp * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_opcode_init\n");
#endif 
  assert (eg && eg->opcodes);

  /* *************** */
  /* register opcode */
  /* *************** */
  /*     stream      */
  egxp_opcode_add (eg->opcodes, XMPP_TAG_STREAM);
  
  egxp_opcode_add (eg->opcodes, XMPP_ATT_XMLNS);
  egxp_opcode_add (eg->opcodes, XMPP_ATT_XMLNS_STREAM);
  
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_XMLNS);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_XMLNS_STREAM);
  egxp_opcode_add (eg->opcodes, XMPP_VALUE_STREAM_VERSION);
  
  
  
  /********************/
  /********************/
  /*  Protocol Init   */
  /********************/
  /********************/
  /* define stream */
  Egxp_Node * stream = egxp_node_new (egxp_opcode_get_id (eg->opcodes, XMPP_TAG_STREAM));
  egxp_node_add_child (eg->root, stream);
  
  egxp_node_add_condition (stream, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_XMLNS),
						       egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_STREAM_XMLNS)));
  
  egxp_node_add_condition (stream, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_XMLNS_STREAM),
						       egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_STREAM_XMLNS_STREAM)));
  
}
