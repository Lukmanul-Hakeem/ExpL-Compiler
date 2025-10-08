#include "parse_tree.h"

struct ASTNode* create_ast_node(int nodetype, char *name, union Constant value) {
    struct ASTNode *node = (struct ASTNode*)malloc(sizeof(struct ASTNode));
    if (!node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    node->nodetype = nodetype;
    node->name = name ? strdup(name) : NULL;  // duplicate string if not NULL
    node->value = value;                       // set the constant value

    node->type = NULL;
    node->arglist = NULL;

    node->ptr1 = node->ptr2 = node->ptr3 = NULL;
    
    node->Gentry = NULL;
    node->Lentry = NULL;

    return node;
}