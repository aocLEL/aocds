// HEADER FILE CONTAINING DEFINITIONS FOR SINGLY CIRCULAR AND NORMAL LINKED LISTS
#pragma once 
#include <stdio.h>
#include "ds/types.h" // for ds types
#include "generic.h" // for generic list macros and funcs

/*
TODO:
- finire enum tipi dato
- revisionare e finire codice singly
- creare type alias per il puntatore a lista
*/

// LEGEND:
// function prefixes:
// c --> custom list
// s --> for singly list
// sc --> for singly circular list
// d --> for doubly list
// dc --> for doubly circular list

/*
IDEA FINALE: struttura doubly e singly separata, le liste si utilizzano con una sintassi oop, quindi dentro la funzione di costruzione della lista che acceterà :
create_list(list_type, list_data_type)
dove list_type è :
- SINGLY_LIST(con tipo custom o meno) o SINGLY_CIRC_LIST(con tipo custom o meno)
- DOUBLY_LIST(con tipo custom o meno) o DOUBLY_CIRC_LIST(con tipo custom o meno) 

in base a se è circ o no e se il tipo è custom o no, si bindano metodi diversi, l'interfaccia dovrà essere tipo:
list->add_at(&list, pos, data); , dove il bind corretto per add_at è scelto in base al tipo di lista

*/

typedef struct _s_node {
  struct _s_node *_next;
  DSData _data;
} _SinglyNode;


typedef _SinglyNode *SinglyNode;


typedef struct _s_list {
  size_t      _size;
  SinglyNode  _head;
  SinglyNode  _tail;
  SinglyNode  _curr; // curr points to last accessed node
  DSDataTypes _type;
} _SinglyList;


// list types for user
typedef _SinglyList *SinglyList;
typedef SinglyList SinglyCircList;



SinglyList s_create_list(DSDataTypes type); // ok

// FOR NORMAL TYPES LISTS

// GETTING

// get value for node
const SinglyNode 
s_get_nv(const SinglyList list, const SinglyNode node, DSData dest);

// get node at pos, value in dest
const SinglyNode 
s_get_atp(const SinglyList list, const size_t pos, DSData dest); // ok
// get node by value(first occurrence), starting from offset
const SinglyNode 
s_get_byv(const SinglyList list, const DSData value, const size_t offset);

// get position of node, value in dest
const int16_t
s_get_np(const SinglyList list, const SinglyNode node, DSData dest);
// get pos of node by value(first occurrence), starting from offset
const int16_t 
s_get_pbyv(const SinglyList list, const DSData value, const size_t offset);

// useful macros
#define s_get_last(list, dest)  s_get_nv(list, list->_tail, dest) // ok
#define s_get_first(list, dest) s_get_nv(list, list->_head, dest) // ok
#define s_get_curr(list, dest)  s_get_nv(list, list->_curr, dest) // ok


// ADDING

const SinglyNode 
s_insert_at(const SinglyList list, const size_t pos, const DSData data); // ok
const SinglyNode 
s_insert_after(const SinglyList list, const SinglyNode node, const DSData data); // ok
const SinglyNode 
s_insert_before(const SinglyList list, const SinglyNode node, const DSData data); // ok
const SinglyNode 
s_replace(SinglyList list, SinglyNode node, const DSData data, DSData old_dest); // ok
#define s_push_front(list, data)        s_insert_before(list, list->_head, data)
#define s_push_back(list, data)         s_insert_after(list, list->_tail, data)
#define s_insert_curr(list, data)       s_insert_after(list, list->_curr, data)

const SinglyNode
s_swap_node(const SinglyList list, const SinglyNode n1, const SinglyNode n2);


// REMOVING

const int16_t 
s_remove_node(const SinglyList list, SinglyNode node, DSData dest); // ok
const int16_t 
s_remove_atp(const SinglyList list, const size_t pos, DSData dest); // ok
// remove by value
// remove all by value
// deallocazione
// da capire per add e remove delle circular

// ITERATOR --> FUNCTIONS FOR GET AN INTERATOR AND ITERATE THORUGH THE LIST


// DESTROYING

// int s_free(SinglyList list); // ok


// ADDING
const SinglyNode sc_insert_at(SinglyCircList list, const size_t pos, const DSData data); // ok
const SinglyNode sc_insert_after(SinglyCircList list, SinglyNode node, const DSData data); // ok
const SinglyNode sc_replace(SinglyCircList list, SinglyNode node, const DSData data); // ok
#define sc_insert_start(list, data)      sc_insert_at(list, 0, data)
#define sc_insert_end(list, data)        sc_insert_after(list, list->_tail, data)
#define sc_insert_curr(list, data)       sc_insert_after(list, list->_curr, data);

// DESTROYING --> probabilmente va bene anche solo quella della singly
int sc_free(SinglyCircList *list);

