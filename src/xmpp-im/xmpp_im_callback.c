#include <assert.h>
#include <stdio.h>
#include "xmpp_im_callback.h"



void xmpp_im_callback_roster_init(Egxp_Message *msg, void* data) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_callback_roster_init\n");
#endif
  assert (msg && data);

  printf("Callback Roster\n");
}
