#ifndef eim_headers_
#define eim_headers_


#include <Ecore_Data.h>

#include "egxp/egxp.h"


typedef struct _Eim Eim;
#define EIM(o) ((Eim*)o)

struct _Eim {
  /* need to keep a list of Egxp Structure */
  Ecore_List * egxps;

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


#endif
