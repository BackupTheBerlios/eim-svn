#include <assert.h>
#include "properties.h"


/**
 * Create the Account page and add it to the notebook
 *  - jabber id
 *  - password
 *  - resource + priority
 */
void _create_account_property_page (Ewl_Widget * notebook) {
  assert (notebook);
  
  Ewl_Widget * tab;
  Ewl_Widget * vbox;
  Ewl_Widget * hbox;
  Ewl_Widget * text;
  Ewl_Widget * entry;

  /* create the tab entry */
  tab = ewl_text_new ("Account");
  ewl_widget_show (tab);

  /* create the vbox that will contain all widget of the page */
  vbox = ewl_vbox_new ();
  ewl_widget_show (vbox);
  
  /* add jabber id */
  hbox = ewl_hbox_new ();
  ewl_widget_show (hbox);
  ewl_container_child_append (EWL_CONTAINER(vbox), hbox);
  text = ewl_text_new ("Jabber ID");
  ewl_container_child_append (EWL_CONTAINER (hbox), text);
  ewl_widget_show (text);
  entry = ewl_entry_new ("");
  ewl_container_child_append (EWL_CONTAINER (hbox), entry);
  ewl_widget_show (entry);

  /* password */
  hbox = ewl_hbox_new ();
  ewl_widget_show (hbox);
  ewl_container_child_append (EWL_CONTAINER(vbox), hbox);
  text = ewl_text_new ("Password");
  ewl_container_child_append (EWL_CONTAINER (hbox), text);
  ewl_widget_show (text);
  entry = ewl_password_new ("");
  //ewl_callback_append(entry, EWL_CALLBACK_VALUE_CHANGED, passwd_cb, NULL);
  ewl_container_child_append (EWL_CONTAINER (hbox), entry);
  ewl_widget_show (entry);
  
  
  /* resource + priority */

  
  /* add the tab and vbox to the notebook */
  ewl_notebook_page_append (EWL_NOTEBOOK(notebook), tab, vbox);
}



/**
 * Create the connection property page and add it to the notebook
 * - Use SSL encryption
 * - Allow Plaintext Login
 * - Send "Keep-Alive" packets (for NAT timeouts)
 * - Manually specify Server Host/Port
 */
void _create_connection_property_page (Ewl_Widget * notebook) {
  assert (notebook);
  
  Ewl_Widget * tab;
  Ewl_Widget * vbox;
  Ewl_Widget * hbox;
  Ewl_Widget * text;
  Ewl_Widget * entry;

  /* create the tab entry */
  tab = ewl_text_new ("Connection");
  ewl_widget_show (tab);

  /* create the vbox that will contain all widget of the page */
  vbox = ewl_vbox_new ();
  ewl_widget_show (vbox);
  

  /* add the tab and vbox to the notebook */
  ewl_notebook_page_append (EWL_NOTEBOOK(notebook), tab, vbox);
}



/**
 * Create the details property page and add it to the notebook
 * - Edit Personal Information
 * - Allows to change password on the server side
 */
void _create_details_property_page (Ewl_Widget * notebook) {
  assert (notebook);
  
  Ewl_Widget * tab;
  Ewl_Widget * vbox;
  Ewl_Widget * hbox;
  Ewl_Widget * text;
  Ewl_Widget * entry;

  /* create the tab entry */
  tab = ewl_text_new ("Details");
  ewl_widget_show (tab);

  /* create the vbox that will contain all widget of the page */
  vbox = ewl_vbox_new ();
  ewl_widget_show (vbox);
  

  /* add the tab and vbox to the notebook */
  ewl_notebook_page_append (EWL_NOTEBOOK(notebook), tab, vbox);
}

/**
 * Create the preferences property page and add it to the notebook
 * - Automatically connect on startup
 * - Automatically reconnect if disconnected
 * - Log message history
 * - Ignore SSL warnings
 */
void _create_preferences_property_page (Ewl_Widget * notebook) {
  assert (notebook);
  
  Ewl_Widget * tab;
  Ewl_Widget * vbox;
  Ewl_Widget * hbox;
  Ewl_Widget * text;
  Ewl_Widget * entry;

  /* create the tab entry */
  tab = ewl_text_new ("Preferences");
  ewl_widget_show (tab);

  /* create the vbox that will contain all widget of the page */
  vbox = ewl_vbox_new ();
  ewl_widget_show (vbox);
  

  /* add the tab and vbox to the notebook */
  ewl_notebook_page_append (EWL_NOTEBOOK(notebook), tab, vbox);
}







/**
 * This windows should contains all properties
 * @return the newly created windows
 */
Ewl_Widget * create_properties_window () {
  Ewl_Widget * win;
  Ewl_Widget * notebook;
  Ewl_Widget * vbox;

  /* create the new window */
  win = ewl_window_new ();
  ewl_object_size_request(EWL_OBJECT(win), 300, 80); 
  ewl_object_fill_policy_set(EWL_OBJECT(win), EWL_FLAG_FILL_ALL);
  
  ewl_window_title_set (EWL_WINDOW(win), "EIM Properties");
  ewl_window_name_set (EWL_WINDOW(win), "EIM Properties");
  ewl_window_class_set (EWL_WINDOW(win), "EIM Properties");
  // should insert the CALLBACK DELETE FUNCTION

  /* create the vbox which contains the notebook */
  vbox = ewl_vbox_new ();
  ewl_object_fill_policy_set (EWL_OBJECT(vbox), EWL_FLAG_FILL_SHRINK);
  ewl_container_child_append (EWL_CONTAINER (win), vbox);
  ewl_widget_show (vbox);

  /* create the note book */
  notebook = ewl_notebook_new ();
  ewl_notebook_tabs_position_set (EWL_NOTEBOOK(notebook), EWL_POSITION_TOP);
  ewl_widget_appearance_set (notebook, "window");
  
  /* create the Account Page */
  _create_account_property_page (notebook);
  _create_connection_property_page (notebook);
  _create_details_property_page (notebook);
  _create_preferences_property_page (notebook);

  /* after added pages inside the notebook, we add it to the window */
  ewl_container_child_append (EWL_CONTAINER(vbox), notebook);
  ewl_widget_show (notebook);
  
  return win;
}
