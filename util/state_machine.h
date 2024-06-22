#ifndef STATE
#define STATE

#include "heap.h"
#include "map.h"

typedef int32_t stat_t;
stat_t stat_init();
stat_t stat_inc(stat_t stat);

typedef struct {
    int_list_t stack;
    // dump_p* dump;
    heap_t* heap;
    map_t* globals;
    stat_t stats;
} state_t;


void stat_apply(state_t* state, stat_t (*stat_fun)(stat_t));

#endif