#include <stdio.h>
#include <stdlib.h>



typedef void *list_elem_ptr;

/*#define add_list(list, value)\
    ({  __auto_type __val = value; \
        add_node(list, create_node(list->type, (list_elem_ptr)&__val));})
*/
#define add_list(list, value)  add_node(list, create_node(list->type, (list_elem_ptr)value))

typedef enum _types {
    INT_LIST=0,
    CHAR_LIST=1,
    UINT_LIST=2,
    CUSTOM_LIST=3
} list_type;

/*typedef union _data_t{
    int a;
    char b;
    float c;
} data_t;*/
    
typedef struct node {
    struct node *next;
    list_elem_ptr data;
} Node;

typedef struct list {
    size_t size;
    Node *head;
    list_type type;
} List;


List* create_list(list_type t) {
    List* new_list = (List*)malloc(sizeof(List));
    new_list->size = 0;
    new_list->head = NULL;
    new_list->type = t;
    return new_list;
}

Node *get_node_val(List *list, size_t pos, list_elem_ptr dest) {
    Node *node = list->head;
    for(size_t i = 0; node != NULL && i < pos; node = node->next, i++);
    if(node == NULL)
      return NULL;
    switch(list->type) { 
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
        case CUSTOM_LIST:
          {
            dest = node->data;
          }
        default:
            printf("Not a list type!!\n");
            exit(EXIT_FAILURE);
            break;
    }
    return node;
}

Node *add_node(List *list, Node *new_node) {
  if(list->head == NULL)
    list->head = new_node;
  else {
    Node *_it;
    for(_it = list->head; _it->next != NULL; _it = _it->next);
    _it->next = new_node;
  }
  list->size++;
  return new_node;
}

Node *create_node(list_type type, list_elem_ptr data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}


void free_list(List *list) {
  Node *_it, *prec = NULL;
  for(_it = list->head; _it != NULL;) {
    prec = _it;
    _it = _it->next;
    free(prec);
  }
  free(list);
}


void print_list(const List *list, void (*pf)(void*)) {
    switch(list->type) {
        case INT_LIST:
            for(Node *_it = list->head; _it != NULL; _it = _it->next)
              printf("%d ", (int)(long)_it->data);
            break;
        case CHAR_LIST:
            for(Node *_it = list->head; _it != NULL; _it = _it->next)
              printf("%c ", (char)(long)_it->data); 
            break;
        case UINT_LIST:
            for(Node *_it = list->head; _it != NULL; _it = _it->next)
              printf("%u ", (unsigned)(long)_it->data); 
            break;
        case CUSTOM_LIST:
            for(Node *_it = list->head; _it != NULL; _it = _it->next)
              pf(_it->data);
            break;
        default:
            printf("Not a list type!!\n");
            exit(EXIT_FAILURE);
            break;
    }
    printf("\n");
}



int main() {
  // INT_LIST
  List *list1 = create_list(INT_LIST);
  add_list(list1, 5);
  add_list(list1, 12);
  add_list(list1, 78);
  int val0, val1, val2;
  get_node_val(list1, 0, (list_elem_ptr)&val0);
  get_node_val(list1, 1, (list_elem_ptr)&val1);
  get_node_val(list1, 2, (list_elem_ptr)&val2);
  printf("VALS FROM MAIN(LIST1): %d, %d, %d\n", val0, val1, val2);
  printf("PRINTED LIST: ");
  print_list(list1, NULL);
  free_list(list1);
  // CHAR LIST
  List *list2 = create_list(CHAR_LIST);
  add_list(list2, 'a');
  add_list(list2, 'b');
  add_list(list2, 'c');
  char cval0, cval1, cval2;
  get_node_val(list2, 0, (list_elem_ptr)&cval0);
  get_node_val(list2, 1, (list_elem_ptr)&cval1);
  get_node_val(list2, 2, (list_elem_ptr)&cval2);
  printf("VALS FROM MAIN(LIST2): %c, %c, %c\n", cval0, cval1, cval2);
  printf("PRINTED LIST: ");
  print_list(list2, NULL);
  free_list(list2);
  // UINT_LIST
  List *list3 = create_list(UINT_LIST);
  add_list(list3, 23232);
  add_list(list3, 12345);
  add_list(list3, 6789);
  unsigned uval0, uval1, uval2;
  get_node_val(list3, 0, (list_elem_ptr)&uval0);
  get_node_val(list3, 1, (list_elem_ptr)&uval1);
  get_node_val(list3, 2, (list_elem_ptr)&uval2);
  printf("VALS FROM MAIN(LIST3): %u, %u, %u\n", uval0, uval1, uval2);
  printf("PRINTED LIST: ");
  print_list(list3, NULL);
  free_list(list3);
  printf("AFTER LIST FREE: %d %c %u\n", val0, cval0, uval0);
  return 0;
}

