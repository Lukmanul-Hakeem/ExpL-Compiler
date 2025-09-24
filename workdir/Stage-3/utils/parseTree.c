#include "parseTree.h"

tnode *create_node(int val, int type, int nodeType, char *c, struct tnode *left, struct tnode *right)
{
    tnode *newNode = (tnode *)malloc(sizeof(tnode));

    if (!newNode)
    {
        fprintf(stderr, "Memory allocation failed in create_node\n");
        exit(1);
    }

    newNode->val = val;
    newNode->type = type;
    newNode->nodetype = nodeType;

    if (c != NULL)
    {
        newNode->varname = strdup(c);
    }
    else
    {
        newNode->varname = NULL;
    }

    newNode->left = left;
    newNode->right = right;

    return newNode;
}

const char *getNodeSymbol(int nodetype)
{
    switch (nodetype)
    {
    case NODE_TYPE_PLUS:
        return "+";
    case NODE_TYPE_MINUS:
        return "-";
    case NODE_TYPE_MULT:
        return "*";
    case NODE_TYPE_DIV:
        return "/";
    case NODE_TYPE_ASSIGN:
        return "=";
    case NODE_TYPE_READ:
        return "READ";
    case NODE_TYPE_WRITE:
        return "WRITE";
    case NODE_TYPE_CONNECTOR:
        return "CONNECTOR";
    case NODE_TYPE_IF:
        return "IF";
    case NODE_TYPE_IF_ELSE:
        return "IF_ELSE";
    case NODE_TYPE_LT:
        return "LT";
    case NODE_TYPE_LE:
        return "LE";
    case NODE_TYPE_GT:
        return "GT";
    case NODE_TYPE_GE:
        return "GE";
    case NODE_TYPE_EQ:
        return "EQ";
    case NODE_TYPE_NE:
        return "NE";
    case NODE_TYPE_WHILE:
        return "WHILE";
    case NODE_TYPE_DO_WHILE:
        return "DO_WHILE";
    case NODE_TYPE_REPEAT_UNTIL:
        return "REPEAT_UNTIL";
    default:
        return "?";
    }
}

void inorder(tnode *root)
{
    if (root == NULL)
        return;

    if (root->nodetype == NODE_TYPE_ID)
    {
        printf("%s ", root->varname ? root->varname : "NULL");
    }
    else if (root->nodetype == NODE_TYPE_VALUE)
    {
        printf("%d ", root->val);
    }
    else
    {
        inorder(root->left);
        printf("%s ", getNodeSymbol(root->nodetype));
        inorder(root->right);
    }
}

int evaluateArithmaticExpr(tnode *root)
{
    if (root == NULL)
        return 0;
    if (root->nodetype == NODE_TYPE_ID)
    {
        return var[*root->varname - 'a'];
    }
    else if (root->nodetype == NODE_TYPE_VALUE)
    {
        return root->val;
    }
    else
    {

        int left = evaluateArithmaticExpr(root->left);
        int right = evaluateArithmaticExpr(root->right);
        if (root->nodetype == NODE_TYPE_PLUS)
            return left + right;
        else if (root->nodetype == NODE_TYPE_MINUS)
            return left - right;
        else if (root->nodetype == NODE_TYPE_MULT)
            return left * right;
        else if (root->nodetype == NODE_TYPE_DIV)
            return left / right;

        return 0;
    }
}

int evaluateBooleanExpr(tnode *root)
{
    if (root == NULL)
        return 0;
    if (root->nodetype == NODE_TYPE_ID)
    {
        return var[*root->varname - 'a'];
    }
    else if (root->nodetype == NODE_TYPE_VALUE)
    {
        return root->val;
    }
    else
    {

        int left = evaluateBooleanExpr(root->left);
        int right = evaluateBooleanExpr(root->right);

        if (root->nodetype == NODE_TYPE_LT)
        {
            if (left < right)
                return 1;
            else
                return 0;
        }
        else if (root->nodetype == NODE_TYPE_LE)
        {
            if (left <= right)
                return 1;
            else
                return 0;
        }
        else if (root->nodetype == NODE_TYPE_GT)
        {
            if (left > right)
                return 1;
            else
                return 0;
        }
        else if (root->nodetype == NODE_TYPE_GE)
        {
            if (left >= right)
                return 1;
            else
                return 0;
        }
        else if (root->nodetype == NODE_TYPE_EQ)
        {
            if (left == right)
                return 1;
            else
                return 0;
        }
        else if (root->nodetype == NODE_TYPE_NE)
        {
            if (left != right)
                return 1;
            else
                return 0;
        }
        else
        {
            return 0;
        }
    }
}

void evaluate(tnode *root)
{

    if (root == NULL)
        return;

    if (root->nodetype == NODE_TYPE_READ)
    {

        scanf("%d", &var[*(root->left->varname) - 'a']);
    }
    else if (root->nodetype == NODE_TYPE_WRITE)
    {

        printf("%d\n", var[*root->left->varname - 'a']);
    }
    else if (root->nodetype == NODE_TYPE_ASSIGN)
    {

        var[*root->left->varname - 'a'] = evaluateArithmaticExpr(root->right);
    }
    else if (root->nodetype == NODE_TYPE_IF_ELSE)
    {

        int condition = evaluateBooleanExpr(root->left);
        if (condition)
        {
            evaluate(root->right->left);
            return;
        }
        else
        {
            evaluate(root->right->right);
            return;
        }
    }
    else if (root->nodetype == NODE_TYPE_IF)
    {

        int condition = evaluateBooleanExpr(root->left);
        if (condition)
        {
            evaluate(root->right);
            return;
        }
        else
            return;
    }
    else if (root->nodetype == NODE_TYPE_WHILE)
    {
        int condition = evaluateBooleanExpr(root->left);
        while (condition)
        {
            evaluate(root->right);
            condition = evaluateBooleanExpr(root->left);
        }
    }
    else if (root->nodetype == NODE_TYPE_DO_WHILE)
    {

        int condition = 0;
        do
        {
            evaluate(root->right);
            condition = evaluateBooleanExpr(root->left);

        } while (condition);
    }
    else if (root->nodetype == NODE_TYPE_REPEAT_UNTIL)
    {
        int condition = 0;
        do
        {
            evaluate(root->right);
            condition = evaluateBooleanExpr(root->left);

        } while (!condition);
    }
    else
    {
        evaluate(root->left);
        evaluate(root->right);
    }
}

void freeTree(tnode *root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    if (root->varname != NULL)
    {
        free(root->varname);
    }
    free(root);
}