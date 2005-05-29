#include <assert.h>
#include <string.h>
#include "properties.h"


/**
 * Define the properties for the Properties page.
 * It contains all parameters available inside the Egxp and its extension
 * We use this structure has temporary variable.
 */
typedef struct _Properties Properties;
#define PROPERTIES(o) ((Properties*)o)
struct _Properties {
  /* account */
  char * jabber_id;
  char * password;
  char * resource;
  int priority;

  /* connection */
  int use_ssl;
  int allow_plaintext;
  int send_keep_alive;
  // manual server host port

  /* details */

  /* preferences */
  int auto_connect;
  int auto_reconnect;
  int log_history;
  int ignore_ssl_warning;
};



Properties * _properties_new () {
  Properties * tmp = PROPERTIES(malloc (sizeof(Properties)));
  memset (tmp, 0, sizeof (Properties));

  return tmp;
}





/**
 * Create the Account page and add it to the notebook
 *  - jabber id
 *  - password
 *  - resource + priority
 */
void _create_account_property_page (Ewl_Widget * notebook, Egxp * eg) {
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
void _create_connection_property_page (Ewl_Widget * notebook, Egxp *eg) {
  assert (notebook);
  
  Ewl_Widget * tab;
  Ewl_Widget * vbox;
  Ewl_Widget * hbox;
  Ewl_Widget * text;
  Ewl_Widget * entry;
  Ewl_Widget * misc;

  /* create the tab entry */
  tab = ewl_text_new ("Connection");
  ewl_widget_show (tab);

  /* create the vbox that will contain all widget of the page */
  vbox = ewl_vbox_new ();
  ewl_widget_show (vbox);
  
  /* use SSL encryption */
  misc = ewl_checkbutton_new ("Use SSL encryption");
  ewl_container_child_append (EWL_CONTAINER(vbox), misc);
  ewl_widget_show(misc);

  /* allow plain text login */
  misc = ewl_checkbutton_new ("Allow plain text login");
  ewl_container_child_append (EWL_CONTAINER(vbox), misc);
  ewl_widget_show(misc);

  /* Send "keep alive" packets (for NAT timeouts) */
  misc = ewl_checkbutton_new ("Send \"keep alive\" packets (for NAT timeouts)");
  ewl_container_child_append (EWL_CONTAINER(vbox), misc);
  ewl_widget_show(misc);
  

  /* add the tab and vbox to the notebook */
  ewl_notebook_page_append (EWL_NOTEBOOK(notebook), tab, vbox);
}



/**
 * Create the details property page and add it to the notebook
 * - Edit Personal Information
 * - Allows to change password on the server side
 */
void _create_details_property_page (Ewl_Widget * notebook, Egxp *eg) {
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
void _create_preferences_property_page (Ewl_Widget * notebook, Egxp * eg) {
  assert (notebook);
  
  Ewl_Widget * tab;
  Ewl_Widget * vbox;
  Ewl_Widget * hbox;
  Ewl_Widget * text;
  Ewl_Widget * entry;
  Ewl_Widget * misc;

  /* create the tab entry */
  tab = ewl_text_new ("Preferences");
  ewl_widget_show (tab);

  /* create the vbox that will contain all widget of the page */
  vbox = ewl_vbox_new ();
  ewl_widget_show (vbox);
  
  /* Automatically connect on startup */
  misc = ewl_checkbutton_new ("Automatically connect on startup");
  ewl_container_child_append (EWL_CONTAINER(vbox), misc);
  ewl_widget_show(misc);

  /* Automatically reconnect if disconnected */
  misc = ewl_checkbutton_new ("Automatically reconnect if disconnected");
  ewl_container_child_append (EWL_CONTAINER(vbox), misc);
  ewl_widget_show(misc);

  /* Log message history */
  misc = ewl_checkbutton_new ("Log message history");
  ewl_container_child_append (EWL_CONTAINER(vbox), misc);
  ewl_widget_show(misc);

  /* Ignore SSL warnings */
  misc = ewl_checkbutton_new ("Ignore SSL warnings");
  ewl_container_child_append (EWL_CONTAINER(vbox), misc);
  ewl_widget_show(misc);
  
  /* add the tab and vbox to the notebook */
  ewl_notebook_page_append (EWL_NOTEBOOK(notebook), tab, vbox);
}







/**
 * This windows should contains all properties
 * @return the newly created windows
 */
Ewl_Widget * create_properties_dialog (Egxp * eg) {
  Ewl_Widget * dialog;
  Ewl_Widget * notebook;
  Ewl_Widget * vbox;
  Ewl_Widget * button;

  /* create the new dialog */
  dialog = ewl_dialog_new(EWL_POSITION_BOTTOM);
  ewl_dialog_has_separator_set(EWL_DIALOG(dialog), 1);

  /* create the ok button */
  button = ewl_dialog_button_add(EWL_DIALOG(dialog),"OK", EWL_RESPONSE_OK);
  ewl_container_child_append(EWL_CONTAINER(dialog), button);
  //ewl_callback_append(o, EWL_CALLBACK_CLICKED, dialog_clicked_cb, dialog);
  ewl_widget_show(button);
  
  
  /* create the cancel button */
  button = ewl_dialog_button_left_add(EWL_DIALOG(dialog),"Cancel", EWL_RESPONSE_CANCEL);
  ewl_container_child_append(EWL_CONTAINER(dialog), button);
  //ewl_callback_append(o, EWL_CALLBACK_CLICKED, dialog_clicked_cb, dialog);
  ewl_widget_show(button);
  

  /* create the vbox which contains the notebook */
  vbox = ewl_vbox_new ();
  ewl_object_fill_policy_set (EWL_OBJECT(vbox), EWL_FLAG_FILL_SHRINK);
  ewl_widget_show (vbox);

  /* create the note book */
  notebook = ewl_notebook_new ();
  ewl_notebook_tabs_position_set (EWL_NOTEBOOK(notebook), EWL_POSITION_TOP);
  ewl_widget_appearance_set (notebook, "window");
  
  /* create the Account Page */
  _create_account_property_page (notebook, eg);
  _create_connection_property_page (notebook, eg);
  _create_details_property_page (notebook, eg);
  _create_preferences_property_page (notebook, eg);
  
  /* after added pages inside the notebook, we add it to the dialog */
  ewl_container_child_append (EWL_CONTAINER(vbox), notebook);
  ewl_widget_show (notebook);
  
  ewl_dialog_widget_add(EWL_DIALOG(dialog), vbox);
  ewl_object_alignment_set(EWL_OBJECT(dialog), EWL_FLAG_ALIGN_CENTER);
  
  return dialog;
}
