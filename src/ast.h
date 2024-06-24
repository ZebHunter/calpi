
#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "../util/node.h"

typedef enum nodeType{
    SUPERCOMB_T,
    DEFINITION_T,
    VAR_T,
    EXPRESSION_T,
    VAL_T,
    ALT_T,
    AEXPR_T,
    PLUS_T,
    MINUS_T,
    MUL_T,
    DIV_T,
    MOD_T,
    AND_T,
    OR_T,
    LESS_T,
    LESS_EQ_T,
    GT_T,
    GT_EQ_T,
    EQ_T,
    NONEQ_T,
    LET_T,
    CASE_T,
    LAMBDA_T
} node_t;


struct list{
    struct astNode* node;
    struct list* next;
};

struct list* initNode(struct astNode* ast){
    struct list* node = malloc(sizeof(struct list));
    node->node = ast;
    node->next = NULL;
    return node;
}

struct list* addNode(struct astNode* node, struct list* cur){
    struct list* new = initNode(node);
    cur->next = new;
    return new;
}

struct astNode
{
    node_t type;
    struct astNode* left;
    struct astNode* right;
    union {
        char* name;
        int val;
    };
};

struct astNode* newNode(node_t type, struct astNode* left, struct astNode* right);

void freeNode(struct astNode*);

struct astNode* newVarNode(const char* name);

program_t* addProgramNode(supercomb_t* comb, program_t* next){
    program_t* program = malloc(sizeof(program_t));
    program->definition = comb;
    program->next = next;
    return program;
}

supercomb_t* addSupercomb(string_list_t* args, expr_t* expr){
    supercomb_t* comb = malloc(sizeof(supercomb_t));
    char* name = args->str;
    args = args->next;
    args->prev = NULL;
    comb->name = name;
    comb->args = args;
    comb->body = expr;
    return comb;
}

string_list_t* addArgsList(const char* name, string_list_t* list){
    string_list_t* args = malloc(sizeof(string_list_t));
    args->str = name;
    args->next = list;
    return args;
}

defs_list_t* addDefsList(defs_list_t* defun, defs_list_t* list){
    defun->next = list;
    list->prev = defun;
    return defun;
}

defs_list_t* addDefun(const char* name, expr_t* expr){
    defs_list_t* defun = malloc(sizeof(defs_list_t));
    defun->name = name;
    defun->def_body = expr;
    return defun;
}

expr_t* addLetExpr(defs_list_t* defuns, expr_t* expr){
    expr_t* let = malloc(sizeof(expr_t));
    let->type = E_LET;
    let->let = malloc(sizeof(e_let_t));
    let->let->defs = defuns;
    let->let->body = expr;
    let->let->is_rec = false;
    return let;
}

expr_t* addCaseExpr(expr_t* expr, alt_list_t* alts){
    expr_t* case_ex = malloc(sizeof(expr_t));
    case_ex->type = E_CASE;
    case_ex->my_case = malloc(sizeof(e_case_t));
    case_ex->my_case->case_val = expr;
    case_ex->my_case->alts = alts;
    return case_ex;
}

alt_t* addAlt(int32_t case_num, string_list_t* list, expr_t* expr){
    alt_t* alt = malloc(sizeof(alt_t));
    alt->case_num = case_num;
    alt->bounded_vars = list;
    alt->body = expr;
    return alt;
}

alt_list_t* addAltList(alt_t* alt, alt_list_t* list){
    alt_list_t* node = malloc(sizeof(alt_list_t));
    node->alt = alt;
    node->next = list;
    if(list) list->prev = node;
    return node;
}

expr_t* addLambda(string_list_t* vars, expr_t* expr){
    expr_t* lambda = malloc(sizeof(expr_t));
    lambda->type = E_LAM;
    lambda->lambda = malloc(sizeof(e_lam_t));
    lambda->lambda->bounded_vars = vars;
    lambda->lambda->body = expr;
    return lambda;
}

expr_t* wrapperExprOperation(expr_t* expr1, expr_t* expr2){
    expr_t* e = malloc(sizeof(expr_t));
    e->type = E_AP;
    e->ap = malloc(sizeof(e_ap_nodes));
    e->ap->left = expr1;
    e->ap->right = expr2;
    return e;
}

expr_t* addExprOperation(const char* operation, expr_t* expr){
    expr_t* oper = malloc(sizeof(expr_t));
    oper->type = E_VAR;
    oper->name = operation;
    expr_t* e = malloc(sizeof(expr_t));
    e->type = E_AP;
    e->ap = malloc(sizeof(e_ap_nodes));
    e->ap->left = oper;
    e->ap->right = expr;
    return e;
}

expr_t* addAexprVar(const char* var){
    expr_t* expr = malloc(sizeof(expr_t));
    expr->type = E_VAR;
    expr->name = var;
    return expr;
}

expr_t* addAexprDigit(int32_t num){
    expr_t* expr = malloc(sizeof(expr_t));
    expr->type = E_VAL;
    expr->val = num;
    return expr;
}

// expr_t* addAexprExp(expr_t* expr){
//     return expr;
// }


#endif //AST_H