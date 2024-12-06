#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "ds/lists/singly.h"
#include "ds/types.h"


#define __private static

// singly(normal or circular) list creation
SinglyList 
s_create_list(DSDataTypes type) {
  SinglyList list = malloc(sizeof(_SinglyList));
  if(!list)
    return NULL;
  list->_type = type;
  list->_size = 0;
  list->_head = NULL;
  list->_tail = NULL;
  list->_curr = NULL;
  return list;
}

// getters have to be suitable for both singly and circular

// get value for node
const SinglyNode 
s_get_nv(const SinglyList list, const SinglyNode node, DSData dest) {
  if(!dest || !node || !list) {
    errno = EINVAL;
    return NULL;
  }
  // convert value to the right type and put it into dest
  __type_dispatcher(list->_type, dest, node->_data);
  return node;
}

// get node at position pos, put value into dest
const SinglyNode 
s_get_atp(const SinglyList list, const size_t pos, DSData dest) {
  if(!dest || pos > list->_size - 1 || !list) {
    errno = EINVAL;
    return NULL;
  }
  size_t c = 0;
  SinglyNode _it = list->_head;
  for(; c++ < pos; _it = _it->_next);
  // get node value
  s_get_nv(list, _it, dest);
  return _it;
}

// get pos of node in list, put value into dest
const int 
s_get_np(const SinglyList list, const SinglyNode node, DSData dest) {
  if(!dest || !node || !list) {
    errno = EINVAL;
    return -1;
  }
  int c = 0;
  SinglyNode _it = list->_head;
  for(; _it != list->_tail && _it != node; _it = _it->_next) c++;
  if(_it != node) { // we reached _tail without finding node 
    errno = ENOENT; // no such node
    return -1;
  }
  // get node value
  s_get_nv(list, _it, dest);
  return c;
}


// get node by val, return the first occurence from offset
const SinglyNode 
s_get_byv(const SinglyList list, const DSData value, const size_t offset) {
  // get the offset node
  SinglyNode _it = s_get_atp(list, offset, NULL);
  if(!_it) return NULL;
  // start the search from offset
  for(; _it != list->_tail && _it->_data != value; _it = _it->_next);
  if(_it == list->_tail && _it->_data != value) {
    errno = ENOENT; // no such node
    return NULL;
  }
  return _it;
}



// get pos of node in list by value, starting from offset
const int 
s_get_pbyv(const SinglyList list, const DSData value, const size_t offset) {
  // get the node with value from offset
  SinglyNode _it = s_get_byv(list, value, offset);
  if(!_it) return -1;
  // search for its pos
  int c = s_get_np(list, _it, NULL);
  return c;
}

// int s_free(SinglyList *list) {
//   if(list == NULL)
//     return 0;
//   for(SinglyNode *_it = list->head, *prec = NULL; _it != NULL;) {
//     prec = _it;
//     _it = _it->next;
//     free(prec);
//   }
//   return 1;
// }


// CIRCUAR SINGLY LISTS








