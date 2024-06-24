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


tmp build_init_heap(program_t* defs) {
    heap_t* h = heap_empty();
    map_t* m = map_empty();
    while(defs) {
        heap_node_t* node = malloc(sizeof(heap_node_t));
        node->type = N_Supercomb;
        node->supercomb = defs->definition;
        addr_t addr = heap_alloc(h, node);
        map_add(&m, defs->definition->name, (void*)addr);

        defs = defs->next;
    }
    return (tmp){.heap = h, .globals = m};
}

state_t* compile(program_t* program) {
    program_t* defs = program; // ++ preludeDefs ++ extraDefs
    tmp init = build_init_heap(defs);

    addr_t main_addr = map_find(init.globals, "main");
    if (!main_addr) {
        //ERROR JOPA JOPA JOPA
        return -1;
    }

    int_list_t* init_stack = list_init(main_addr);
    state_t* init_state = state_init();
    init_state->stack = init_stack;
    init_state->globals = init.globals;
    init_state->heap = init.heap;
    init_state->stats = stat_init();
    // init_state->dump = dump_init();

    return init_state;
}

addr_t instantiate(expr_t* expr, heap_t* heap, map_t* env) {
    switch (expr->type) {
    case E_VAL: {
        heap_node_t* n = malloc(sizeof(heap_node_t));
        n->type = N_VAL;
        n->n = expr->val;
        return heap_alloc(heap, n);
    }
    case E_AP: {
        heap_node_t* n = malloc(sizeof(heap_node_t));
        n->type = N_AP;
        n->ap  = (ap_t){.a1 = instantiate(expr->ap.left, heap, env),
                        .a2 = instantiate(expr->ap.right, heap, env)
                        };
        return heap_alloc(heap, n);
    }
    case E_VAR: {
        addr_t addr = map_find(env, expr->name);
        if (!addr) // JOPA JOPA JOPA UNDEF NAME;
        return addr;
    }
    case E_CASE: {
        //JOPA JOPA CASE INSTANT JOPA
        return -1;
    }
    default:
        break;
    }
}

bool is_final(state_t* state) {
    if (!state->stack) return true;
    if(!(state->stack->next) && heap_find(state->heap, state->stack->val)->type == N_VAL) return true;
    return false;
}

void admin(state_t* state) {
    stat_apply(state, stat_inc);
}

void num_step(state_t* state, int32_t val) {
    //JOPA JOPA JOPA INT ON STACK;
    return;
}

void ap_step(state_t* state, ap_t ap) {
    state->stack = list_push(state->stack, ap.a1);
}

void supercomb_step(state_t* state, supercomb_t* sc) {
    map_t* arg_bindings = map_empty();
    string_list_t* name = sc->args;
    int_list_t* stack = state->stack->next;
    int len = 0;
    while (name) {
        map_add(&arg_bindings, name->str, heap_find(state->heap, stack->val));
        name = name->next;
        stack = stack->next;
        len++;
    }

    map_t* env = map_concat(arg_bindings, state->globals);

    addr_t result_addr = instantiate(sc->body, state->heap, env);

    state->stack = list_drop(state->stack, len + 1);
    state->stack = list_push(state->stack, result_addr);
}

void step(state_t* state) {
    heap_node_t* node = heap_find(state->heap, state->stack->val);
    switch (node->type) {
    case N_VAL:
        return num_step(state, node->n);
    case N_AP:
        return ap_step(state, node->ap);
    case N_Supercomb:
        return supercomb_step(state, node->supercomb);
    default:
        //JOPA JOPA JOPA
        break;
    }
}

void eval(state_t* state) {
    if (is_final(state)) return;
    step(state);
    admin(state);
    eval(state);
}
