#include <assert.h>
#include <stdio.h>

#include "xmpp/xmpp.h"

#include "xmpp_im_struct.h"
#include "xmpp_im_opcode.h"
#include "xmpp_im.h"
#include "xmpp_im_callback.h"


void xmpp_im_callback_roster_init(Egxp_Message *msg, void* data) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_callback_roster_init\n");
#endif
  assert (msg && data);

  Xmpp * x = XMPP_GET(data);

  /* build a message to prevent that we want roster information */
  /* create the iq type="get" */
  Egxp_Message * iq = xmpp_message_iq (XMPP_VALUE_IQ_GET, XMPP_IM_VALUE_IQ_ROSTER_REQUEST,
				       x->jid->host);
  Egxp_Message * query = xmpp_message_query (XMPP_IM_VALUE_QUERY_ROSTER); 
  egxp_message_add_child (iq, query);

  /* now send it */
  Egxp_Connection * conn = EGXP_EXTENSION(x)->parent->connection;
  egxp_connection_send_message (conn, iq, 1);
}


void xmpp_im_callback_roster_populate(Egxp_Message *msg, void* data) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_callback_roster_populate\n");
#endif
  assert (msg && data);
  
  Egxp * eg = EGXP(data);

  /* get the query, all data are inside the query */
  Egxp_Message * query = egxp_message_get_child(msg, XMPP_TAG_QUERY);
  assert (query); 

  /* now get the list of all item message */
  Ecore_List * child_list = egxp_message_get_childs(query, XMPP_IM_TAG_ITEM);

  /* for each element try to create/update the contact */
  xmpp_im_roster_update_from_item_messages (XMPPIM_GET(eg)->roster, child_list);

  /* free list */
  ecore_list_destroy (child_list);

  printf("Callback Roster Populate !!!\n");
}
