#ifndef HEAP
#define HEAP

#include <stdint.h>
#include <stdlib.h>
#include "map.h"
#include "node.h"

#define MEM_SIZE 65535
typedef uint16_t addr_t;

typedef struct int_list{
    addr_t val;
    struct int_list* next;
    struct int_list* prev;
} int_list_t;

typedef enum {
    N_AP,
    N_Supercomb,
    N_VAL,
    N_IND,
    N_OP,
} heap_node_type_e;

typedef enum {
    ADD,
    SUB,
    DIV,
    MOD,
    MUL,
    AND,
    OR,
    GT,
    GT_EQ,
    LT,
    LT_EQ,
    EQ,
    NON_EQ
} prim_e;

typedef struct {
    prim_e op_e;
    char* op_s;
} prim_t;

typedef struct {
    heap_node_type_e type;

    union {
        ap_t* ap;
        supercomb_t* supercomb;
        int32_t n;
        addr_t addr;
        prim_t* prim;
    };

} heap_node_t;

typedef struct{
    addr_t a1;
    addr_t a2;
} ap_t;

typedef struct {
    uint16_t size;
    int_list_t* free;
    heap_node_t* mappings[MEM_SIZE + 1];
} heap_t;

int_list_t* list_init(addr_t val);
int_list_t* list_push(int_list_t* l, addr_t val);
int_list_t* list_concat(int_list_t* l1, int_list_t* l2);
void list_free(int_list_t* l);
int_list_t* list_drop(int_list_t* l, int32_t n);


heap_t* heap_empty();
addr_t heap_alloc(heap_t* heap, heap_node_t* node);
void heap_update(heap_t* heap, addr_t addr, heap_node_t* node);
void heap_free(heap_t* heap, addr_t addr);

heap_node_t* heap_find(heap_t* heap, addr_t addr);

#endif