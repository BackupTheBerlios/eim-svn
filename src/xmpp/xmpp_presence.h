#ifndef xmpp_presence_header
#define xmpp_presence_header

#include "xmpp_struct.h"


/**
 * This method try to send a presence message with the show 
 * information
 * @param x: The xmpp
 * @param show: The show value.
 */
int xmpp_presence_send (Xmpp *x, int show);



#endif
