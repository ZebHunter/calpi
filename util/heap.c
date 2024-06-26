#include "heap.h"

int_list_t* list_init(addr_t val) {
    int_list_t* l = malloc(sizeof(int_list_t));
    l->val = val;
    return l;
}

int_list_t* list_push(int_list_t* l, addr_t val) {
    int_list_t* new = list_init(val);
    new->next = l;
    return new;
}

int_list_t* list_concat(int_list_t* l1, int_list_t* l2) {
    if(!l1) return l2;
    int_list_t* l = l1;
    while(l1->next) {
        l1 = l1->next;
    }
    l1->next = l2;
    return l;
}

void list_free(int_list_t* l) {
    free(l);
}

int_list_t* list_drop(int_list_t* l, int32_t n) {
    int_list_t* prev = l;
    for (int32_t i = 0; i < n && l; ++i) {
        prev = l;
        l = l->next;
        list_free(prev);
    }
    return l;
}

heap_t* heap_empty() {
    heap_t* heap = malloc(sizeof(heap_t));
    *heap = (heap_t){0};
    int_list_t* l;
    for (uint16_t i = 65535; i > 0; --i){
        l = malloc(sizeof(int_list_t));
        l->next = heap->free;
        l->val = i;
        heap->free = l;
    }
    return heap;
}

addr_t heap_alloc(heap_t* heap, heap_node_t* node) {
    heap->size += 1;
    addr_t addr = heap->free->val;
    heap->mappings[addr] = node;
    heap->free = heap->free->next;
    return addr;
}

void heap_update(heap_t* heap, addr_t addr, heap_node_t* node){
    heap->mappings[addr] = node;
}

void heap_free(heap_t* heap, addr_t addr) {
    heap->size -= 1;
    heap->mappings[addr] = 0;
}

heap_node_t* heap_find(heap_t* heap, addr_t addr){
    return heap->mappings[addr];
}