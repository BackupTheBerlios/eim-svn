#include <assert.h>
#include <stdio.h>

#include "egxp_condition.h"

Egxp_Condition * egxp_condition_new (const unsigned int key, const unsigned int value) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_condition_new\n");
#endif
  Egxp_Condition * tmp = (Egxp_Condition*) malloc (sizeof (Egxp_Condition));
  tmp->key = key;
  tmp->value = value;
  return tmp;
}

void egxp_condition_free (Egxp_Condition * condition) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_condition_free\n");
#endif

  assert (condition != NULL);
  
  free (condition);
}


unsigned char egxp_condition_equals (Egxp_Condition * condition, const unsigned int key, const unsigned int value) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_condition_equals\n");
#endif

  assert (condition != NULL);

  return condition->key == key && condition->value == value;
}
