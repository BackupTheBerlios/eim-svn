#include <stdio.h>

#include "egxp/egxp.h"
#include "xmpp.h"

int main (int argc, char ** argv) {
  
  /* create the protocol grammar */
  Egxp * eg = egxp_new ();
  
  /* init opcode */
  xmpp_register (eg);

  /* display opcode */
  egxp_opcode_display (eg->opcodes);
  
  /* free opcode */
  egxp_free (eg);
  
  return 0;
}
