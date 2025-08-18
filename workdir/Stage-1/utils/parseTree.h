#include <stdio.h>
#include <stdlib.h>
#ifndef PARSETREE_H
#define PARSETREE_H


struct t_node{
    int val;
    char* op;
    struct t_node* left;
    struct t_node* right;
};

typedef struct t_node t_node;

t_node* makeLeafNode(int val);
t_node* makeOperatorNode(char operator, t_node* left, t_node* right);
void printPrefix(t_node* root);
void printPostfix(t_node* root);

#endif