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
#include "xmpp_im.h"



XmppIM * xmpp_im_register (Egxp *eg) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_register\n");
#endif
  assert (eg);

  /* register xmpp_im opcode */
  xmpp_im_opcode_init (eg);

  /* add the xmppim_register */
  int id = egxp_opcode_add (eg->opcodes, XMPPIM_REGISTER);
  XmppIM * tmp = xmpp_im_new (eg);
  
  /* register the xmpp_im protocole */
  egxp_extension_register (eg, id, tmp);
  
  return tmp;
}


XmppIM * xmpp_im_new (Egxp * eg) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_new\n");
#endif
  assert (eg);

  /* allocate the structure */
  XmppIM * tmp = XMPPIM (malloc(sizeof (XmppIM)));
  
  /* define the destroy function */
  tmp->extension.destroy = ECORE_FREE_CB(xmpp_im_free);
  
  /* allocate the roster */
  tmp->roster = xmpp_im_roster_new ();
  
  /* return the structure */
  return tmp;
}


void xmpp_im_free (XmppIM * x) {
#ifdef XMPPIM_DEBUG
  printf("TRACE: xmpp_im_free\n");
#endif
  assert (x);
 
  /* deallocate the roster */
  if (x->roster) xmpp_im_roster_free (x->roster);
  
  FREE (x);
}
