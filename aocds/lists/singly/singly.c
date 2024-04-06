#include <stdio.h>
#include <stdlib.h>
#include "singly.h"

#define __private static


SinglyList *s_create_list(ListType type) {
  SinglyList *list = malloc(sizeof(SinglyList));
  if(list == NULL)
    return NULL;
  list->type = type;
  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  list->curr = NULL;
  return list;
}

// cast void pointer to specific type
__private void type_dispatcher(const SinglyNode *node, ListType type, ListElemPtr dest) {
     switch(type) { 
        case INT_LIST:
          {
            int *data_ptr = (int*)dest;
            *data_ptr = (int)(long)node->data; 
            break;
          }
        case CHAR_LIST:
          {
            char *data_ptr = (char*)dest;
            *data_ptr = (char)(long)node->data;
            break;
          }
        case UINT_LIST:
          {
            unsigned *data_ptr = (unsigned*)dest;
            *data_ptr = (unsigned)(long)node->data;
            break;
          } 
        default:
            printf("Not a list type!!\n");
            exit(EXIT_FAILURE);
            break;
    } 
}

// get value stored in node at position pos
const SinglyNode *s_get_node_pos_val(SinglyList *list, size_t pos, ListElemPtr dest) {
  if(dest == NULL || pos >= list->size || list == NULL)
    return NULL;
  SinglyNode *_it;
  pos++;
  for(_it = list->head; pos-- > 0 && _it != NULL; _it = _it->next);
  if(_it == NULL) {
    return NULL;
  }
  type_dispatcher(_it, list->type, dest);
  return _it; 
}

// get value stored in node
const SinglyNode *s_get_node_val(const SinglyNode *node, ListType type,  ListElemPtr dest) {
  if(node == NULL || dest == NULL) {
    return NULL;
  }
  type_dispatcher(node, type, dest);
  return node;
}


// add node at position:  pos, node previously at pos goes before new node
const SinglyNode *s_add_node_at(SinglyList *list, size_t pos, ListElemPtr data) {
  if(list == NULL || data == NULL || pos >= list->size)
    return NULL;
  SinglyNode *new_node = malloc(sizeof(SinglyNode));
  if(new_node == NULL)
    return NULL;
  new_node->data = data;
  if(pos == 0) {
    if(list->head == NULL) {
        list->head = new_node;
        list->head->next = NULL;
        list->tail = list->head;
    }
    else {
      new_node->next = list->head;
      list->head = new_node;
    }
  }
  else {
    pos++;
    SinglyNode *_it;
    for(_it = list->head; pos-- > 0; _it = _it->next); // node at pos pos goes before new node
    new_node->next = _it->next;
    _it->next = new_node;
    if(list->tail == _it)
        list->tail = new_node;
  }
  list->curr = new_node;
  list->size++;
  return new_node;
}



const SinglyNode *s_add_node_after(SinglyList *list, SinglyNode *node, ListElemPtr data) {
  if(list == NULL || node == NULL || data == NULL)
    return NULL;
  SinglyNode *new_node = malloc(sizeof(SinglyNode));
  if(new_node == NULL)
    return NULL;
  new_node->data = data;
  new_node->next = node->next;
  node->next = new_node;
  if(list->tail == node)
    list->tail = new_node;
  list->curr = new_node;
  list->size++;
  return new_node;
}

 
const SinglyNode *s_replace_node(SinglyList *list, SinglyNode *node, ListElemPtr data) {
  if(list == NULL || node == NULL || data == NULL)
    return NULL;
  node->data = data;
  list->curr = node;
  return node;
}


// CUSTOM LISTS

const SinglyNode *cs_get_node_pos_val(SinglyList *list, size_t pos, ListElemPtr *dest) {
  if(list == NULL || dest == NULL || pos > list->size - 1)
    return NULL;
  SinglyNode *_it;
  pos++;
  for(_it = list->head; pos-- > 0; _it = _it->next); 
  *dest = _it->data;
  return _it; 
}


const SinglyNode *cs_get_node_val(const SinglyNode *node, ListElemPtr *dest) {
  if(node == NULL || dest == NULL) {
    return NULL;
  }
  *dest = node->data;
  return node;
}


int s_free(SinglyList *list) {
  if(list == NULL)
    return 0;
  for(SinglyNode *_it = list->head, *prec = NULL; _it != NULL;) {
    prec = _it;
    _it = _it->next;
    free(prec);
  }
  return 1;
}


// CIRCUAR SINGLY LISTS








