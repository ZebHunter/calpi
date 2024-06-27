#include "state_machine.h"

#include <stdio.h>

dump_t* dump_empty() {
    return (dump_t*) 0;
}

dump_t* dump_init(int_list_t* val) {
    dump_t* d = malloc(sizeof(dump_t));
    d->stack = val;
    return d;
}

dump_t* dump_push(dump_t* d, int_list_t* st) {
    dump_t* new = dump_init(st);
    new->next = d;
    return new;
}

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

typedef struct prims_{
    char* s;
    prim_e e;

    struct prims_* next;
} prims_tmp;

prims_tmp* create_prims() {
    prims_tmp* p1 = malloc(sizeof(prims_tmp));
    p1->s = "!=";
    p1->e = NON_EQ_P;
    p1->next = 0;

    prims_tmp* p2 = malloc(sizeof(prims_tmp));
    p2->s = "==";
    p2->e = EQ_P;
    p2->next = p1;

    prims_tmp* p3 = malloc(sizeof(prims_tmp));
    p3->s = "<=";
    p3->e = LT_EQ_P;
    p3->next = p2;

    prims_tmp* p4 = malloc(sizeof(prims_tmp));
    p4->s = "<";
    p4->e = LT_P;
    p4->next = p3;

    prims_tmp* p5 = malloc(sizeof(prims_tmp));
    p5->s = ">=";
    p5->e = GT_EQ_P;
    p5->next = p4;

    prims_tmp* p6 = malloc(sizeof(prims_tmp));
    p6->s = ">";
    p6->e = GT_P;
    p6->next = p5;

    prims_tmp* p7 = malloc(sizeof(prims_tmp));
    p7->s = "||";
    p7->e = OR_P;
    p7->next = p6;

    prims_tmp* p8 = malloc(sizeof(prims_tmp));
    p8->s = "&&";
    p8->e = AND_P;
    p8->next = p7;

    prims_tmp* p9 = malloc(sizeof(prims_tmp));
    p9->s = "*";
    p9->e = MUL_P;
    p9->next = p8;

    prims_tmp* p10 = malloc(sizeof(prims_tmp));
    p10->s = "%";
    p10->e = MOD_P;
    p10->next = p9;

    prims_tmp* p11 = malloc(sizeof(prims_tmp));
    p11->s = "/";
    p11->e = DIV_P;
    p11->next = p10;

    prims_tmp* p12 = malloc(sizeof(prims_tmp));
    p12->s = "-";
    p12->e = SUB_P;
    p12->next = p11;

    prims_tmp* p13 = malloc(sizeof(prims_tmp));
    p13->s = "+";
    p13->e = ADD_P;
    p13->next = p12;

    return p13;
}

tmp build_init_heap(program_t* defs) {
    heap_t* h = heap_empty();
    map_t* m = map_empty();
    heap_node_t* node;
    addr_t addr;
    while(defs) {
        node = malloc(sizeof(heap_node_t));
        node->type = N_Supercomb;
        node->supercomb = defs->definition;
        addr = heap_alloc(h, node);
        map_add(&m, defs->definition->name, addr);
        defs = defs->next;
    }
    prims_tmp* prims = create_prims(); 
    prims_tmp* next;
    while(prims) {
        node = malloc(sizeof(heap_node_t));
        node->type = N_OP;
        node->prim = malloc(sizeof(prim_t));
        node->prim->op_e = prims->e;
        node->prim->op_s = prims->s;
        addr = heap_alloc(h, node);
        map_add(&m, prims->s, addr);
        next = prims->next;
        free(prims);
        prims = next;
    }    

    return (tmp){.heap = h, .globals = m};
}

state_t* compile(program_t* program) {
    program_t* defs = program; // ++ preludeDefs ++ extraDefs
    tmp init = build_init_heap(defs);

    addr_t main_addr = map_find(init.globals, "main");
    if (!main_addr) {
        //ERROR JOPA JOPA JOPA
        return (void *)0;
    }

    int_list_t* init_stack = list_init(main_addr);
    state_t* init_state = state_init();
    init_state->stack = init_stack;
    init_state->globals = init.globals;
    init_state->heap = init.heap;
    init_state->stats = stat_init();
    init_state->dump = dump_empty();

    return init_state;
}


addr_t instantiate(expr_t* expr, heap_t* heap, map_t* env);
map_t* instantiate_defs(defs_list_t* d, heap_t* heap, map_t* env) {
    map_t* bindings = map_empty();
    while(d) {
        map_add(&bindings, d->name, instantiate(d->def_body, heap, env));
        d = d->next;
    }
    return bindings;
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
            n->ap  = malloc(sizeof(ap_t));
            n->ap->a1 = instantiate(expr->ap->left, heap, env);
            n->ap->a2 = instantiate(expr->ap->right, heap, env);
            return heap_alloc(heap, n);
        }
        case E_VAR: {
            addr_t addr = map_find(env, expr->name);
            if (!addr); // JOPA JOPA JOPA UNDEF NAME;
            return addr;
        }
        case E_CASE: {
            //JOPA JOPA CASE INSTANT JOPA
            return 0;
        }
        case E_LET: {
            map_t* bindings = instantiate_defs(expr->let->defs, heap, env);
            map_t* env1 = map_concat(bindings, env);
            return instantiate(expr->let->body, heap, env1);
        }
    }
}

void instantiate_and_update(expr_t* expr, addr_t addr, heap_t* heap, map_t* env) {
    switch (expr->type) {
    case E_VAR:{
        heap_node_t* n = malloc(sizeof(heap_node_t));
        n->type = N_IND;
        n->addr = map_find(env, expr->name);
        return heap_update(heap, addr, n);
    }
    case E_VAL:{
        heap_node_t* n = malloc(sizeof(heap_node_t));
        n->type = N_VAL;
        n->n = expr->val;
        return heap_update(heap, addr, n);
    }
    case E_AP:{
        heap_node_t* n = malloc(sizeof(heap_node_t));
        n->type = N_AP;
        n->ap = malloc(sizeof(ap_t));
        n->ap->a1 = instantiate(expr->ap->left, heap, env);
        n->ap->a2 = instantiate(expr->ap->right, heap, env);
        return heap_update(heap, addr, n);
    }
    case E_LET:{
        heap_node_t* n = malloc(sizeof(heap_node_t));
        n->type = N_IND;
        n->addr = instantiate(expr, heap, env);
        return heap_update(heap, addr, n);
    }
    case E_CASE: {
        //JOPA JOPA CASE INSTANT JOPA
        return;
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
    if (!state->stack) {
        state->stack = state->dump->stack;
        state->dump = state->dump->next;
    }
    else //JOPA JOPA JOPA
    return;
}

void ap_step(state_t* state, ap_t* ap) {
    heap_node_t* node = heap_find(state->heap, ap->a2);
    if(node->type == N_IND) {
        heap_node_t* n = malloc(sizeof(heap_node_t));
        n->type = N_AP;
        n->ap = malloc(sizeof(ap_t));
        n->ap->a1 = ap->a1;
        n->ap->a2 = node->addr;
        heap_update(state->heap, state->stack->val, n);
    }
    else {
        state->stack = list_push(state->stack, ap->a1);
    }
}

void ind_step(state_t* state, addr_t a) {
    state->stack->val = a;
}

void supercomb_step(state_t* state, supercomb_t* sc) {
    map_t* arg_bindings = map_empty();
    string_list_t* name = sc->args;
    int_list_t* stack = state->stack;
    int len = 0;
    while (name) {
        map_add(&arg_bindings, name->str, heap_find(state->heap, stack->next->val)->ap->a2);
        name = name->next;
        stack = stack->next;
        ++len;
    }
    map_t* env = map_concat(arg_bindings, state->globals);
    instantiate_and_update(sc->body, stack->val, state->heap, env);
    state->stack = list_drop(state->stack, len);
}

void prim_step(state_t* state, prim_e op) {
    addr_t b1 = heap_find(state->heap, state->stack->next->val)->ap->a2;
    addr_t b2 = heap_find(state->heap, state->stack->next->next->val)->ap->a2;
    heap_node_t* n1 = heap_find(state->heap, b1);
    heap_node_t* n2 = heap_find(state->heap, b2);

    if (n1->type == N_VAL && n2->type == N_VAL) {
        heap_node_t* n_res = malloc(sizeof(heap_node_t));
        n_res->type = N_VAL;
        switch (op) {
            case ADD_P: {
                n_res->n = n1->n + n2->n;
                break;
            }
            case SUB_P: {
                n_res->n = n1->n - n2->n;
                break;
            }
            case DIV_P: {
                n_res->n = n1->n / n2->n;
                break;
            }
            case MOD_P: {
                n_res->n = n1->n % n2->n;
                break;
            }
            case MUL_P: {
                n_res->n = n1->n * n2->n;
                break;
            }
            case AND_P: {
                n_res->n = n1->n && n2->n;
                break;
            }
            case OR_P: {
                n_res->n = n1->n || n2->n;
                break;
            }
            case GT_P: {
                n_res->n = n1->n > n2->n;
                break;
            }
            case GT_EQ_P: {
                n_res->n = n1->n >= n2->n;
                break;
            }
            case LT_P: {
                n_res->n = n1->n < n2->n;
                break;
            }
            case LT_EQ_P: {
                n_res->n = n1->n <= n2->n;
                break;
            }
            case EQ_P: {
                n_res->n = n1->n == n2->n;
                break;
            }
            case NON_EQ_P: {
                n_res->n = n1->n != n2->n;
                break;
            }
        }
        addr_t b_res = heap_alloc(state->heap, n_res);
        heap_update(state->heap, state->stack->next->next->val, n_res);
        state->stack = list_init(b_res);
        //AAAAAAAAAAAAa
        printf("?res = %d\n", n_res->n);
        return;
    }
    else {
        dump_push(state->dump, state->stack->next->next);
        dump_push(state->dump, list_init(b1));
        state->stack = list_init(b2);
        return;
    }
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
    case N_IND:
        return ind_step(state, node->addr);
    case N_OP:
        return prim_step(state, node->prim->op_e);
    default:
        //JOPA JOPA JOPA
        break;
    }
}

void eval(state_t* state) {
    // print_state(state);
    if (is_final(state)) return;
    step(state);
    admin(state);
    eval(state);
}

void dump_print(dump_t * d) {
    printf("Dump:\n");
    while(d) {
        int_list_print(d->stack);
        d = d->next;
    }
}

void print_state(state_t* s) {
    printf("State:\n");
    printf("stack: ");
    int_list_print(s->stack);

    dump_print(s->dump);
    heap_print(s->heap);
    map_print(s->globals);
    printf("stat = %d\n###########################################\n\n", s->stats);

}