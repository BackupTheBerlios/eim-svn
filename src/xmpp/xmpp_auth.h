#ifndef xmpp_auth_header_h_
#define xmpp_auth_header_h_

struct _Xmpp;

/**
 * This structure and set of functions should 
 * manage the authentification step of the jabber protocol.
 */
typedef struct _Xmpp_Auth Xmpp_Auth;
#define XMPP_AUTH(o) ((Xmpp_Auth*)o)
struct _Xmpp_Auth {
  
  /* store the password */
  char * password;

  /* store the stream id */
  char * stream_id;
};


/**
 * Initialize the structure
 * @return the newly allocated structure
 */
Xmpp_Auth * xmpp_auth_new ();


/**
 * Free the authentification structure
 * - free the password
 * - free the stream id
 * @param a: The Authentification structure to be freed.
 */
void xmpp_auth_free (Xmpp_Auth * a);



/**
 * Send a message to try to be authenticiate in
 * no SASL mode
 * @param x: The Xmpp structure
 */
void xmpp_auth_msg_no_sasl (struct _Xmpp * x);


/**
 * This method is called when the server return the response
 * of the query auth_1 (the first step of the non-sasl auth).
 * @param msg: The message
 * @param eg: The Egxp object
 */
void xmpp_auth_auth_1_cb (Egxp_Message * msg, void * eg);

#endif
