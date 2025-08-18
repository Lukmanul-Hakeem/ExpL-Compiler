#include "./parseTree.h"

typedef struct t_node t_node;

t_node *makeLeafNode(int val)
{

    t_node *temp = (t_node *)malloc(sizeof(t_node));
    temp->val = val;
    temp->op = NULL;
    temp->left = temp->right = NULL;

    return temp;
}

t_node *makeOperatorNode(char operator, t_node *left, t_node *right)
{
    t_node *temp = (t_node *)malloc(sizeof(t_node));

    temp->op = (char *)malloc(sizeof(char));
    *(temp->op) = operator;

    temp->left = left;
    temp->right = right;

    return temp;
}

void printPostfix(t_node *root)
{
    if (!root->op)
    {
        printf("%d ", root->val);
        return;
    }
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%c ", *(root->op));
}

void printPrefix(t_node *root)
{
    if (!root->op)
    {
        printf("%d ", root->val);
        return;
    }
    printf("%c ", *(root->op));
    printPrefix(root->left);
    printPrefix(root->right);
}