#include "xmpp_callback.h"


void xmpp_callback_stream_begin_cb (Egxp_Message * msg, void * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_callback_stream_begin_cb\n");
#endif 
  assert (msg && eg);
  
  
}
