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
 */
Xmpp_Auth * xmpp_auth_new ();


/**
 * Free the authentification structure
 * - free the password
 * - free the stream id
 */
void xmpp_auth_free (Xmpp_Auth * a);



/**
 * Send a message to try to be authenticiate in
 * no SASL mode
 */
void xmpp_auth_msg_no_sasl (struct _Xmpp * x);

#endif
