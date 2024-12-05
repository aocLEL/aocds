// COMMON 
#include "../types.h"


#ifndef __COMMON__
  #define __COMMON__
  // available list types
  typedef enum list_types {
    SINGLY = 0,
    CIRC_SINGLY,
    DOUBLY,
    CIRC_DOUBLY
  } ListTypes;
  typedef void *GenericList;
  // searching funcs common
  // search by pos
  int s_search_pos(const GenericList list, const ListTypes type, const size_t pos);
  // search by value
  int s_search_val(const GenericList list, const ListTypes type, const DSData value);
#endif
  
