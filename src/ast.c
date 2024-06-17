#include "ast.h"
#include <stdlib.h>



struct astNode* newNode(const node_t type)
{
    struct astNode* node = malloc(sizeof(struct astNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeNode(struct astNode* node)
{
    if (node->left) freeNode(node->left);
    else if (node->right) free(node->right);

    free(node);
}



