#include <assert.h>
#include <stdlib.h>
#include "egxp.h"

Egxp * egxp_new () {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_new\n");
#endif
  Egxp * tmp = EGXP(malloc (sizeof(Egxp)));
  tmp->opcodes = egxp_opcode_new ();
  tmp->root = NULL;
  return tmp;
}


void egxp_free (Egxp * e) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_free\n");
#endif
  assert (e);
  egxp_opcode_free (e->opcodes);
  if (e->root) egxp_node_free(e->root);
  free (e);
}
