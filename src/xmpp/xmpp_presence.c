#include <assert.h>
#include <string.h>

#include "egxp/egxp.h"
#include "xmpp_opcode.h"
#include "xmpp_presence.h"

int xmpp_presence_send (Xmpp *x, int show) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_presence_send\n");
#endif

  assert (x);

  /* create a presence message */
  Egxp_Message * message = egxp_message_new (XMPP_TAG_PRESENCE);
  
  /* create show tag */
  Egxp_Message * show_msg = egxp_message_new (XMPP_TAG_PRESENCE_SHOW);
  Egxp_Opcode * opcodes = EGXP_EXTENSION (x)->parent->opcodes;
  assert (opcodes);
  /* append the show value */
  const char * data = egxp_opcode_get_string (opcodes, show);
  egxp_message_append_data (show_msg, (char*)data, strlen (data));
  egxp_message_add_child (message, show_msg);

  /* send the message */
  Egxp_Connection * conn = EGXP_EXTENSION(x)->parent->connection;
  egxp_connection_send_message (conn, message, 1);
  
  return 1;
}
