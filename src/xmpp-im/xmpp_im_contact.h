#ifndef xmpp_im_contact_headers
#define xmpp_im_contact_headers


#include <Ecore_Data.h>

#include "xmpp/xmpp_jid.h"
#include "xmpp_im_struct.h"

/**
 * Create a new contact.
 * @param jid: The jid of the user
 * @param name: The name of the user
 */
XmppIM_Contact * xmpp_im_contact_new (Xmpp_JID * jid, char * name);


/**
 * Free the parameters.
 */
void xmpp_im_contact_free (XmppIM_Contact * contact);


/**
 * Remove all group of the contact. This function update the group
 * contact list of each group.
 * @param c: the contact
 */
void xmpp_im_contact_remove_all_group (XmppIM_Contact * c);



/**
 * Display information about contact in the stdout stream
 * @param c: the contact to display
 */
void xmpp_im_contact_display (void *c, void * user_data);

#endif
