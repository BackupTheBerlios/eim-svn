#ifndef xmpp_header_h_
#define xmpp_header_h_

#include "egxp/egxp.h"

#include "xmpp_struct.h"
#include "xmpp_opcode.h"
#include "xmpp_callback.h"


#define XMPP_REGISTER "__XMPP_REGISTER__"

/**
 * Register the xmpp protocol
 *  - initialize the xmpp structure
 *  - register opcode and protocol node
 * @param eg: The Egpx structure
 */
void xmpp_register (Egxp * eg);


/**
 * Initialize the xmpp structure.
 */
Xmpp * xmpp_new (Egxp * eg);


/**
 * Free memory
 */
void xmpp_free (Xmpp * x);

#endif
