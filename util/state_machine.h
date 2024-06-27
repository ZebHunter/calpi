#ifndef STATE
#define STATE

#include "heap.h"
#include "map.h"
#include "../src/ast.h"


typedef int32_t stat_t;
stat_t stat_init();
stat_t stat_inc(stat_t stat);

typedef struct dump{
    int_list_t* stack;

    struct dump* next;
    struct dump* prev;
} dump_t;

dump_t* dump_empty();
dump_t* dump_push(dump_t* d, int_list_t* st);

typedef struct {
    int_list_t* stack;
    dump_t* dump;
    heap_t* heap;
    map_t* globals;
    stat_t stats;
} state_t;



state_t* state_init();
void stat_apply(state_t* state, stat_t (*stat_fun)(stat_t));

state_t* compile(program_t* program);
void eval(state_t* state);

void print_state(state_t* s);
#endif