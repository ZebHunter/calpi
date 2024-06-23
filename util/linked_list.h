#ifndef LINKED_LIST
#define LINKED_LIST


#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>



#define LinkedList(typename) struct linked_list_##typename

#define ListNode(typename) struct list_node_##typename

#define popListFunc(type, typename) \
    type popList_##typename(LinkedList(typename)* list) {   \
        ListNode(typename)* node = list->tail;  \
        list->tail = list->tail->prev;             \
        type val = node->data;          \
        unlinkNode(node);               \
        free(node);         \
        return val;            \
    }

#define popHeadListFunc(type, typename) \
    type popHeadList_##typename(LinkedList(typename)* list) {   \
        ListNode(typename)* node = list->head;  \
        list->head = list->head->next;             \
        type val = node->data;          \
        unlinkNode(node);               \
        free(node);         \
        return val;            \
    }

#define declareList(type, typename) \
    LinkedList(typename) {  \
        ListNode(typename)* head;   \
        ListNode(typename)* tail;    \
    };  \
    ListNode(typename) {    \
        type data;  \
        ListNode(typename)* next;     \
        ListNode(typename)* prev;   \
    };  \
    popHeadListFunc(type, typename); \
    popListFunc(type, typename)

#define initList(type) malloc(sizeof(LinkedList(type)))

#define initNode(type) malloc(sizeof(ListNode(type)))

#define linkNodes(node1, node2) do {    \
    if(node1) node1->next = node2;      \
    if(node2) node2->prev = node1;      \
} while(0)

#define unlinkNode(node) do {      \
    if(!node) break;   \
    if(node->next) node->next->prev = node->prev;   \
    if(node->prev) node->prev-> next = node->next;  \
    node->prev = NULL;                              \
    node->next = NULL;                              \
} while(0)

#define llistPush(type, l, el) do { \
    if (!l) l = initList(type);     \
    ListNode(type)* node = initNode(type);      \
    node->data = el;                            \
    linkNodes(l->tail, node);                    \
    l->tail = node;                              \
    if(!l->head) l->head = node;                \
} while(0)

#define llistAppendHead(type, l, el) do { \
    if (!l) l = initList(type);     \
    ListNode(type)* node = initNode(type);      \
    node->data = el;                            \
    linkNodes(node, l->head);                    \
    l->head = node;                              \
    if(!l->tail) l->tail = node;                \
} while(0)

#define popList(type, list) popList_##type(list)

#define popHeadList(type, list) popHeadList_##type(list)

#define getData(node) ((node)->data)

#define freeList(type, list) do {       \
    ListNode(type) *cur = list->head, *prev = NULL;        \
    while(cur) {        \
        prev = cur;     \
        cur = cur->next;    \
        free(prev); \
    }   \
    free(list); \
} while(0)

#define listForEach(type, list, node)   \
    ListNode(type)* node;   \
    for(node = list->head; node != NULL; node = node->next)

#define concate(l1, l2) do {    \
   linkNodes(l1->tail, l2->head);   \
} while(0)

#endif