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
#ifndef header_egxp_message_h
#define header_egxp_message_h

#include <Ecore_Data.h>

typedef struct _Egxp_Message Egxp_Message;

struct _Egxp_Message {
  
  /* the tag name */
  char * tagname;

  /* data */
  char * data;
  unsigned int data_size;

  /* parent */
  Egxp_Message * parent;

  /* the attributes list */
  Ecore_List * attributes;
  
  /* the child nodes */
  Ecore_List * childs;
};

#define EGXP_MESSAGE(o) ((Egxp_Message*)o)


typedef struct _Egxp_MessageAttribute {
  char * key;
  char * value;
} Egxp_MessageAttribute;

#define EGXP_MESSAGEATTRIBUTE(o) ((Egxp_MessageAttribute*)o)

/**************************************************************************/

/**
 * Create and initialize the message structure.
 * 
 * @param tag_name: The name of the tag
 * 
 * @return: The newly created message
 */
Egxp_Message * egxp_message_new (char * tag_name);


/**
 * Free a Egxp_Message.
 *
 * @param m: The message to free
 */
void egxp_message_free (Egxp_Message * m);


/**
 * Add an attribute element to the message.
 *
 * @param m: The target message
 * @param ma: The attribute to add to the message.
 */
void egxp_message_add_attribute (Egxp_Message *m, Egxp_MessageAttribute * ma); 

/**
 * Return an attribute designed by the key from the message.
 * The caller must free the return value.
 *
 * @param m: The message that contains attributes
 * @param key: The attribute name
 * 
 * @return: The value of the attribute, don't forget to free it after used.
 */
char * egxp_message_get_attribute (Egxp_Message *m, char * key);


/**
 * Add a child to a message, a child is another message.
 * The parent is responsible to delete the child.
 *
 * @param m: The parent message
 * @param ma: The child message.
 */
void egxp_message_add_child (Egxp_Message *m, Egxp_Message * ma);


/**
 * Remove a child from the parent message but does not free it.
 * 
 * @param m: The parent message
 * @param ma: The child message
 */
void egxp_message_remove_child (Egxp_Message *m, Egxp_Message * ma);


/**
 * Check if the message a not data and not child.
 *
 * @param m: The message to be tested
 * 
 * @return true if the message has no data and no child, false otherwise.
 */
unsigned int egxp_message_is_empty (Egxp_Message *m);


/**
 * Return the first child with its tag name equals to the tagname parameter.
 *
 * @param m: The parent message
 * @param tagname: The tag used to search the first message with this tag
 *
 * @return: the first child found, otherwise return NULL.
 */
Egxp_Message * egxp_message_get_child (Egxp_Message *m, char * tagname);


/**
 * Return a list with all direct child of the message with the tagname
 * passed as parameter. Do not forget to free the list after used.
 *
 * @param m: The parent message.
 * @param tagname: The tag used to search the first message with this tag.
 *
 * @return: the list with all element with the parameter as tagname.
 */
Ecore_List * egxp_message_get_childs (Egxp_Message *m, char * tagname);


/**
 * Append data (text data) to the message.
 * 
 * @param m: The target message.
 * @param data: The data to add to the message
 * @param size: The size of the data.
 */
void egxp_message_append_data (Egxp_Message *m, char * data, unsigned int size);


/**
 * Return the data inside this message
 * @param m: the message.
 * @return: a new buffer with data, so don't forget to delete it.
 */
char * egxp_message_get_data (Egxp_Message *m);


/**
 * return the xml stream associated. The returned stream is stored 
 * in utf-8
 */
char * egxp_message_to_xml (Egxp_Message *m, unsigned int endtag);

/**
 * Display the xml representation of the message
 * @param m: The message to display
 */
void egxp_message_print(Egxp_Message *m);

/**
 * Return the root message.
 * @param m: a message
 * @return the root message or null if no message.
 */
Egxp_Message * egxp_message_root (Egxp_Message * m);




/**
 * Create a Egxp_MessageAttribute
 */
Egxp_MessageAttribute * egxp_message_attribute_new (char * key, char * value);

/**
 * Free the MessageAttribute structure
 */
void egxp_message_attribute_free (Egxp_MessageAttribute * ma);

#endif
