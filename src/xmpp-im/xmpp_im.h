#ifndef xmpp_im_header
#define xmpp_im_header

#include "xmpp_im_struct.h"
#include "xmpp_im_contact.h"
#include "xmpp_im_roster.h"


#define XMPPIM_REGISTER "__XMPPIM_REGISTER__"


/**
 * Should register the xmpp_im extension
 * @param eg: The egxp structure
 * @return the XmppIM register
 */
XmppIM * xmpp_im_register (Egxp *eg);


/**
 * Create the xmpp structure
 */
XmppIM * xmpp_im_new (Egxp * eg);


/**
 * free the memory used by the XmppIM structure
 */
void xmpp_im_free (XmppIM * x);



#endif
