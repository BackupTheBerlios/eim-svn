/*
   $Id$

   Copyright (C) 2005 Joël Vennin < joel.vennin _@_ gmail _dot_ com >
   Part of the Eim Project http://eim.berlios.de

   Eim is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   Eim is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Eim; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef header_xmpp_im_struct_header
#define header_xmpp_im_struct_header

#include <Ecore_Data.h>

#include "egxp/egxp.h"
#include "xmpp/xmpp_jid.h"


/**
 * This structure defines what is a contact. A contact is associated 
 * to a jid and a list of group. A contact can be in several groups.
 * The name field is the pseudo of the contact.
 */
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



/**
 * This structure contains all variable associated to 
 * the xmpp-im extension.
 */
typedef struct _XmppIM XmppIM;
#define XMPPIM(o) ((XmppIM*)o)
struct _XmppIM {
  /* This variable is really important, it's used to destroy itself */
  Egxp_Extension extension;

  /* the roster */
  XmppIM_Roster * roster;
  
  
};

#endif
