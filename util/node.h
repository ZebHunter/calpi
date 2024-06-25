#ifndef NODE
#define NODE

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    E_VAR,
    E_VAL,
    E_AP,
    E_LET,
    E_CASE,
    E_LAM,
} expr_type_e;

typedef struct {
    //if letrec exists
    bool is_rec;
    struct defs_list* defs;
    struct expr* body;
} e_let_t;

typedef struct {
    struct expr* left;
    struct expr* right;
} e_ap_nodes;

typedef struct {
    struct expr* case_val;
    struct alt_list* alts;
} e_case_t;

typedef struct {
    struct string_list* bounded_vars;
    struct expr* body;
} e_lam_t;

typedef struct expr{
    expr_type_e type;
    union {
        char* name;
        int32_t val;
        e_ap_nodes* ap;
        e_let_t* let;
        e_case_t* my_case;
        e_lam_t* lambda;
    };
} expr_t;

typedef struct string_list {
    char* str;

    struct string_list* next;
    struct string_list* prev;
} string_list_t;

typedef struct{
    char* name;
    string_list_t* args;
    expr_t* body;
} supercomb_t;

typedef struct program {
    struct program* next;
    struct program* prev;
    supercomb_t* definition;
} program_t;

typedef struct defs_list {
    char* name;
    expr_t* def_body;

    struct defs_list* next;
    struct defs_list* prev;
} defs_list_t;

typedef struct {
    int32_t case_num;
    string_list_t* bounded_vars;
    expr_t* body;
} alt_t;

typedef struct alt_list {
    alt_t* alt;

    struct alt_list* next;
    struct alt_list* prev;
} alt_list_t;

#endif