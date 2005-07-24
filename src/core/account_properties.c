#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Ecore_Config.h"
#include "account_properties.h"

#define EIM_ACCOUNT_PROP              "account"

#define EIM_ACCOUNT_PROP_JABBER_ID    "jabber_id"
#define EIM_ACCOUNT_PROP_PASSWORD     "password"
#define EIM_ACCOUNT_PROP_RESSOURCE    "resource"
#define EIM_ACCOUNT_PROP_PRIORITY     "priority"

#define EIM_ACCOUNT_PROP_PORT         "port"
#define EIM_ACCOUNT_PROP_USE_SSL      "use_ssl"
#define EIM_ACCOUNT_PROP_ALLOW_PLAINTEXT "plain_text"
#define EIM_ACCOUNT_PROP_SEND_KEEP_ALIVE "send_keep_alive"

#define EIM_ACCOUNT_PROP_AUTO_CONNECT   "auto_connect"
#define EIM_ACCOUNT_PROP_AUTO_RECONNECT "auto_reconnect"
#define EIM_ACCOUNT_PROP_LOG_HISTORY    "log_history"
#define EIM_ACCOUNT_PROP_IGNORE_SSL_WARNING "ignore_ssl_warning"

AccountProperties * account_properties_new () {
#ifdef CORE_DEBUG
  printf("TRACE: account_properties_new\n");
#endif
  AccountProperties * tmp = ACCOUNTPROPERTIES(malloc (sizeof(AccountProperties)));
  memset (tmp, 0, sizeof (AccountProperties));
  
  return tmp;
}


AccountProperties * account_properties_new_from_config (int i) {
#ifdef CORE_DEBUG
  printf("TRACE: account_properties_new_from_config\n");
#endif
  assert (i > -1);

#define BUF_SIZE 250
  char buf[BUF_SIZE + 5];
  
  AccountProperties * tmp = account_properties_new ();
  
  
  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	   EIM_ACCOUNT_PROP_JABBER_ID);
  tmp->jabber_id = ecore_config_string_get(buf);
  
  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	   EIM_ACCOUNT_PROP_PASSWORD);
  tmp->password = ecore_config_string_get(buf);

  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	   EIM_ACCOUNT_PROP_RESSOURCE);
  tmp->resource = ecore_config_string_get(buf);
  
  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_PRIORITY);
  tmp->priority = ecore_config_int_get(buf);

  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	   EIM_ACCOUNT_PROP_PORT);
  tmp->port = ecore_config_int_get(buf);
  

  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_USE_SSL);
  tmp->use_ssl = ecore_config_int_get(buf);
  
  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_ALLOW_PLAINTEXT);
  tmp->allow_plaintext = ecore_config_int_get(buf);

  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_SEND_KEEP_ALIVE);
  tmp->send_keep_alive = ecore_config_int_get(buf);
  
  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_AUTO_CONNECT);
  tmp->auto_connect = ecore_config_int_get(buf);

  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_AUTO_RECONNECT);
  tmp->auto_reconnect = ecore_config_int_get(buf);

  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_LOG_HISTORY);
  tmp->log_history = ecore_config_int_get(buf);
  
  snprintf(buf, BUF_SIZE, "%s/%d/%s\0", EIM_ACCOUNT_PROP, i,
	  EIM_ACCOUNT_PROP_IGNORE_SSL_WARNING);
  tmp->ignore_ssl_warning = ecore_config_int_get(buf);
  
  return tmp;
}


void account_properties_free (AccountProperties* ap) {
#ifdef CORE_DEBUG
  printf("TRACE: account_properties_free\n");
#endif

  assert (ap);

  IF_FREE (ap->jabber_id);
  IF_FREE (ap->password);
  IF_FREE (ap->resource);

  FREE (ap);
}
