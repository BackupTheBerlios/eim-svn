#include <assert.h>
#include "egxp/egxp_opcode.h"
#include "xmpp/xmpp_opcode.h"
#include "xmpp_im_callback.h"

#include "xmpp_im_opcode.h"



void xmpp_im_opcode_init (Egxp *eg) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_opcode_init\n");
#endif
  assert (eg);
  assert (eg->opcodes);

  /* 
     get the message when the authentification is done
     and associate a callback to it.
     we need to catch <iq id='auth_2' type='result'/>
  */
  assert (eg->root);
  
  Egxp_Node * stream = egxp_node_get_child(eg->root, 
					   egxp_opcode_get_id(eg->opcodes, XMPP_TAG_STREAM));
  assert (stream);
  
  /* define iq type='result' id='auth_2' */
  Egxp_Node * iq = egxp_node_new (egxp_opcode_get_id (eg->opcodes, XMPP_TAG_IQ));
  egxp_node_add_child (stream, iq);
  /* type = result */
  egxp_node_add_condition (iq, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_TYPE),
						   egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_IQ_RESULT)));
  egxp_node_add_condition (iq, egxp_condition_new (egxp_opcode_get_id (eg->opcodes, XMPP_ATT_ID),
						   egxp_opcode_get_id (eg->opcodes, XMPP_VALUE_IQ_AUTH_2)));
  /* attach callback */
  egxp_node_set_cb (iq, NULL, xmpp_im_callback_roster_init);
}
