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
  
  tmp->user = user?strdup (user):NULL;
  tmp->host = host?strdup (host):NULL;
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
    int t = at - jidbar;
    tmp->user = (char*) malloc ( (t+1) * sizeof(char));
    tmp->user = strncpy (tmp->user, jidbar, t);
    tmp->user[t] = '\0';
    at = (at+1);
  } else {
    tmp->user = NULL; //strdup("");
    at = jidbar;
  }

  /* set the host */
  if (slash == NULL) {
    tmp->host = strdup ((char*) at);
    tmp->resource = NULL;
  } else {
    /* set the host */
    int t = (size_t) (((int)slash) - ((int)at)) / sizeof(char);
    tmp->host = (char*) malloc ((t+1) * sizeof (char));
    tmp->host = strncpy (tmp->host, at, t);
    tmp->host[t] = '\0';
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
  
  if (jid->user) {
    /* allocate user + '@' + host + '\0' */
    char * tmp = (char*) malloc ( (u + h + 2) * sizeof (char));
    tmp = strncpy (tmp, jid->user, u);
    tmp[u] = '@';
    strncpy (tmp + ((u+1) * sizeof (char)), jid->host, h);
    tmp [u + h + 1] = '\0';
    return tmp;
  }
  
  return strdup (jid->host);
}


char * xmpp_jid_get_full (Xmpp_JID * jid) {
 #ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_get_full\n");
#endif 
  assert (jid);
  
  /* compute the size user@host/resource\0 */
  // unsigned int u = jid->user?strlen (jid->user):0;
  // unsigned int h = jid->host?strlen (jid->host):0;
  unsigned int r = jid->resource?strlen (jid->resource):0;
  
  /* initialize the structre */
  /*  char * tmp = (char*) malloc ( (u + h + r + 3) * sizeof (char));
  tmp = strncpy (tmp, jid->user, u);
  tmp[u] = '@';
  strncpy (tmp + ((u+1) * sizeof (char)), jid->host, h);
  tmp[u + 1 + h] = '/';
  strncpy (tmp + ((u + 2 + h) * sizeof (char)), jid->resource, r);
  tmp [u + h + r + 2] = '\0';
  */
  
  
  if (r) {
    char * tmp =  xmpp_jid_get_bar (jid);
    int idx = strlen (tmp);
    char * tmp2 = (char*) malloc ( (idx + r + 1) * sizeof (char));
    strcpy (tmp2, tmp);
    strcpy (tmp2 + idx, jid->resource);
    tmp2[idx + r ] = '\0';
    free (tmp);
    return tmp2;
  }

  
  return xmpp_jid_get_bar (jid);
}


unsigned int xmpp_jid_has_user (Xmpp_JID * jid) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_jid_has_user\n");
#endif 
  assert (jid);
  return jid->user != NULL;
}
