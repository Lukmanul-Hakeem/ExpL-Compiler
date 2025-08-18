#include "parseTree.h"

tnode* create_node(int val, int type, char* c, struct tnode *left, struct tnode *right) {
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed in create_node\n");
        exit(1);
    }

    newNode->val = val;
    newNode->nodetype = type;

    if (c != NULL) {
        newNode->varname = strdup(c);  // copy string safely
    } else {
        newNode->varname = NULL;
    }

    newNode->left = left;
    newNode->right = right;

    return newNode;
}

const char* getNodeSymbol(int nodetype) {
    switch (nodetype) {
        case NODE_TYPE_PLUS: return "+";
        case NODE_TYPE_MINUS: return "-";
        case NODE_TYPE_MULT: return "*";
        case NODE_TYPE_DIV: return "/";
        case NODE_TYPE_ASSIGN: return "=";
        case NODE_TYPE_READ: return "READ";
        case NODE_TYPE_WRITE: return "WRITE";
        case NODE_TYPE_CONNECTOR: return "CONNECTOR";
        default: return "?";
    }
}

void inorder(tnode* root) {
    if (root == NULL) return;

    if (root->nodetype == NODE_TYPE_ID) {
        printf("%s ", root->varname ? root->varname : "NULL");
    } else if (root->nodetype == NODE_TYPE_VALUE) {
        printf("%d ", root->val);
    } else {
        inorder(root->left);
        printf("%s ", getNodeSymbol(root->nodetype));
        inorder(root->right);
    }
}

void freeTree(tnode* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);

    if (root->varname != NULL) {
        free(root->varname);
    }
    free(root);
}