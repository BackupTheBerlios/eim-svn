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
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Ecore_Data.h>

#include "xmpp_jid.h"


Xmpp_JID * xmpp_jid_new (char * user, char * host, char * resource) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_new\n");
#endif 
  
  Xmpp_JID * tmp = XMPP_JID(malloc (sizeof(Xmpp_JID)));
  
  tmp->user = strdup (user);
  tmp->host = strdup (host);
  tmp->resource = resource?strdup (resource):NULL;

  return tmp;
}


void xmpp_jid_free (Xmpp_JID * jid) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_free\n");
#endif 
  assert (jid);

  IF_FREE (jid->user);
  IF_FREE (jid->host);
  IF_FREE (jid->resource);

  FREE (jid);
}

Xmpp_JID * xmpp_jid_new_from_bare (char * jidbar) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_new_from_bar\n");
#endif 
  assert (jidbar);
  Xmpp_JID * tmp = XMPP_JID(malloc (sizeof(Xmpp_JID)));

  /* split the jidbare in two parts */
  char * at = strchr (jidbar, '@');
  char * slash = strchr (jidbar, '/');

  /* check if there is a name */
  if (at != NULL) {
    tmp->user = strndup ((const char*)jidbar, (size_t) (((int)at) - ((int)jidbar)) / sizeof (char));
    at = (at+1);
  } else {
    tmp->user = strdup("");
    at = jidbar;
  }

  /* set the host */
  if (slash == NULL) {
    tmp->host = strdup ((char*) at);
    tmp->resource = strdup ("");
  } else {
    /* set the host */
    tmp->host = strndup ((const char*) at, (size_t) (((int)slash) - ((int)at)) / sizeof(char));
    tmp->resource = strdup((const char*) (slash + 1));
  }

  return tmp;
}

char * xmpp_jid_get_bar (Xmpp_JID * jid) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_get_bar\n");
#endif 
  assert (jid);
  
  /* compute the size user@host\0 */
  unsigned int u = jid->user?strlen (jid->user):0;
  unsigned int h = jid->host?strlen (jid->host):0;
  
  /* initialize the structre */
  char * tmp = (char*) malloc ( (u + h + 2) * sizeof (char));
  tmp = strncpy (tmp, jid->user, u);
  tmp[u] = '@';
  strncpy (tmp + ((u+1) * sizeof (char)), jid->host, h);
  tmp [u + h + 1] = '\0';
  
  return tmp;
}


char * xmpp_jid_get_full (Xmpp_JID * jid) {
 #ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_get_full\n");
#endif 
  assert (jid);
  
  /* compute the size user@host/resource\0 */
  unsigned int u = jid->user?strlen (jid->user):0;
  unsigned int h = jid->host?strlen (jid->host):0;
  unsigned int r = jid->resource?strlen (jid->resource):0;
  
  /* initialize the structre */
  char * tmp = (char*) malloc ( (u + h + r + 3) * sizeof (char));
  tmp = strncpy (tmp, jid->user, u);
  tmp[u] = '@';
  strncpy (tmp + ((u+1) * sizeof (char)), jid->host, h);
  tmp[u + 1 + h] = '/';
  strncpy (tmp + ((u + 2 + h) * sizeof (char)), jid->resource, r);
  tmp [u + h + r + 2] = '\0';
  
  return tmp;
}
