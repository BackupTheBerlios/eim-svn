#ifndef EGXP_NODE_STRUCT_H_
#define EGXP_NODE_STRUCT_H_

#include <Ecore_Data.h>

#include "egxp_message.h"

/**
 * Defines the callback types supported by egxp
 */
typedef void (*egxp_callback_ptr)(Egxp_Message *, void*);


typedef struct _Egxp_ChildNode Egxp_ChildNode;
#define EGXP_CHILDNODE(o) ((Egxp_ChildNode*)o)
struct _Egxp_ChildNode {
  Ecore_Hash * childs; /* hash map, the key is the tag, value is a Egxp node */

  egxp_callback_ptr * begin_func; /* called when the start tag appears */
  egxp_callback_ptr * end_func;   /* called when the end tag appears */
};


/**
 * This is the main structure of Egxp. This structure keeps the tag id.
 */
typedef struct _Egxp_Node Egxp_Node;
#define EGXP_NODE(o) ((Egxp_Node*)o)
struct _Egxp_Node {
  Egxp_ChildNode * child; /* this is a pointer on a child, it's used when no specific condition
			     are specified */
  
  unsigned int tag; /* this is the id of the tag */
  
  Ecore_List * conditions; /* this is a list of conditionnal Node attributes -> epgx_conditional node */
};


typedef struct _Egxp_Condition Egxp_Condition;
#define EGXP_CONDITION(o) ((Egxp_Condition*)o)
struct _Egxp_Condition {
  unsigned int key; /* the id of the key */
  unsigned int value; /* the id of the value */
};



typedef struct _Egxp_ConditionalNode Egxp_ConditionalNode;
#define EGXP_CONDITIONALNODE(o) ((Egxp_ConditionalNode*)o)
struct _Egxp_ConditionalNode {
  Egxp_ChildNode * child;
  
  Egxp_Node * parent; /* the parent of this node, it's necessary to know the tag, but maybe 
			 useless ... */
  
  Ecore_List * conditions; /* this is the list of the condition */
};

#endif
