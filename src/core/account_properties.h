#ifndef account_properties_header_
#define account_properties_header_


/**
 * Define the properties for the Properties page.
 * It contains all parameters available inside the Egxp and its extension
 * We use this structure has temporary variable.
 */
typedef struct _AccountProperties AccountProperties;
#define ACCOUNTPROPERTIES(o) ((AccountProperties*)o)
struct _AccountProperties {
  /* account */
  char * jabber_id;
  char * password;
  char * resource;
  int priority;

  /* connection */
  int port;
  int use_ssl;
  int allow_plaintext;
  int send_keep_alive;
  // manual server host port

  /* details */

  /* preferences */
  int auto_connect;
  int auto_reconnect;
  int log_history;
  int ignore_ssl_warning;
};




AccountProperties * account_properties_new ();
AccountProperties * account_properties_new_from_config (int i);
void account_properties_free (AccountProperties* ap);

#endif
