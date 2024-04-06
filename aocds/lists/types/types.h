// HEADER FILE CONTAINING LIST TYPES AND LIST ELEMENT TYPES

#ifndef __LIST_E_TYPES__
  #define __LIST_E_TYPES__
  typedef enum _etypes {
    INT_LIST=0,
    CHAR_LIST=1,
    UINT_LIST=2,
    CUSTOM_LIST=3
  } ListType;
#endif


/*#ifndef __LIST_TYPES__
  #define __LIST_TYPES__
  typedef enum _ltypes {
    SINGLE=0,
    SINGLE_CIRC=1,
    DOUBLE=2,
    DOUBLE_CIRC=3
  } ListType;
#endif
*/
#ifndef __ELEM_POINTER__
  #define __ELEM_POINTER__
  typedef void *ListElemPtr;
#endif



