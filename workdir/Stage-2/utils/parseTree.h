#ifndef PARSETREE_H
#define PARSETREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum node_type {
    NODE_TYPE_WRITE,
    NODE_TYPE_READ,
    NODE_TYPE_CONNECTOR,
    NODE_TYPE_PLUS,
    NODE_TYPE_MINUS,
    NODE_TYPE_MULT,
    NODE_TYPE_DIV,
    NODE_TYPE_VALUE,
    NODE_TYPE_ID,
    NODE_TYPE_ASSIGN,
};

typedef struct tnode { 
    int val;              
    int nodetype;         // type of node (read/write/connector/operator/etc.)
    char *varname;        // name of a variable for ID nodes
    struct tnode *left;   
    struct tnode *right;  
} tnode;

tnode* create_node(int val, int type, char* c, struct tnode *left, struct tnode *right);
const char* getNodeSymbol(int nodetype);
void inorder(tnode* root);
void freeTree(tnode* root);

#endif