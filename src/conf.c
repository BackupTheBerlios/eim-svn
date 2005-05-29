#include <assert.h>
#include "Ecore_Config.h"
#include "conf.h"


/**
 * Initialize the config.
 * @param eg: the Egxp structure
 */
int eim_config_init (Egxp * eg) {
  assert (eg);

  if (ecore_config_init ("eim") == ECORE_CONFIG_ERR_FAIL) {
    printf("WARNING: config file not available\n");
  }
  
  // load default config

  // save in order to have config object
  eim_config_save ();

  return 1;
}


/**
 * Save the configuration
 */
void eim_config_save () {
  ecore_config_save ();
}


void eim_config_shutdown () {
  eim_config_save ();
  ecore_config_shutdown ();
}
