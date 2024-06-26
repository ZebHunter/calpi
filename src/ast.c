#include "ast.h"
#include <stdlib.h>
#include <stdio.h>



program_t* addProgramNode(supercomb_t* comb, program_t* next){
    program_t* program = malloc(sizeof(program_t));
    program->definition = comb;
    program->next = next;
    return program;
}

supercomb_t* addSupercomb(string_list_t* args, expr_t* expr){
    supercomb_t* comb = malloc(sizeof(supercomb_t));
    char* name = args->str;
    if (args->next) args = args->next;
    args->prev = NULL;
    comb->name = name;
    comb->args = args;
    comb->body = expr;
    return comb;
}

string_list_t* addArgsList(char* name, string_list_t* list){
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

defs_list_t* addDefun(char* name, expr_t* expr){
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

expr_t* addExprOperation(char* operation, expr_t* expr){
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

expr_t* addAexprVar(char* var){
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

void printProgram(program_t* program){
    for (program_t* node = program; node != NULL; node = node->next){
        printSupercomb(node->definition, 0);
    } 
}

void printVars(string_list_t* list , int32_t lvl){
    for (string_list_t* node = list; node != NULL; node = node->next){
        printf("%*sVar: %s\n", lvl, "", node->str);
    }
}

void printSupercomb(supercomb_t* supercomb, int32_t lvl){
    printf("%*sName = %s\n", lvl, "", supercomb->name);
    printVars(supercomb->args, lvl);
    printExpr(supercomb->body, lvl);
}

void printExpr(expr_t* expr , int32_t lvl){
    switch(expr->type){
        case E_VAR:
            printf("%*sExpression var: %s\n", lvl+1, "", expr->name);
            break;
        case E_VAL:
            printf("%*sExpression value: %d\n", lvl+1, "",  expr->val);
            break;
        case E_AP:
            printApExpr(expr->ap, lvl+1);
            break;
        case E_LET:
            printLetExpression(expr->let, lvl+1);
            break;
        case E_CASE:
            printCaseExpr(expr->my_case, lvl+1);
            break;
        case E_LAM:
            printLambdaExpr(expr->lambda, lvl+1);
    }
}

void printAlt(alt_t* alt, int32_t lvl){
    printf("%*sCase_num: %d\n", lvl+1, "",  alt->case_num);
    printVars(alt->bounded_vars,lvl+1);
    printExpr(alt->body, lvl+1);
}

void printAlts(alt_list_t* alts, int32_t lvl){
    for(alt_list_t* node = alts; node != NULL; node = node->next){
        printAlt(node->alt, lvl);
    }
}

void printDefs(defs_list_t* defs, int32_t lvl){
    for(defs_list_t* node = defs; node != NULL; node = node->next){
        printf("%*sFunc name: %s\n", lvl+1, "",  defs->name);
        printExpr(defs->def_body, lvl+1);
    }
}

void printCaseExpr(e_case_t* expr, int32_t lvl){
    printExpr(expr->case_val, lvl+1);
    printAlts(expr->alts, lvl+1);
}

void printLambdaExpr(e_lam_t* expr, int32_t lvl){
    printVars(expr->bounded_vars, lvl+1);
    printExpr(expr->body, lvl+1);
}

void printLetExpression(e_let_t* expr, int32_t lvl){
    printDefs(expr->defs, lvl+1);
    printExpr(expr->body, lvl+1);
}

void printApExpr(e_ap_nodes* expr, int32_t lvl){
    if(expr->left) printExpr(expr->left, lvl+1);
    if(expr->right) printExpr(expr->right, lvl+1);
}

