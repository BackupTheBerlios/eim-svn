#ifndef xmpp_core_header_h_
#define xmpp_core_header_h_

#include "egxp/egxp.h"

/**
 * Here we define the xmpp opcodes
 */
#define XMPP_TAG_STREAM "stream:stream"

#define XMPP_ATT_XMLNS          "xmlns"
#define XMPP_ATT_XMLNS_STREAM   "xmlns:stream"

#define XMPP_VALUE_STREAM_XMLNS          "jabber:client"
#define XMPP_VALUE_STREAM_XMLNS_STREAM   "http://etherx.jabber.org/streams"
#define XMPP_VALUE_STREAM_VERSION        "1.0"



#define XMPP_ATT_TYPE           "type"
#define XMPP_ATT_TO             "to"
#define XMPP_ATT_XMLNS          "xmlns"
#define XMPP_ATT_VERSION        "version"
#define XMPP_ATT_ID             "id"
#define XMPP_ATT_JID            "jid"
#define XMPP_ATT_FROM           "from"
#define XMPP_ATT_NAME           "name"




/**
 * Add the xmpp opcode inside the opcode variable
 * @param opcode: use to store xmpp opcode
 */
void xmpp_opcode_init (Egxp * eg);


#endif
