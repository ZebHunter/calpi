#include "state_machine.h"


stat_t stat_init() {
    return 0;
}

stat_t stat_inc(stat_t stat) {
    return stat + 1;
}

void stat_apply(state_t* state, stat_t (*stat_fun)(stat_t)){
    state->stats = stat_fun(state->stats);
}

state_t* state_init() {
    state_t* s = malloc(sizeof(state_t));
    return s;
}

typedef struct {
    heap_t* heap;
    map_t* globals;
} tmp;


tmp* build_init_heap(supercomp_t* defs) {
    heap_t* h = heap_empty();
    
}

state_t* compile(program_t* program) {
    supercomp_t* defs = program->definition; // ++ preludeDefs ++ extraDefs
    tmp* init = build_init_heap(defs);

    addr_t main_addr = map_find(init->globals, "main");
    if (!main_addr) {
        //ERROR JOPA JOPA JOPA
        return -1;
    }

    int_list_t* init_stack = list_init(main_addr);
    state_t* init_state = state_init();
    init_state->stack = init_stack;
    init_state->globals = init->globals;
    init_state->heap = init->heap;
    init_state->stats = stat_init();
    // init_state->dump = dump_init();

    return init_state;
}
