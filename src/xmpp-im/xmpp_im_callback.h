#ifndef xmpp_im_callback_header
#define xmpp_im_callback_header

#include "egxp/egxp_message.h"

/**
 * This callback is called when the authentification has been accepted.
 * It try to send a roster request to fill the roster.
 * @param msg: The authentification message.
 * @param data: The egxp structure.
 */
void xmpp_im_callback_roster_init(Egxp_Message * msg, void* data);


/**
 * This callback is called when the request roster has been accepted.
 * So this method try to populate the roster.
 * @param msg: a message with the request acceptation
 * @param data: the egxp structure
 */
void xmpp_im_callback_roster_populate(Egxp_Message * msg, void* data);
#endif
