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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "egxp_message.h"



typedef void (*Handler_Func) (void *data);


/*****************************************************************************/

Egxp_Message * egxp_message_new (char * tag_name) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_new\n");
#endif
  
  Egxp_Message * tmp = (Egxp_Message*) malloc (sizeof (Egxp_Message));
  
  /* copy the tag name */
  tmp->tagname = strdup (tag_name);
  
  tmp->parent = NULL;
  tmp->data = NULL;
  tmp->data_size = 0;
  
  /* initialize list */
  tmp->attributes = ecore_list_new();
  tmp->childs = ecore_list_new();

  /* set destroy callback to the list */
  ecore_list_set_free_cb(tmp->attributes, (Handler_Func)egxp_message_attribute_free);
  ecore_list_set_free_cb(tmp->childs, (Handler_Func)egxp_message_free);
  
  return tmp;
}


void egxp_message_free (Egxp_Message * m) {
  assert (m);
#ifdef EGXP_DEBUG
  char * debug = strdup (m->tagname);
  printf("TRACE: egxp_message_free -> begin: %s\n", debug);
#endif
  
  FREE (m->tagname);
  ecore_list_destroy (m->attributes);
  ecore_list_destroy (m->childs);
  
  /* if attached to a parent, we remove the dependancies */
  if (m->parent) {
    // egxp_message_remove_child (m->parent, m);
  }
  m->parent = NULL;

 IF_FREE (m->data);
  FREE (m);
  
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_free -> end: %s\n", debug);
  FREE (debug);
#endif
}

Egxp_Message * egxp_message_get_child (Egxp_Message *m, char * tagname) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_get_child\n");
#endif

  assert (m != NULL && tagname != NULL);

  ecore_list_goto_first(m->childs);
  Egxp_Message * list_item;
  while((list_item = (Egxp_Message*)ecore_list_next(m->childs)) != NULL) {
    if (strcmp (tagname, list_item->tagname) == 0) {
      return list_item;
    } 
  }
  return NULL;
}

Ecore_List * egxp_message_get_childs (Egxp_Message *m, char * tagname) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_get_childs\n");
#endif

  assert (m != NULL && tagname != NULL);

  Ecore_List * result = ecore_list_new ();

  ecore_list_goto_first(m->childs);
  Egxp_Message * list_item;
  while((list_item = (Egxp_Message*)ecore_list_next(m->childs)) != NULL) {
    if (strcmp (tagname, list_item->tagname) == 0) {
      ecore_list_append (result, list_item);
    } 
  }
  return result;
}


void egxp_message_add_attribute (Egxp_Message *m, Egxp_MessageAttribute * ma) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_add_attribute\n");
#endif
  
  if (m == NULL) return;
  
  ecore_list_append (m->attributes, ma);
}


char * egxp_message_get_attribute (Egxp_Message *m, char * key) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_get_attribute\n");
#endif

  assert (m != NULL && key != NULL);
  
  ecore_list_goto_first(m->attributes);
  Egxp_MessageAttribute * list_item;
  while((list_item = (Egxp_MessageAttribute*)ecore_list_next(m->attributes)) != NULL) {
    if (strcmp (key, list_item->key) == 0)
      return strdup (list_item->value);
  }
  return NULL;
}

void egxp_message_add_child (Egxp_Message *m, Egxp_Message * ma) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_add_child\n");
#endif
  
  if (m == NULL || ma == NULL) return;
  
  ecore_list_append (m->childs, ma);
  ma->parent = m;
}

void egxp_message_remove_child (Egxp_Message *m, Egxp_Message * ma) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_remove_child\n");
#endif

  assert (m != NULL && ma != NULL);

  ecore_list_goto_first(m->childs);
  Egxp_Message * list_item;
  while((list_item = EGXP_MESSAGE(ecore_list_next(m->childs))) != NULL) {
    if (ma == list_item) {
      ecore_list_remove (m->childs);
      return;
    } 
  }
}


void egxp_message_append_data (Egxp_Message *m, char * data, unsigned int size) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_append_data\n");
#endif

  assert (m!= NULL);

  // i think we can just use realloc ... but i'm not sure about strcat 
  /*if (m->data == NULL) {
    m->data = (char*) calloc (size, sizeof (char));
    memset (m->data, 0, size);
  } else {
    m->data = realloc (m->data, size * sizeof (char) );
  }
  m->data_size += size;
  m->data = strncat (m->data, data, size);*/

  m->data = (char *) realloc (m->data, (size + m->data_size) * sizeof(char));
  char * p = m->data + m->data_size;
  strncpy (p, data, size);
  m->data_size += size;
}


char * egxp_message_get_data (Egxp_Message *m) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_get_data\n");
#endif

  assert (m != NULL);
  
  /* if there is no data we return NULL */
  if (m->data == NULL) return NULL;
  
  char * buf = (char*) malloc ((m->data_size + 1) * sizeof (char));
  strncpy (buf, m->data, m->data_size);
  
  return buf;
}


char * egxp_message_to_xml (Egxp_Message *m, unsigned int endtag) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_to_xml\n");
#endif

  int buf_len, len;
  char * buf;

  if (m == NULL) return NULL;

  // "<tagname " + 3 -> \0
  len = strlen (m->tagname) + 3;
  buf = (char*) calloc (len, sizeof (char));
  buf = memset (buf, 0, len); 
  buf = strncat (buf, "<", 1);
  buf = strncat (buf, m->tagname, strlen (m->tagname));
  buf = strncat (buf, " ", 1);
  buf_len = len;
  
  ecore_list_goto_first(m->attributes);
  Egxp_MessageAttribute * list_item;
  while((list_item = (Egxp_MessageAttribute*)ecore_list_next(m->attributes)) != NULL) {
    // "key=value " +4 (don't forget "")
    // printf("DEBUG XML ATTRIBUTES: %s=%s\n",list_item->key, list_item->value);
    buf_len += strlen (list_item->key) + strlen (list_item->value) + 4;
    buf = (char*) realloc (buf, buf_len);
    // copy the key
    buf = strncat (buf, list_item->key, strlen (list_item->key));
    buf = strncat (buf, "=\"", 2);
    buf = strncat (buf, list_item->value, strlen (list_item->value));
    buf = strncat (buf, "\" ", 2);
  }
  
  // check if there are childs and no data 
  if (egxp_message_is_empty (m)) {
    // it's empty just add the necessary: "/>"
    if (endtag) {
      buf_len += 2;
      buf = (char*) realloc (buf, buf_len);
      buf = strncat (buf, "/>", 2);
    } else {
      buf_len += 1;
      buf = (char*) realloc (buf, buf_len);
      buf = strncat (buf, ">", 1);
    }
    
    /*buf_len += 2;
    buf = (char*) realloc (buf, buf_len);
    buf = strncat (buf, "/>", 2);*/
  } else {
    
    /* close the current tag before process the children or data */
    buf_len += 1;
    buf = (char*) realloc (buf, buf_len);
    buf = strncat (buf, ">", 1);
    
    if (m->data != NULL) {
      len = m->data_size;
      buf_len += len;
      buf = (char*) realloc (buf, buf_len);
      buf = strncat (buf, m->data, len);
    }
    //
    ecore_list_goto_first(m->childs);
    Egxp_Message * li;
    while((li = (Egxp_Message*)ecore_list_next(m->childs)) != NULL) {
      char * tmp_buf = egxp_message_to_xml (li, 1); // all child has a endtag
      len = strlen (tmp_buf);
      buf_len += len;
      buf = (char*) realloc (buf, buf_len);
      buf = strncat (buf, tmp_buf, len);
      FREE (tmp_buf);
    }
    
    // the termination tag
    if (endtag) {
      len = strlen (m->tagname);
      buf_len += len + 3; // </tagname>
      buf = (char*) realloc (buf, buf_len);
      buf = strncat (buf, "</",2);
      buf = strncat (buf, m->tagname, len);
      buf = strncat (buf, ">",1);
    }
  }
  return buf;
}

void egxp_message_print(Egxp_Message *m) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_print\n");
#endif
  if (m == NULL) return;
  char * buf = egxp_message_to_xml (m, 1);
  printf("%s\n", buf);
  FREE(buf);
}


Egxp_Message * egxp_message_root (Egxp_Message * m) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_root\n");
#endif
  assert (m != NULL);
  
  /* if the parent is null we return this message */
  if (m->parent == NULL) return m;
  /* else we return the root of the parent */
  return egxp_message_root (m->parent);
}



unsigned int egxp_message_is_empty (Egxp_Message *m) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_is_empty\n");
#endif
  assert (m != NULL);
  return (ecore_list_is_empty (m->childs) && m->data == NULL);
}


Egxp_MessageAttribute * egxp_message_attribute_new (char * key, char * value) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_attribute_new\n");
#endif
  assert (key && value);
  
  Egxp_MessageAttribute * tmp = (Egxp_MessageAttribute *) malloc (sizeof (Egxp_MessageAttribute));
  
  tmp->key = strdup (key);
  tmp->value = strdup (value);
  
  return tmp;
}

void egxp_message_attribute_free (Egxp_MessageAttribute * ma) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_message_attribute_free\n");
#endif
  
  assert (ma);

  FREE (ma->key);
  FREE (ma->value);
  FREE (ma);
}
