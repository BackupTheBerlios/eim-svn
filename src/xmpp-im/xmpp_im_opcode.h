#ifndef xmpp_im_opcode_header_
#define xmpp_im_opcode_header_

#include "egxp/egxp.h"


#define XMPP_IM_VALUE_IQ_ROSTER_REQUEST   "roster_request"
#define XMPP_IM_VALUE_QUERY_ROSTER        "jabber:iq:roster" 

#define XMPP_IM_TAG_ITEM		  "item"
#define XMPP_IM_TAG_GROUP                 "group"


/**
 * Initialize all opcode of the xmpp_im protocol
 * @param eg: The egxp structure
 */
void xmpp_im_opcode_init (Egxp *eg);





#endif
