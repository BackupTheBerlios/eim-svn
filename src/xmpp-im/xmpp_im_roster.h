#ifndef header_xmpp_im_roster_h_
#define header_xmpp_im_roster_h_

#include "egxp/egxp_message.h"
#include "xmpp_im_struct.h"

/**
 * Create a new roster object
 * - initialize the group hash map
 * - initialize the users hash map
 * @return: the newly created roster
 */
XmppIM_Roster * xmpp_im_roster_new ();


/**
 * Delete a roster
 * - free all memory used by the roster
 * - remove all groups and all users
 * @param r: the roster to be freed
 */
void xmpp_im_roster_free (XmppIM_Roster * r);


/**
 * Add a group to the roster
 * @param r: the roster
 * @param g: the group to add
 */
void xmpp_im_roster_add_group (XmppIM_Roster * r, XmppIM_RosterGroup * g);

/**
 * Add a contact to the roster.
 * - add the contact inside the user hashmap
 * - this function do nothing about group of the contact.
 */
void xmpp_im_roster_add_contact (XmppIM_Roster * r, XmppIM_Contact * c);


/**
 * Remove a contact from the roster,
 * - remove all attached group of the xmpp_im_contact.
 * @param r: the roster
 * @param c: the contact to remove.
 * @warning: the contact are not freed.
 */
void xmpp_im_roster_remove_contact (XmppIM_Roster * r, XmppIM_Contact * c);


/**
 * Return the contact structure in function of the jid bare
 * @param r: the roster
 * @param jid: the bare jid of the searched user 
 */
XmppIM_Contact * xmpp_im_roster_get_contact (XmppIM_Roster *r, char * jid);


/**
 * Add a contact to a group:
 *  - update the group list of the contact
 *  - if the group doesn't exist in the roster, create it and add the XmppIM_Contact inside
 * @param r: The roster,
 * @param c: contact to add to the group,
 * @param groupname: the name of the group.
 * @return: return the group on which we have added 
 */
XmppIM_RosterGroup * xmpp_im_roster_add_contact_to_group (XmppIM_Roster *r, XmppIM_Contact * c, char *groupname);


/**
 * This method display the roster in the stdout stream.
 * @param r: The concern roster.
 */
void xmpp_im_roster_display (XmppIM_Roster *r);


/**
 * Create a group
 */
XmppIM_RosterGroup * xmpp_im_roster_group_new (char * groupname);



/**
 * Delete a group
 */
void xmpp_im_roster_group_free (XmppIM_RosterGroup * );


/**
 * Remove the contact from the roster group. This function doesn't remove
 * the reference of the user to this group.
 */
void xmpp_im_roster_group_remove_contact (XmppIM_RosterGroup * rg, XmppIM_Contact * ec);


/**
 * Add a contact to a group
 * - update the contact group list
 * - update the group
 */
void xmpp_im_roster_group_add_contact (XmppIM_RosterGroup * rg, XmppIM_Contact *ec);


/**
 * This function update the roster from a message. The message must be a 
 * iq message. Next we get all contact from this message and update 
 * their status.
 * @param r: the concern roster
 * @param m: the message that contains all information.
 */
void xmpp_im_roster_update_from_message (XmppIM_Roster *r, Egxp_Message *m);


/**
 * This method display the group roster information in the stdout stream.
 * @param r: The concern roster group.
 */
void xmpp_im_roster_group_display (void * i, void * user_data);
#endif
