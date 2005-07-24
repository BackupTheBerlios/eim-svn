#include <assert.h>
#include <stdlib.h>
#include "Ecore_Config.h"

#include "xmpp/xmpp.h"
#include "xmpp-im/xmpp_im.h"

#include "account_properties.h"
#include "eim.h"
 

#define EIM_CONFIG_NB_ACCOUNT "nb_account"


/**
 * Call this method to initialize 
 * the default config (called when there is
 * no config file 
 */
void _eim_load_default_config () {
  ecore_config_int_default(EIM_CONFIG_NB_ACCOUNT, 0);
}


Eim * eim_new () {
#ifdef CORE_DEBUG
  printf("TRACE: eim_new\n");
#endif
  /* create the eim object */
  Eim * tmp = EIM(malloc(sizeof(Eim)));
  
  /* allocates the lists of egxp object */
  tmp->egxps = ecore_list_new ();
  ecore_list_set_free_cb (tmp->egxps, egxp_free);

  /* allocates the list of properties accounts */
  tmp->account_properties = ecore_list_new ();
  ecore_list_set_free_cb (tmp->account_properties, account_properties_free);
  
  /* return the newly created object */
  return tmp;
}



void eim_config_init (Eim *e) {
#ifdef CORE_DEBUG
  printf("TRACE: eim_initialize\n");
#endif
  assert (e);

  int nb_account = 0;
  int i;
  
  /* read config file to get account properties */
  if (ecore_config_init ("eim") == ECORE_CONFIG_ERR_FAIL) {
    printf("WARNING: config file not available\n");
    /* load default config and save it*/
    _eim_load_default_config ();
    ecore_config_save ();
  }
  
  /* here we can load each configuration */
  ecore_config_load();
  nb_account = ecore_config_int_get(EIM_CONFIG_NB_ACCOUNT);
  for (i = 0; i < nb_account; i++) {
    ecore_list_append (e->account_properties, 
		       account_properties_new_from_config (i));
  }
}



void eim_free (Eim *e) {
#ifdef CORE_DEBUG
  printf("TRACE: eim_free\n");
#endif
  assert (e);
  
  if (e->egxps!= NULL) ecore_list_destroy (e->egxps);
  if (e->account_properties) ecore_list_destroy (e->account_properties);

  FREE (e);
}


Egxp * eim_create_egxp_from (AccountProperties * ap) {
#ifdef CORE_DEBUG
  printf("TRACE: eim_create_egxp_from\n");
#endif
  assert (ap);

  /* create egxp */
  Egxp * eg = egxp_new ();
  
  /* add protocol to egxp */
  Xmpp * xm = xmpp_register (eg);
  XmppIM * xmppim = xmpp_im_register (eg);
  
  
  /********************************************/
  /* set the properties to the egxp structure */
  /********************************************/

  /* set jid (user/host/resource) */
  xm->jid = xmpp_jid_new_from_bare (ap->jabber_id);
  xmpp_jid_set_resource (xm->jid, ap->resource);

  /* password */
  xm->auth = xmpp_auth_new_with_passwd (ap->password);
  
  /* define the connection parameters (host/port/ssl) */
  eg->connection = egxp_connection_new ( xm->jid->host, ap->port, ap->use_ssl);
  eg->connection->ignore_ssl_warning = ap->ignore_ssl_warning;
  eg->connection->send_keep_alive = ap->send_keep_alive;
  eg->connection->auto_connect = ap->auto_connect;
  eg->connection->auto_reconnect = ap->auto_reconnect;

  return eg;
}
