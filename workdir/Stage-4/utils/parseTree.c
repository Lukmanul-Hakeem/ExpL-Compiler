#include "parseTree.h"
#include "./../GlobalSymbolTable/GlobalSymbolTable.h"

void yyerror(const char *s);

tnode *create_node(int val, char *sval, int type, int nodeType, char *c, Stnode *entry, tnode *left, tnode *right)
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
    case NODE_TYPE_BREAK:
        return "BREAK";
    case NODE_TYPE_CONTINUE:
        return "CONTINUE";
    case NODE_TYPE_VALUE:
        return "VALUE";
    case NODE_TYPE_ID:
        return "ID";
    case NODE_TYPE_STRING:
        return "STRING";
    case NODE_TYPE_ARR_ASSIGN:
        return "ARRAY_ASSIGN";
    case NODE_TYPE_ARR_READ:
        return "ARRAY_READ";
    case NODE_TYPE_ARRAY:
        return "ARRAY";
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

tnode* create_array_node(tnode* id, tnode* index) {

    Stnode* temp = Lookup(id->varname);
    if(temp == NULL){
        yyerror("VARIABLE IS NOT DECLARED\n");
    }

    if(temp->innerSize == 0){
        yyerror("NOT AN ARRAY\n");
    }

    id->entry = temp;

    if(index->type != DATA_TYPE_INTEGER){
        yyerror("Array Index must be Integer\n");
    }
    
    id->type = temp->type;

    return create_node(-1, NULL, temp->type, NODE_TYPE_ARRAY, NULL, NULL, id, index);
}

tnode* create_2D_array_node(tnode* id, tnode* index1, tnode* index2) {

    Stnode* temp = Lookup(id->varname);
    if(temp == NULL){
        yyerror("VARIABLE IS NOT DECLARED\n");
    }

    if(temp->size == 1 || temp->innerSize == 0){
        yyerror("NOT A 2D ARRAY\n");
    }

    id->entry = temp;

    if(index1->type != DATA_TYPE_INTEGER || index2->type != DATA_TYPE_INTEGER){
        yyerror("Array Indices must be Integer\n");
    }
    
    id->type = temp->type;

    tnode* connectorNode = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_CONNECTOR, NULL, NULL, index1, index2);
    return create_node(-1, NULL, temp->type, NODE_TYPE_2D_ARRAY, NULL, NULL, id, connectorNode);
}

tnode* create_id_node(tnode* id) {

    Stnode* temp = Lookup(id->varname);
    if(temp == NULL){
        yyerror("VARIABLE IS NOT DECLARED\n");
    }

    id->entry = temp;
    id->type = temp->type; 

    return id;
}

tnode* create_write_node(tnode* expr) {

    if(expr->type != DATA_TYPE_INTEGER && expr->type != DATA_TYPE_STRING){
        yyerror("WRITE can only be done on Integer or String\n");
    }

    return create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_WRITE, NULL, NULL, expr, NULL);
}

tnode* create_read_node(tnode* id) {

    if(id->type != DATA_TYPE_INTEGER && id->type != DATA_TYPE_STRING){
        yyerror("READ can only be done on Integer or String\n");
    }

    return create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_READ, NULL, NULL, id, NULL);
}

tnode* create_assign_node(tnode* left, tnode* right) {

    if(left->type != right->type){
        yyerror("Type Mismatch in Assignment\n");
    }

    return create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_ASSIGN, NULL, NULL, left, right);
}

tnode* create_if_node(tnode* condition, tnode* thenBranch) {

    if(condition->type != DATA_TYPE_BOOLEAN){
        yyerror("Condition in IF should be Boolean\n");
    }

    return create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_IF, NULL, NULL, condition, thenBranch);
}

tnode* create_if_else_node(tnode* condition, tnode* thenBranch, tnode* elseBranch) {

    if(condition->type != DATA_TYPE_BOOLEAN){
        yyerror("Condition in IF-ELSE should be Boolean\n");
    }

    tnode* connectorNode = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_CONNECTOR, NULL, NULL, thenBranch, elseBranch);
    tnode* ifElseNode = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_IF_ELSE, NULL, NULL, condition, connectorNode);

    return ifElseNode;
}

tnode* create_while_node(tnode* condition, tnode* body) {

    if(condition->type != DATA_TYPE_BOOLEAN){
        yyerror("Condition in WHILE should be Boolean\n");
    }

    return create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_WHILE, NULL, NULL, condition, body);
}

tnode* create_do_while_node(tnode* body, tnode* condition) {

    if(condition->type != DATA_TYPE_BOOLEAN){
        yyerror("Condition in DO-WHILE should be Boolean\n");
    }

    return create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_DO_WHILE, NULL, NULL, body, condition);
}

tnode* create_repeat_until_node(tnode* body, tnode* condition) {

    if(condition->type != DATA_TYPE_BOOLEAN){
        yyerror("Condition in REPEAT-UNTIL should be Boolean\n");
    }

    return create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_REPEAT_UNTIL, NULL, NULL, body, condition);
}

tnode* create_arithmetic_node(tnode* left, tnode* right, int operator) {

    if(left->type != DATA_TYPE_INTEGER || right->type != DATA_TYPE_INTEGER){
        yyerror("Arithmetic operations can only be done on Integers\n");
    }

    return create_node(-1, NULL, DATA_TYPE_INTEGER, operator, NULL, NULL, left, right);
}

tnode* create_boolean_node(tnode* left, tnode* right, int operator) {


    if(left->type != DATA_TYPE_INTEGER || right->type != DATA_TYPE_INTEGER){
        yyerror("Relational operations can only be done on Integers\n");
    }

    return create_node(-1, NULL, DATA_TYPE_BOOLEAN, operator, NULL, NULL, left, right);
}

tnode* create_deref_node(tnode* id){

    Stnode* temp = Lookup(id->varname);

    if(temp == NULL){
        yyerror("VARIABLE IS NOT DECLARED\n");
    }

    id->type = temp->type;
    id->entry = temp;

    if(id->type == DATA_TYPE_INTEGER_PTR) 
        return create_node(-1, NULL, DATA_TYPE_INTEGER, NODE_TYPE_DEREF, NULL, NULL, id, NULL);
    else 
        return create_node(-1, NULL, DATA_TYPE_STRING, NODE_TYPE_DEREF, NULL, NULL, id, NULL);

}

tnode* create_addr_node(tnode* id){
    Stnode* temp = Lookup(id->varname);

    if(temp == NULL){
       yyerror("VARIABLE IS NOT DECLARED\n");
    }

    id->type = temp->type;
    id->entry = temp;

    if(id->type == DATA_TYPE_INTEGER) 
        return create_node(-1, NULL, DATA_TYPE_INTEGER_PTR, NODE_TYPE_REF, NULL, NULL, id, NULL);
    else 
        return create_node(-1, NULL, DATA_TYPE_STRING_PTR, NODE_TYPE_REF, NULL, NULL, id, NULL);

}


