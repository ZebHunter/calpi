
#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdlib.h>

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

#endif //AST_H