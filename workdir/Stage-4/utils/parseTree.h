#ifndef PARSETREE_H
#define PARSETREE_H

#include <stdlib.h>
#include <string.h>

/* Forward declare symbol table node type to avoid circular include */
typedef struct Stnode Stnode;

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
    NODE_TYPE_MOD,
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
    NODE_TYPE_ARR_ASSIGN,
    NODE_TYPE_ARR_READ,
    NODE_TYPE_ARRAY,
    NODE_TYPE_2D_ARRAY,
    NODE_TYPE_DEREF,
    NODE_TYPE_REF
};

enum node_data_type {
    DATA_TYPE_INTEGER,
    DATA_TYPE_BOOLEAN,
    DATA_TYPE_VOID,
    DATA_TYPE_STRING,
    DATA_TYPE_ARRAY,
    DATA_TYPE_INTEGER_PTR,
    DATA_TYPE_STRING_PTR
};

int var[26];

typedef struct tnode { 
    int val;  
    char* sval;
    int type;            /* DATA_TYPE_* */
    int nodetype;        /* NODE_TYPE_* */
    char *varname;
    Stnode* entry;       /* pointer to symbol-table node (forward-declared) */
    struct tnode *left;   
    struct tnode *right;  
} tnode;

/* function prototypes - use tnode and Stnode forward decls where needed */
tnode* create_node(int val, char* sval, int type, int nodeType, char* c, Stnode* entry, tnode *left, tnode *right);
tnode* create_array_node(tnode* id, tnode* index);
tnode* create_2D_array_node(tnode* id, tnode* index1, tnode* index2);
tnode* create_id_node(tnode* id);
tnode* create_write_node(tnode* expr);
tnode* create_read_node(tnode* id);
tnode* create_assign_node(tnode* left, tnode* right);
tnode* create_if_node(tnode* condition, tnode* thenBranch);
tnode* create_if_else_node(tnode* condition, tnode* thenBranch, tnode* elseBranch);
tnode* create_while_node(tnode* condition, tnode* body);
tnode* create_do_while_node(tnode* body, tnode* condition);
tnode* create_repeat_until_node(tnode* body, tnode* condition);
tnode* create_arithmetic_node(tnode* left, tnode* right, int operator);
tnode* create_boolean_node(tnode* left, tnode* right, int operator);

tnode* create_deref_node(tnode* id);
tnode* create_addr_node(tnode* id);

const char* getNodeSymbol(int nodetype);
void inorder(tnode* root);
int evaluateArithmaticExpr(tnode* root);
int evaluateBooleanExpr(tnode* root);
void evaluate(tnode* root);
void freeTree(tnode* root);

#endif /* PARSETREE_H */