#include "./parseTree.h"

tnode *create_node(int val, char *sval, int type, int nodeType, char *c, Stnode *entry, tnode *left, struct tnode *right)
{

    tnode *newNode = (tnode *)malloc(sizeof(tnode));
    newNode->val = val;

    if (sval != NULL){
        newNode->sval = strdup(sval);
    }else{
        newNode->sval = NULL;
    }

    newNode->type = type;
    newNode->nodetype = nodeType;

    if (c != NULL)
        newNode->varname = strdup(c);
    else
        newNode->varname = NULL;

    newNode->entry = entry;
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
    else if (root->nodetype == NODE_TYPE_STRING)
    {
        printf("%s ", root->sval);
    }
    else
    {
        inorder(root->left);
        printf("%s ", getNodeSymbol(root->nodetype));
        inorder(root->right);
    }
}


// void inorder(tnode *root)
// {
//     if (root == NULL)
//         return;

//     switch (root->nodetype)
//     {
//         case NODE_TYPE_ID:
//             printf("%s", root->varname ? root->varname : "NULL");
//             break;

//         case NODE_TYPE_VALUE:
//             printf("%d", root->val);
//             break;

//         case NODE_TYPE_STRING:
//             printf("\"%s\"", root->sval);
//             break;

//         case NODE_TYPE_WRITE:
//             printf("write(");
//             inorder(root->left); // print what is being written
//             printf(");\n");
//             break;

//         case NODE_TYPE_READ:
//             printf("read(");
//             if(root->left && root->left->nodetype == NODE_TYPE_ID)
//                 printf("%s", root->left->varname);
//             printf(");\n");
//             break;

//         case NODE_TYPE_ASSIGN:
//             inorder(root->left);
//             printf(" = ");
//             inorder(root->right);
//             printf(";\n");
//             break;

//         case NODE_TYPE_CONNECTOR:
//             inorder(root->left);
//             inorder(root->right);
//             break;

//         case NODE_TYPE_IF:
//             printf("if(");
//             inorder(root->left);  // condition
//             printf(") {\n");
//             inorder(root->right); // then block
//             printf("}\n");
//             break;

//         case NODE_TYPE_IF_ELSE:
//             printf("if(");
//             inorder(root->left);  // condition
//             printf(") {\n");
//             if(root->right && root->right->left)
//                 inorder(root->right->left);  // then block
//             printf("} else {\n");
//             if(root->right && root->right->right)
//                 inorder(root->right->right); // else block
//             printf("}\n");
//             break;

//         case NODE_TYPE_WHILE:
//             printf("while(");
//             inorder(root->left);  // condition
//             printf(") {\n");
//             inorder(root->right); // body
//             printf("}\n");
//             break;

//         case NODE_TYPE_DO_WHILE:
//             printf("do {\n");
//             inorder(root->right); // body
//             printf("} while(");
//             inorder(root->left);  // condition
//             printf(");\n");
//             break;

//         case NODE_TYPE_REPEAT_UNTIL:
//             printf("repeat {\n");
//             inorder(root->right); // body
//             printf("} until(");
//             inorder(root->left);  // condition
//             printf(");\n");
//             break;

//         case NODE_TYPE_BREAK:
//             printf("break;\n");
//             break;

//         case NODE_TYPE_CONTINUE:
//             printf("continue;\n");
//             break;

//         // arithmetic and boolean operators
//         case NODE_TYPE_PLUS: case NODE_TYPE_MINUS: case NODE_TYPE_MULT:
//         case NODE_TYPE_DIV: case NODE_TYPE_LT: case NODE_TYPE_LE:
//         case NODE_TYPE_GT: case NODE_TYPE_GE: case NODE_TYPE_EQ:
//         case NODE_TYPE_NE:
//             printf("(");
//             inorder(root->left);
//             printf(" %s ", getNodeSymbol(root->nodetype));
//             inorder(root->right);
//             printf(")");
//             break;

//         default:
//             printf("UNKNOWN_NODE");
//             break;
//     }
// }