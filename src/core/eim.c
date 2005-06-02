#include <assert.h>
#include <stdlib.h>
#include "eim.h"


Eim * eim_new () {
#ifdef CORE_DEBUG
  printf("TRACE: eim_new\n");
#endif
  Eim * tmp = EIM(malloc(sizeof(Eim)));
  
  tmp->egxps = ecore_list_new ();
  ecore_list_set_free_cb (tmp->egxps, egxp_free);

  return tmp;
}



void eim_config_init (Eim *e) {
#ifdef CORE_DEBUG
  printf("TRACE: eim_initialize\n");
#endif
  assert (e);

  

}



void eim_free (Eim *e) {
#ifdef CORE_DEBUG
  printf("TRACE: eim_free\n");
#endif
  assert (e);
  
  if (e->egxps!= NULL) ecore_list_destroy (e->egxps);
  FREE (e);
}
