
#ifndef AST_H
#define AST_H


typedef enum nodeType node_t;

struct astNode
{
    node_t type;
    struct astNode* left;
    struct astNode* right;
};

struct astNode* newNode(node_t type);

void freeNode(struct astNode*);



#endif //AST_H
