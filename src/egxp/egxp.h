#ifndef egxp_header_h_
#define egxp_header_h_

#include "egxp_node_struct.h"
#include "egxp_child_node.h"
#include "egxp_node.h"
#include "egxp_opcode.h"
#include "egxp_condition.h"
#include "egxp_message.h"
#include "egxp_conditional_node.h"

typedef struct _Egxp Egxp;
#define EGXP(o) ((Egxp*)o)
struct _Egxp {
  /* opcodes list */
  Egxp_Opcode * opcodes;
  
  /* root node */
  Egxp_Node * root;
};


/**
 * Allocate the Egxp structure
 * - allocate the opcodes structures 
 * - set to null the opcode
 */
Egxp * egxp_new ();


/**
 * Free the egxp structure
 */
void egxp_free (Egxp * e);

#endif
