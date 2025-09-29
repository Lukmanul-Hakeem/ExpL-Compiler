#ifndef PARSETREE_H
#define PARSETREE_H

#include "./../GlobalSymbolTable/GlobalSymbolTable.h"
#include <stdlib.h>
#include <string.h>

enum node_type {
    NODE_TYPE_WRITE,
    NODE_TYPE_READ,
    NODE_TYPE_CONNECTOR,
    NODE_TYPE_IF_ELSE,
    NODE_TYPE_IF,
    NODE_TYPE_PLUS,
    NODE_TYPE_MINUS,
    NODE_TYPE_MULT,
    NODE_TYPE_DIV,
    NODE_TYPE_ASSIGN,
    NODE_TYPE_VALUE,
    NODE_TYPE_ID,
    NODE_TYPE_LT,
    NODE_TYPE_LE,
    NODE_TYPE_GT,
    NODE_TYPE_GE,
    NODE_TYPE_EQ,
    NODE_TYPE_NE,
    NODE_TYPE_WHILE,
    NODE_TYPE_DO_WHILE,
    NODE_TYPE_REPEAT_UNTIL,
    NODE_TYPE_BREAK,
    NODE_TYPE_CONTINUE,
    NODE_TYPE_STRING,
    NODE_TYPE_ARR_ASSIGN
};

enum node_data_type {
    DATA_TYPE_INTEGER,
    DATA_TYPE_BOOLEAN,
    DATA_TYPE_VOID,
    DATA_TYPE_STRING
};

int var[26];

typedef struct tnode { 
    int val;  
    char* sval;
    int type;            
    int nodetype;         // type of node (read/write/connector/operator/etc.)
    char *varname;        // name of a variable for ID nodes
    Stnode* entry;
    struct tnode *left;   
    struct tnode *right;  
} tnode;

tnode* create_node(int val, char* sval, int type, int nodeType, char* c, Stnode* entry, tnode *left, struct tnode *right);
const char* getNodeSymbol(int nodetype);
void inorder(tnode* root);
int evaluateArithmaticExpr(tnode* root);
int evaluateBooleanExpr(tnode* root);
void evaluate(tnode* root);
void freeTree(tnode* root);

#endif
