#ifndef xmpp_struct_header_h_
#define xmpp_struct_header_h_

#include <Ecore_Data.h>

#include "egxp/egxp.h"

typedef struct _Xmpp Xmpp;
#define XMPP(o) ((Xmpp*)o)
struct _Xmpp {
  /* This variable is really important, it's used to destroy itself */
  Egxp_Extension extension;
  
  int t;
};

#endif
