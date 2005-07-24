#ifndef eim_headers_
#define eim_headers_


#include <Ecore_Data.h>

#include "egxp/egxp.h"
#include "account_properties.h"

typedef struct _Eim Eim;
#define EIM(o) ((Eim*)o)

struct _Eim {
  /* need to keep a list of Egxp Structure */
  Ecore_List * egxps;

  /* contains all accounts properties */
  Ecore_List * account_properties;
  
};


/**
 * Allocate the eim structure
 * - initialize the egxps list
 */
Eim * eim_new ();


/**
 * Initialize the eim strutcure
 * - try to read the configuration file
 */
void eim_config_init (Eim *e);


/**
 * Free the eim structure
 */
void eim_free (Eim *e);


/**
 * Initialize the Egxp from an account properties
 */
Egxp * eim_create_egxp_from (AccountProperties * ap);


#endif
