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
#include <stdio.h>
#include <stdlib.h>
#include <Ecore_Data.h>

#include "egxp_condition.h"

Egxp_Condition * egxp_condition_new (const int key, const int value) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_condition_new\n");
#endif
  Egxp_Condition * tmp = (Egxp_Condition*) malloc (sizeof (Egxp_Condition));
  tmp->key = key;
  tmp->value = value;
  return tmp;
}

void egxp_condition_free (Egxp_Condition * condition) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_condition_free\n");
#endif

  assert (condition != NULL);
  
  FREE (condition);
}


unsigned char egxp_condition_equals (Egxp_Condition * condition, const int key, const int value) {
#ifdef EGXP_DEBUG
  printf("TRACE: egxp_condition_equals\n");
#endif

  assert (condition != NULL);

  return condition->key == key && condition->value == value;
}
