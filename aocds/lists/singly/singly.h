// HEADER FILE CONTAINING DEFINITIONS FOR SINGLY CIRCULAR AND NORMAL LINKED LISTS
#include <stdio.h>
#include "../types/types.h"

// LEGEND:
// function prefixes:
// c --> custom list
// s --> for singly list
// sc --> for singly circular list
// d --> for doubly list
// dc --> for doubly circular list


#ifndef __SINGLY_NODE__
  #define __SINGLY_NODE__
  typedef struct _s_node {
    struct _s_node *next;
    ListElemPtr data;
  } SinglyNode;
#endif

#ifndef __SINGLY_LIST__
  #define __SINGLY_LIST__
  typedef struct _s_list {
    size_t size;
    SinglyNode *head;
    SinglyNode *tail;
    SinglyNode *curr; // curr points to last accessed node
    ListType type;
  } SinglyList;
#endif

#ifndef __SINGLY_CIRC_LIST__
  #define __SINGLY_CIRC_LIST__
  #define SinglyCircList SinglyList
#endif

#ifndef __SINGLY_LIST_FUNCS__
  #define __SINGLY_LIST_FUNCS__
  SinglyList *s_create_list(ListType type); // ok
  // FOR NORMAL TYPES LISTS
  // GETTING
  const SinglyNode *s_get_node_pos_val(SinglyList *list, size_t pos, ListElemPtr dest); // ok
  const SinglyNode *s_get_node_val(const SinglyNode *node, ListType type,  ListElemPtr dest); // ok
  #define s_get_last(list, dest)  s_get_node_val(list->tail, list->type, dest) // ok
  #define s_get_first(list, dest) s_get_node_val(list->head, list->type, dest) // ok
  #define s_get_curr(list, dest)  s_get_node_val(list->curr, list->type, dest) // ok
  // ADDING
  const SinglyNode *s_add_node_at(SinglyList *list, size_t pos, ListElemPtr data); // ok
  const SinglyNode *s_add_node_after(SinglyList *list, SinglyNode *node, ListElemPtr data); // ok
  const SinglyNode *s_replace_node(SinglyList *list, SinglyNode *node, ListElemPtr data); // ok
  #define s_add_node_start(list, data)      s_add_node_at(list, 0, data)
  #define s_add_node_end(list, data)        s_add_node_at(list, list->size - 1, data)
  #define s_add_node_after_curr(list, data) s_add_node_after(list, list->curr, data);

  // FOR CUSTOM LISTS, HERE dest IS A void**
  const SinglyNode *cs_get_node_pos_val(SinglyList *list, size_t pos, ListElemPtr *dest); // ok
  const SinglyNode *cs_get_node_val(const SinglyNode *node, ListElemPtr *dest); // ok
  #define cs_get_last(list, dest)   cs_get_node_val(list->tail, dest)
  #define cs_get_first(list, dest)  cs_get_node_val(list->head, dest)
  #define cs_get_curr(list, dest)   cs_get_node_val(list->curr, dest)

  // DESTROYING
  int s_free(SinglyList *list); // ok
#endif



#ifndef __SINGLY_CIRC_LIST_FUNCS__
  #define __SINGLY_CIRC_LIST_FUNCS__
  //SinglyCircList *sc_create_list(ListType type); // unuseful, is the same struct as normal SinglyList
  // FOR NORMAL TYPES LISTS
  // GETTING
  //SinglyNode *sc_get_node_val(SinglyCircList *list, size_t pos, ListElemPtr dest);
  SinglyNode *sc_get_curr_val(SinglyCircList *list, ListElemPtr dest);
  #define sc_get_last(list, dest)  sc_get_node_val(list, list->size - 1, dest)
  #define sc_get_first(list, dest) sc_get_node_val(list, 0, dest)
  // ADDING
  SinglyNode *sc_add_node_at(SinglyCircList *list, size_t pos, ListElemPtr data);
  SinglyNode *sc_add_node_after(SinglyCircList *list, SinglyNode *node, ListElemPtr data);
  SinglyNode *sc_replace_node(SinglyCircList *list, SinglyNode *node, ListElemPtr data);
  #define sc_add_node_start(list, data)      sc_add_node_at(list, 0, data)
  #define sc_add_node_end(list, data)        sc_add_node_at(list, list->size - 1, data)
  #define sc_add_node_after_curr(list, data) sc_add_node_after(list, list->curr, data);

  // FOR CUSTOM LISTS, HERE dest IS A void**
  // GETTING
  SinglyNode *csc_get_node_val(SinglyCircList *list, size_t pos, ListElemPtr *dest);
  SinglyNode *csc_get_curr_val(SinglyCircList *list, ListElemPtr *dest);
  #define csc_get_last(list, dest)  csc_get_node_val(list, list->size - 1, dest)
  #define csc_get_first(list, dest) csc_get_node_val(list, 0, dest)
  //ADDING
  SinglyNode *csc_add_node_at(SinglyCircList *list, size_t pos, ListElemPtr *data);
  SinglyNode *csc_add_node_after(SinglyCircList *list, SinglyNode *node, ListElemPtr *data);
  SinglyNode *csc_replace_node(SinglyCircList *list, SinglyNode *node, ListElemPtr *data);
  #define csc_add_node_start(list, data)      csc_add_node_at(list, 0, data)
  #define csc_add_node_end(list, data)        csc_add_node_at(list, list->size - 1, data)
  #define csc_add_node_after_curr(list, data) csc_add_node_after(list, list->curr, data);

  // DESTROYING
  int sc_free(SinglyCircList *list);
#endif 
