#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <Ecore_Data.h>
#include "xmpp.h"

#include "xmpp_auth.h"

Xmpp_Auth * xmpp_auth_new () {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_auth_new\n");
#endif

  Xmpp_Auth * auth = XMPP_AUTH(malloc (sizeof(Xmpp_Auth)));
  
  auth->password = NULL;
  auth->stream_id = NULL;
  
  return auth;
}


void xmpp_auth_free (Xmpp_Auth * a) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_auth_free\n");
#endif
  assert (a);
  
  IF_FREE(a->password);
  IF_FREE(a->stream_id);
  FREE(a);
}


void xmpp_auth_msg_no_sasl (Xmpp * x) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_auth_msg_no_sasl\n");
#endif
  assert (x);
 
  /* create the iq type="get" */
  Egxp_Message * iq = xmpp_message_iq (XMPP_VALUE_IQ_GET, "auth_1", 
				       x->jid->host);
  /* create the query message */
  Egxp_Message * query = xmpp_message_query (XMPP_VALUE_QUERY_AUTH);
  /* create the username node */
  Egxp_Message * username = egxp_message_new (XMPP_TAG_USERNAME);
  egxp_message_append_data (username, x->jid->user, strlen (x->jid->user));
  
  /* compose */
  egxp_message_add_child (iq, query);
  egxp_message_add_child (query, username);

  /* now send it */
  Egxp_Connection * conn = EGXP_EXTENSION(x)->parent->connection;
  egxp_connection_send_message (conn, iq, 1);
}
