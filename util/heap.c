#include "heap.h"




heap_t* heap_empty() {
    heap_t* heap = malloc(sizeof(heap_t));
    *heap = (heap_t){0};
    int_list_t* l;
    for (uint16_t i = 65535; i > 0; --i){
        l = malloc(sizeof(int_list_t));
        l->next = heap->free;
        if(heap->free) heap->free->prev = l;
        l->val = i;
        heap->free = l;
    }
    return heap;
}

addr_t heap_alloc(heap_t* heap, node_t* node) {
    heap->size += 1;
    addr_t addr = heap->free->val;
    heap->mappings[addr] = node;
    heap->free = heap->free->next;
    return addr;
}

void heap_update(heap_t* heap, addr_t addr, node_t* node){
    heap->mappings[addr] = node;
}

void heap_free(heap_t* heap, addr_t addr) {
    heap->size -= 1;
    heap->mappings[addr] = 0;
}

node_t* heap_find(heap_t* heap, addr_t addr){
    return heap->mappings[addr];
}