#ifndef header_xmpp_im_struct_header
#define header_xmpp_im_struct_header

#include <Ecore_Data.h>

#include "xmpp/xmpp_jid.h"

typedef struct _XmppIM_Contact XmppIM_Contact;
#define XMPPIM_CONTACT(o) ((XmppIM_Contact*)o)
struct _XmppIM_Contact {
  
  /* the jid of the contact */
  Xmpp_JID * jid;
  
  /* the name of the contact */
  char * name;

  /* List of group reference */
  Ecore_List * groups;
};


/**
 *  This is the definition of the roster. The roster is composed of 
 *  different group. By default we created a group called __default__group__.
 *  So each user who has no group must be inside this one.
 */
typedef struct _XmppIM_Roster  XmppIM_Roster;
#define XMPPIM_ROSTER(o) ((XmppIM_Roster*)o)
struct _XmppIM_Roster {
  
  /* a hash structure to store group, key is group name, the value
     is a reference on the XmppIM_Contact
  */
  Ecore_Hash * groups;
  
  /** 
   * Keep a hash on the XmppIM_Contact, the key is the bare id 
   */
  Ecore_Hash * users;  
};



typedef struct _XmppIM_RosterGroup XmppIM_RosterGroup;
#define XMPPIM_ROSTERGROUP(o) ((XmppIM_RosterGroup*)o)
struct _XmppIM_RosterGroup {
  
  /* group name*/
  char * groupname;
  
  /* contains a list of XmppIM_Contact element*/
  Ecore_List * users;
};


#endif
