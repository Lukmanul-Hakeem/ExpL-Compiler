#include "./exprtree.h"
#include <stdio.h>
#include <stdlib.h>

tnode* makeLeafNode(int n) {
    tnode* temp = (tnode*)malloc(sizeof(tnode));
    temp->op = NULL;
    temp->val = n;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

tnode* makeOperatorNode(char ch, tnode* left, tnode* right) {
    tnode* temp = (tnode*)malloc(sizeof(tnode));
    temp->op = (char*)malloc(sizeof(char));
    *(temp->op) = ch;
    temp->left = left;
    temp->right = right;
    return temp;
}

int evaluate(tnode* root) {
    if (!root->op) return root->val;

    int left = evaluate(root->left);
    int right = evaluate(root->right);

    char ch = *(root->op);

    switch (ch) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
    }
    return 0;
}
