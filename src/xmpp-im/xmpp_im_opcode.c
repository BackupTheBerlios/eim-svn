#include <assert.h>
#include "egxp/egxp_opcode.h"
#include "xmpp/xmpp_opcode.h"
#include "xmpp_im_callback.h"

#include "xmpp_im_opcode.h"

#define XMPP_IM


void xmpp_im_opcode_init (Egxp *eg) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_opcode_init\n");
#endif
  assert (eg);
  assert (eg->opcodes);

  /******************************************************************************************/
  /* Register opcode */
  /******************************************************************************************/
  egxp_opcode_add(eg->opcodes, XMPP_IM_VALUE_IQ_ROSTER_REQUEST);
  egxp_opcode_add(eg->opcodes, XMPP_IM_VALUE_QUERY_ROSTER);
  egxp_opcode_add(eg->opcodes, XMPP_IM_TAG_ITEM);
  egxp_opcode_add(eg->opcodes, XMPP_IM_TAG_GROUP);

  assert (eg->root);  
  Egxp_Node * stream = egxp_node_get_child(eg->root, egxp_opcode_get_id(eg->opcodes, XMPP_TAG_STREAM));
  assert (stream);

  /******************************************************************************************/
  /* define iq type='result' id='auth_2' */
  /******************************************************************************************/
  Egxp_Node * iq = xmpp_opcode_iq (eg->opcodes, XMPP_VALUE_IQ_RESULT, XMPP_VALUE_IQ_AUTH_2);
  egxp_node_set_cb (iq, NULL, xmpp_im_callback_roster_init);
  egxp_node_add_child (stream, iq);

 /******************************************************************************************/
  /* define iq type='result' id='roster_request' */
  /******************************************************************************************/
  iq = xmpp_opcode_iq (eg->opcodes, XMPP_VALUE_IQ_RESULT, XMPP_IM_VALUE_IQ_ROSTER_REQUEST);
  egxp_node_set_cb (iq, NULL, xmpp_im_callback_roster_populate);
  egxp_node_add_child (stream, iq);
}
