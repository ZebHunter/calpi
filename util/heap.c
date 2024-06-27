#include "heap.h"
#include "../src/ast.h"

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

void int_list_print(int_list_t* l) {
    int32_t i = 0;
    while(l && i < 50) {
        printf("%d ", l->val);
        l = l->next;
        ++i;
    }
    printf("\n");
}

heap_t* heap_empty() {
    heap_t* heap = malloc(sizeof(heap_t));
    *heap = (heap_t){0};
    int_list_t* l;
    for (uint16_t i = MEM_SIZE; i > 0; --i){
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

void heap_print(heap_t* h) {
    printf("Heap:\n");
    printf("size = %d, addrs = ", h->size);
    int_list_print(h->free);
    printf("mappings:\n");
    for (uint32_t i = 0; i < MEM_SIZE + 1; ++i) {
        if(h->mappings[i]) {
            printf("[%d] ", i);
            heap_node_print(h->mappings[i]);
        }
    }   
}


void heap_node_print(heap_node_t* n) {
    printf("Node: ");
    switch(n->type){
        case N_AP: {
            printf("N_AP ");
            printf("a1 = %d, a2 = %d\n", n->ap->a1, n->ap->a2);
            break;
        }
        case N_Supercomb: {
            printf("N_SuperComb\n");
            printSupercomb(n->supercomb, 0);
            break;
        }
        case N_VAL: {
            printf("N_VAL ");
            printf("val = %d\n", n->n);
            break;
        }
        case N_IND: {
            printf("N_IND ");
            printf("addr = %d\n", n->addr);
            break;
        }
        case N_OP: {
            printf("N_OP ");
            printf("%s\n", n->prim->op_s);
            break;
        }
    }
}