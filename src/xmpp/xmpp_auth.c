#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <Ecore_Data.h>

#include "egxp/egxp_message.h"

#include "xmpp.h"
#include "sha1.h"

#include "xmpp_auth.h"

Xmpp_Auth * xmpp_auth_new () {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_auth_new\n");
#endif
  
  /* initialize the structure */
  Xmpp_Auth * auth = XMPP_AUTH(malloc (sizeof(Xmpp_Auth)));
  
  /* initialize data */
  auth->password = NULL;
  auth->stream_id = NULL;
  
  return auth;
}


void xmpp_auth_free (Xmpp_Auth * a) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_auth_free\n");
#endif
  assert (a);
  
  /* free password && stream_id */
  IF_FREE(a->password);
  IF_FREE(a->stream_id);
  
  /* free structure */
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



void xmpp_auth_auth_1_cb (Egxp_Message * msg, void * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_auth_auth_1_cb\n");
#endif
  /**
   * When we received this message it is because we have succeed
   * the first non-sasl step or there is an error ?. Now in 
   * function of the reply of the server we should 
   * send good information
   */
  assert (msg && eg);
  
  /* get the xmpp protocol */
  Xmpp * xm = XMPP( egxp_extension_get_from_string (EGXP(eg), XMPP_REGISTER));
  assert (xm);

  /* now analyse the response of the server */
  /* try to get the query */
  Egxp_Message * received_query = egxp_message_get_child (msg,  XMPP_TAG_QUERY);
  if (received_query == NULL) {
    egxp_message_print (msg);
    assert (0);
  }
  /* FIXME: Technically we should test the response of the server to know what
     type of message we need to send */



  /* begin to build our response */
  /* iq type=set id=auth_2 to=... */
  Egxp_Message * iq = xmpp_message_iq (XMPP_VALUE_IQ_SET, 
				       XMPP_VALUE_IQ_AUTH_2,
				       xm->jid->host);
  /* query xmlns= "jabber:iq:auth" */
  Egxp_Message * query = xmpp_message_query (XMPP_VALUE_QUERY_AUTH);
  egxp_message_add_child (iq, query);
  
  /* create username */
  Egxp_Message * username = egxp_message_new (XMPP_TAG_USERNAME);
  egxp_message_append_data (username, xm->jid->user, strlen (xm->jid->user));
  egxp_message_add_child (query, username);
  
  /* create password */
  if(xm->auth && xm->auth->password && xm->auth->stream_id) {
    Egxp_Message * password = egxp_message_new (XMPP_TAG_PASSWORD);
    /* build the digest data */
    sha1_state_t sha1;
    char sha1_hash[20];
    sha1_init(&sha1);
    sha1_append (&sha1, xm->auth->stream_id, strlen (xm->auth->stream_id));
    sha1_append (&sha1, xm->auth->password, strlen (xm->auth->password));
    sha1_finish (&sha1, sha1_hash);
    char sha1_hex[41];
    hex_from_raw (sha1_hash, 20, sha1_hex);
    /* add the data to the password message */
    egxp_message_append_data (password, sha1_hex, 41);
    egxp_message_add_child (query, password);
  } else {
#ifdef XMPP_DEBUG
    printf("DEBUG: xmpp_auth_auth_1_cb -> The auth seems to be null or the password and stream_id are null\n");
#endif
  }
  
  /* try to append resource */
  if (xm->jid->resource) {
    Egxp_Message * resource = egxp_message_new (XMPP_TAG_RESOURCE);
    egxp_message_append_data (resource, xm->jid->resource, strlen (xm->jid->resource));
    egxp_message_add_child (query, resource);
  } else {
#ifdef XMPP_DEBUG
    printf("DEBUG: xmpp_auth_auth_1_cb -> It seems that you haven't define resource\n");
#endif 
  }

  /* now we can try to send the message */
  // Egxp_Connection * conn = EGXP_EXTENSION(xm)->parent->connection;
  //egxp_connection_send_message (conn, iq, 1);
  egxp_message_free (iq);
}
