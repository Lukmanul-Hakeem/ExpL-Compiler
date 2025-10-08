#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ASTNode ast_node;

union Constant{
    int iVal;
    char* sVal;
};

struct ASTNode{
  struct Typetable *type;           //pointer to the type table entry
  int nodetype;                     //node type information,eg : NODETYPE_WHILE,NODETYPE_PLUS,NODETYPE_STMT etc 
  char *name;                       //stores the variable/function name in case of variable/function nodes
  union Constant value;             //stores the value of the constant if the node corresponds to a constant
  struct ASTNode *arglist;          //pointer to the expression list given as arguments to a function call
  struct ASTNode *ptr1,*ptr2,*ptr3; //Subtrees of the node. (Maximum Subtrees for IF THEN ELSE)
  struct Gsymbol *Gentry;           //pointer to GST entry for global variables and functions
  struct Lsymbol *Lentry;           //pointer to the function's LST for local variables and arguements
};


struct ASTNode* create_ast_node(int nodetype, char *name, union Constant value);

#endif