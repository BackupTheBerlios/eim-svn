#include <stdio.h>
#include <assert.h>
#include "xmpp.h"


void xmpp_register (Egxp * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_register\n");
#endif

  assert (eg);
  
  /* register opcode */
  xmpp_opcode_init (eg);
  /* initialize the Egxp Structure */
  int id = egxp_opcode_add (eg->opcodes, XMPP_REGISTER);
  Xmpp * tmp = xmpp_new (eg);
  /* register the structure */
  egxp_extension_register (eg, id, tmp);
}



Xmpp * xmpp_new (Egxp * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_new\n");
#endif

  assert (eg);
  
  /* allocate the structure */
  Xmpp * tmp = XMPP (malloc(sizeof (Xmpp)));
  
  /* define the destroy function */
  tmp->extension.destroy = ECORE_FREE_CB(xmpp_free);
  
  /* return the xmpp */
  return tmp;
}


void xmpp_free (Xmpp * x) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_free\n");
#endif
  
  assert (x);
  
  FREE (x);
}
