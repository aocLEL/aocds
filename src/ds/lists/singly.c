#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
  if(!list || !node) {
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
  if(!list || pos > list->_size - 1) {
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
const int16_t 
s_get_np(const SinglyList list, const SinglyNode node, DSData dest) {
  if(!list || !node) {
    errno = EINVAL;
    return -1;
  }
  int16_t c = 0;
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
  SinglyNode _it = (SinglyNode)s_get_atp(list, offset, NULL);
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
const int16_t 
s_get_pbyv(const SinglyList list, const DSData value, const size_t offset) {
  // get the node with value from offset
  const SinglyNode _it = s_get_byv(list, value, offset);
  if(!_it) return -1;
  // search for its pos
  const int16_t c = s_get_np(list, _it, NULL);
  return c;
}


// insert new datas at position pos
const SinglyNode 
s_insert_at(const SinglyList list, const size_t pos, const DSData data) {
  if(!list || pos > list->_size) { // allows also size + 1 (add at the end)
    errno = ENOENT; // no such node
    return NULL;
  }
  SinglyNode new_node = (SinglyNode)malloc(sizeof(SinglyNode));
  if(!new_node)
    return NULL;
  new_node->_data = data;
  new_node->_next = NULL;
  const SinglyNode insert_pos = s_get_atp(list, pos - 1, NULL);
  if(!insert_pos) // so head is NULL
    list->_head = list->_tail = new_node;
  else {
    new_node->_next = insert_pos->_next;
    insert_pos->_next = new_node;
    if(!new_node->_next)
      list->_tail = new_node;
  }
  list->_size++;
  return new_node;
}

// insert after node, at pos (node + 1)
const SinglyNode 
s_insert_after(const SinglyList list, const SinglyNode node, const DSData data) {
  const int16_t node_pos = s_get_np(list, node, NULL);
  if(node_pos < 0) // node not found
    return NULL;
  return s_insert_at(list, node_pos + 1, data);
}


// insert before node, at pos (node), node position will increment by 1
const SinglyNode 
s_insert_before(const SinglyList list, const SinglyNode node, const DSData data) {
  const int16_t node_pos = s_get_np(list, node, NULL);
  if(node_pos < 0) // node not found
    return NULL;
  return s_insert_at(list, node_pos, data);
}

// replace value in node, returning the old one for deallocation
const SinglyNode
s_replace(const SinglyList list, const SinglyNode node, const DSData data, DSData old_dest) {
  if(s_get_np(list, node, NULL) < 0) // node not found
    return NULL;
  s_get_nv(list, node, old_dest);
  node->_data = data;
  return node;
}

// swaps value of 2 nodes
const SinglyNode
s_swap_node(const SinglyList list, const SinglyNode n1, const SinglyNode n2) {
  if(!n1 || !n2) {
    errno = EINVAL;
    return NULL;
  } 
  void *_tmp = n1->_data;
  n1->_data = n2->_data;
  n2->_data = _tmp;
  return n1;
}


// removes node from the list
const int16_t 
s_remove_node(const SinglyList list, SinglyNode node, DSData dest) {
  if(!list || !node) {
    errno = EINVAL;
    return -1;
  }
  if(node == list->_head) {
    list->_head = node->_next;
    if(!list->_head) // list was only node
      list->_tail = NULL;
  }
  else {
    SinglyNode _it = list->_head;
    for(; _it && (_it->_next != list->_tail && _it->_next != node); _it = _it->_next);
    if(!_it || _it->_next == list->_tail) {
      if(list->_tail != node) { // if head is NULL or node isn't in the list
        errno = ENOENT; // no such node
        return -1;
      }
      list->_tail = _it;
    }
    _it->_next = _it->_next->_next;
  }
  s_get_nv(list, node, dest);
  free(node);
  list->_size--;
  return 0;
}


// removes node at position pos
const int16_t 
s_remove_atp(const SinglyList list, const size_t pos, DSData dest) {
  SinglyNode node = (SinglyNode)s_get_atp(list, pos, NULL);
  if(!node) return -1;
  return s_remove_node(list, node, dest);
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








