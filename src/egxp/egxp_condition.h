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
#ifndef egxp_condition_header_h_
#define egxp_condition_header_h_

#include "egxp_node_struct.h"

/**
 * Create a egxp condition structure initialized with it parameters
 * @param key: the id of the key
 * @param value: the id of the value
 */
Egxp_Condition * egxp_condition_new (const int key, const int value); 

/**
 * Free the memory of the condition
 */
void egxp_condition_free (Egxp_Condition * condition);

/**
 * Test if the EgxpCondition is equal to the id and the value
 */
unsigned char egxp_condition_equals (Egxp_Condition * condition, const int key, const int value);

 
#endif
