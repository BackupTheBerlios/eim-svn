#ifndef egxp_opcode_header_h_
#define egxp_opcode_header_h_

#include <Ecore_Data.h>

/**
 * This set of function is used to define all opcode.
 * In order to use low memory and to accelerate protocol
 * operations we associate a string to an id. So during the execution
 * we compare id instead string
 */
typedef struct _Egxp_Opcode Egxp_Opcode;
#define EGXP_OPCODE(o) ((Egxp_Opcode*)o)
struct _Egxp_Opcode {
  
  Ecore_Hash * string_id;
  
  char ** id_string;

  unsigned int id;

  unsigned char need_update;
};


/**
 * Initialize the structure
 * @return the newly created object
 */
Egxp_Opcode * egxp_opcode_new ();


/**
 * Need to free unsigned integer of the hash map
 */
void egxp_opcode_free (Egxp_Opcode * op);


/**
 * Add a new word
 * @param op: The opcode structure
 * @param name: The string representation
 * @return the newly created id.
 */
int egxp_opcode_add (Egxp_Opcode * op, const char * name);


/**
 * This is really IMPORTANT to call this method after your last update.
 * Otherwise there will be a segfault.
 * This method update the id_string vector.
 * @param op: The opcode structure
 */
void egxp_opcode_update (Egxp_Opcode * op);


/**
 * Return the opcode in string format
 * @param op: The opcode structure
 * @param id: The id
 * @return: the string id
 */
const char * egxp_opcode_get_string (Egxp_Opcode * op, const int id);


/**
 * Return the opcode in string format
 * @param op: The opcode structure
 * @param id: The id
 * @return: the string id
 */
const int egxp_opcode_get_id (const Egxp_Opcode *op, const char * name);


/**
 * Display the contents of grammar
 */
void egxp_opcode_display (Egxp_Opcode * op);

#endif
