#include "ast.h"
#include <stdlib.h>



struct astNode* newNode(const node_t type, struct astNode* left, struct astNode* right)
{
    struct astNode* node = malloc(sizeof(struct astNode));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}

struct astNode* newVarNode(const char* name){
    struct astNode* node = newNode(VAR_T, NULL, NULL);
    node->name = name;
    return node;
}

void freeNode(struct astNode* node)
{
    if (node->left) freeNode(node->left);
    else if (node->right) free(node->right);

    free(node);
}



