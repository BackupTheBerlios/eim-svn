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
#include <assert.h>
#include "xmpp.h"


Xmpp * xmpp_register (Egxp * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_register\n");
#endif

  assert (eg);
  
  /* register opcode */
  xmpp_opcode_init (eg);
  /* initialize the Egxp Structure */
  int id = egxp_opcode_add (eg->opcodes, XMPP_REGISTER);
  Xmpp * tmp = xmpp_new (eg);
  /* register the structure */
  egxp_extension_register (eg, id, tmp);
  
  return tmp;
}



Xmpp * xmpp_new (Egxp * eg) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_new\n");
#endif

  assert (eg);
  
  /* allocate the structure */
  Xmpp * tmp = XMPP (malloc(sizeof (Xmpp)));
  
  /* define the destroy function */
  tmp->extension.destroy = ECORE_FREE_CB(xmpp_free);

  /* set the user name */
  tmp->jid = NULL;

  /* return the xmpp */
  return tmp;
}


void xmpp_free (Xmpp * x) {
#ifdef XMPP_DEBUG
  printf("TRACE: xmpp_free\n");
#endif
  
  assert (x);

  if (x->jid) xmpp_jid_free(x->jid);
  
  FREE (x);
}
