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
#include <stdlib.h>
#include <Ecore.h>
#include <Ecore_Con.h>

#include <Ewl.h>

#include "gui/gui_main.h"


static int eim_handler_signal_exit (void *data, int ev_type, void *ev) {
  Ecore_Event_Signal_Exit *e = ev;
  
  /*  
  if (e->interrupt)
    printf ("%s exit: interrupt\n", PACKAGE);
  if (e->quit)
    printf ("%s exit: quit\n", PACKAGE);
  if (e->terminate)
    printf ("%s exit: terminate\n", PACKAGE);
  */
  ecore_main_loop_quit ();

  return 1;
}


int main (int argc, char **argv) {
  int          c = 0;
  char         theme_file[PATH_MAX];
  int          got_theme_file = FALSE;
  struct stat  statbuf;
  
  /* parse the command line */
  while ( (c = getopt (argc, argv, "ht")) != -1) {
    
    switch (c) {
    case 'h':
      printf ("Usage: %s [OPTION] ...\n\n", argv[0]);
      printf ("  -h        \t display this help and exit\n");
      printf ("  -t THEME  \t specify an edje theme file (.eet)\n");
      
      exit (-1);
      break;
    case 't':
      got_theme_file = TRUE;
      snprintf (theme_file, PATH_MAX, "%s", (char *) argv[optind]);
      break;
    };
  }
  
  
  /* check if there is a valid theme file */
  if (got_theme_file) {
    stat (theme_file, &statbuf);
    if (!S_ISREG(statbuf.st_mode)) {
      fprintf (stderr, "error: themefile '%s' does not exist!\n", 
	       theme_file);
      exit (-1);
    }
  }
  
  
  /* initialize the core */
  ecore_init ();
  if (!ewl_init(&argc, argv)) {
    printf("Unable to init ewl\n");
    return -1;
  }

  ecore_event_handler_add (ECORE_EVENT_SIGNAL_EXIT, eim_handler_signal_exit, NULL);
  if (!ecore_con_init ()) return -1;
  
  ecore_app_args_set (argc, (const char **) argv);

  if (gui_main_init2 ("eim", theme_file)) return -1;
  
  /* process the main loop */
  ecore_main_loop_begin ();


  /* shutdown all ecore service */
  ewl_shutdown ();
  ecore_shutdown ();
  
  return 0;
}
