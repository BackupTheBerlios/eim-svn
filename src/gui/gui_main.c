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

#include <Ecore_X.h>
#include <Esmart/Esmart_Container.h>
#include <Ecore_Evas.h>

#include "gui_main.h"


static void _freshen_trans(Ecore_Evas *ee) {
    int x, y, w, h;
    Evas_Object *o;

    if (!ee) return;

    /* get the size of the object */
    ecore_evas_geometry_get(ee, &x, &y, &w, &h);
    o = evas_object_name_find(ecore_evas_get(ee), "background");

    /* be sure that the object exist */
    if (!o) {
        fprintf(stderr, "Trans object not found, bad, very bad\n");
        ecore_main_loop_quit();
    }
    /* make the refresh */
    esmart_trans_x11_freshen(o, x, y, w, h);
}


void gui_main_move_cb(Ecore_Evas *ee) {
  /* refresh the transparent during moving */
  _freshen_trans(ee);
}


void gui_main_resize_cb(Ecore_Evas *ee) {
    int w, h;
    int minw, minh;
    int maxw, maxh;
    Evas_Object *o = NULL;

    if (ee) {
      /* get size */
      ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
      ecore_evas_size_min_get(ee, &minw, &minh);
      ecore_evas_size_max_get(ee, &maxw, &maxh);

      if ((w >= minw) && (h >= minh) && (h <= maxh) && (w <= maxw)) {
	if ((o = evas_object_name_find(ecore_evas_get(ee), "background")))
	  evas_object_resize(o, w, h);
      }
    }
    /* call the refresh stuff */
    _freshen_trans(ee);
}


int gui_main_init (char * winname) {

  /* the X Window object */
  Ecore_X_Window  win;
  int x, y , w, h;

  /* initialize x */
  ecore_x_init (NULL);
  if (!ecore_evas_init ()) return -1;
  
  Ecore_Evas  *ee = ecore_evas_software_x11_new (NULL, 0, 0, 0, 150, 150);
  win = ecore_evas_software_x11_window_get(ee);
  
  /* if the ee is not available */
  if (!ee) return -1;

  /* define some properties on the ecore evas object */
  /* set title name */
  ecore_evas_title_set (ee, winname);
  /* remove border */
  //  ecore_evas_borderless_set (ee, 1);
  /* define the window on the below level layer */
  ecore_x_window_prop_layer_set(win, ECORE_X_WINDOW_LAYER_BELOW);
  /* define callback */
  ecore_evas_callback_resize_set(ee, gui_main_resize_cb);
  ecore_evas_callback_move_set(ee, gui_main_move_cb);

  /* display the window */
  ecore_evas_show (ee);
  
  /* get the Evas object from the ecore evas */
  Evas * evas= ecore_evas_get (ee);
  
  /* create a transparent background */
  Evas_Object * background = esmart_trans_x11_new (evas);
  evas_object_move (background, 0, 0);
  evas_object_layer_set(background, -5);
  evas_object_name_set(background, "background");
  ecore_evas_geometry_get(ee, &x, &y, &w, &h);
  evas_object_resize(background, w, h);
  evas_object_show(background);

  /* refresh the background */
  esmart_trans_x11_freshen(background, x, y, w, h);
  
  
  /* create the container */
  Evas_Object * container = esmart_container_new(evas);
  evas_object_move(container, 0, 0);
  evas_object_resize(container, w, h);
  evas_object_layer_set(container, 0);
  evas_object_name_set(container, "container");
  evas_object_show(container);
  esmart_container_padding_set(container, 10, 10, 10, 10);
  esmart_container_spacing_set(container, 5);
  esmart_container_direction_set(container, 1);
  esmart_container_fill_policy_set(container,
				   CONTAINER_FILL_POLICY_FILL);
  

  return 0;
}
