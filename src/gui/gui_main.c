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

#include <Ewl.h>


#include "properties.h"
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


int gui_main_init (char * winname, char * theme) {

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
  //ecore_x_window_prop_layer_set(win, ECORE_X_WINDOW_LAYER_BELOW);

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



/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
void _gui_main_destroy_cb(Ewl_Widget *w, void *event, void *data) {
    ewl_widget_destroy(w);
    ewl_main_quit();
}


void item_cb(Ewl_Widget *w, void *ev_data, void *data) {
  Ewl_Widget *menu = data;
  Ewl_Widget *parent = menu->parent;
  Ewl_Event_Mouse_Down *ev = ev_data;
  
  if (ev->button == 3) {
    printf("Menu callback %d, %d\n", ev->x, ev->y);
    ewl_object_position_request(EWL_OBJECT(menu), ev->x, ev->y - EWL_OBJECT(parent)->current.h);
    ewl_widget_show (menu);
    ewl_callback_call(menu, EWL_CALLBACK_SELECT);
  }
}



Ewl_Widget * create_menu (Ewl_Widget * parent) {
  Ewl_Widget *menu;
  Ewl_Widget *item;
  
  menu = ewl_menu_new(NULL, NULL);
  ewl_container_child_append(EWL_CONTAINER(parent), menu);
  
  item = ewl_menu_item_new(NULL, "Action 1");
  ewl_container_child_append(EWL_CONTAINER(menu), item);
  ewl_widget_show(item);
  
  item = ewl_menu_item_new(NULL, "Action 2");
  ewl_container_child_append(EWL_CONTAINER(menu), item);
  ewl_widget_show(item);

  return menu;
}


/**
 * Create an item for the tree with an image. 
 */
Ewl_Widget * create_tree_item (Ewl_Widget * tree, char * img_path, char * item_text, void * user_data) {

  Ewl_Widget * hbox;
  Ewl_Widget *img;
  Ewl_Widget * text;

  /* create the horizontal box that should contains image + text, then add the clicked callback */
  hbox = ewl_hbox_new (); 
  ewl_object_fill_policy_set(EWL_OBJECT(hbox), EWL_FLAG_FILL_ALL);
  ewl_callback_append(hbox, EWL_CALLBACK_MOUSE_DOWN, item_cb, user_data);
  ewl_widget_show (hbox);
  
  /* create the image and add it to the hbox */
  if (img_path != NULL) {
    img = ewl_image_new(img_path, NULL);
    ewl_object_alignment_set(EWL_OBJECT(img), EWL_FLAG_ALIGN_LEFT);
    ewl_object_fill_policy_set(EWL_OBJECT(img), EWL_FLAG_FILL_HSHRINK);
    ewl_container_child_append (EWL_CONTAINER (hbox), img);
    ewl_widget_show(img);
  }
  
  /* create the text and add it to the hbox */
  text = ewl_text_new(item_text);
  ewl_container_child_append (EWL_CONTAINER (hbox), text);
  ewl_widget_show(text);
  
  
  /* append the item to the tree */
  ewl_tree_row_add (EWL_TREE(tree), NULL, &hbox);
  
  return hbox;
}



int gui_main_init2 (char * winname, char * theme) {
  Ewl_Widget     *main_win = NULL;
  Ewl_Widget     *tree = NULL;
  Ewl_Widget     *box = NULL;

  Ewl_Widget     * item = NULL;
  Ewl_Widget     * box_item = NULL;
  Ewl_Widget     * menu;
  
  /* create the main windows */
  main_win = ewl_window_new();
  
  /* define size */
  ewl_object_size_request(EWL_OBJECT(main_win), 80, 300);
  ewl_object_fill_policy_set(EWL_OBJECT(main_win), EWL_FLAG_FILL_ALL);
  
  /* define title */
  ewl_window_title_set(EWL_WINDOW(main_win),
		       "The Enlightenment Instant Messenger");
  
  ewl_callback_append(main_win, EWL_CALLBACK_DELETE_WINDOW, _gui_main_destroy_cb, NULL);
  ewl_window_name_set(EWL_WINDOW(main_win), "Enlightenment Instant Messenger");
  ewl_window_class_set(EWL_WINDOW(main_win), "Enlightenment Instant Messenger");
  ewl_widget_show(main_win);

  
  /* create the container */
  box = ewl_vbox_new();
  ewl_container_child_append(EWL_CONTAINER(main_win), box);
  ewl_object_fill_policy_set(EWL_OBJECT(box), EWL_FLAG_FILL_ALL);
  ewl_widget_show(box);
  
  
  /* create the tree root object */
  tree = ewl_tree_new (1);
  ewl_container_child_append (EWL_CONTAINER(box), tree);
  ewl_widget_show(tree);

  /* create the menu */
  menu = create_menu (main_win);
  ewl_callback_append(tree, EWL_CALLBACK_MOUSE_DOWN, item_cb, menu);

  /* Add an item */
  // create_tree_item (tree, NULL, "entry 1", menu);
  // create_tree_item (tree, NULL, "entry 2", menu);
  // create_tree_item (tree, NULL, "entry 3", menu);

  /* test properties windows */
  /*  main_win = create_properties_dialog (NULL);
      ewl_widget_show (main_win);****/
  
  return 0;
}
