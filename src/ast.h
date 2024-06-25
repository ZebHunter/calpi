
#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include "../util/node.h"


program_t* addProgramNode(supercomb_t* comb, program_t* next);

supercomb_t* addSupercomb(string_list_t* args, expr_t* expr);

string_list_t* addArgsList(char* name, string_list_t* list);

defs_list_t* addDefsList(defs_list_t* defun, defs_list_t* list);

defs_list_t* addDefun(char* name, expr_t* expr);

expr_t* addLetExpr(defs_list_t* defuns, expr_t* expr);

expr_t* addCaseExpr(expr_t* expr, alt_list_t* alts);

alt_t* addAlt(int32_t case_num, string_list_t* list, expr_t* expr);

alt_list_t* addAltList(alt_t* alt, alt_list_t* list);

expr_t* addLambda(string_list_t* vars, expr_t* expr);

expr_t* wrapperExprOperation(expr_t* expr1, expr_t* expr2);

expr_t* addExprOperation(char* operation, expr_t* expr);

expr_t* addAexprVar(char* var);

expr_t* addAexprDigit(int32_t num);

void printProgram(program_t* program);

void printVars(string_list_t* list);

void printSupercomb(supercomb_t* supercomb);

void printExpr(expr_t* expr);


#endif //AST_H