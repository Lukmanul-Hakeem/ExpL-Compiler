#include "./../utils/parseTree.h"      // full definition of tnode
#include "GlobalSymbolTable.h"
#include <stdlib.h>

void yyerror(const char *s);

Stnode* head = NULL;
Stnode* tail = NULL;
int bindAddr = 0;

Stnode *Lookup(char * name){
    Stnode* temp = head;
    while(temp){
        if(strcmp(temp->name, name) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

Stnode* create_symbol_table_node(char* name, int type, int size, int innerSize){
    
    Stnode* newNode = (Stnode*)malloc(sizeof(Stnode));
    newNode->name = strdup(name);
    newNode->type = type;
    newNode->size = size;
    newNode->innerSize = innerSize;
    int totalSize = size;
    if(innerSize > 0){
        totalSize = size * innerSize;
    }
    newNode->binding = 4096 + bindAddr;
    bindAddr += totalSize;
    newNode->next = NULL;   

    return newNode;
}

void print_symbol_table(){
    Stnode* temp = head;
    while(temp){
        printf("%s : %s : startAddress :- %d : outer:- %d : inner :- %d\n", temp->name, temp->type == 0 ? "INTEGER" : "STRING", temp->binding, temp->size, temp->innerSize);
        temp = temp->next;
    }
}

void Install(char *name, int type, int size, int innerSize){
   Stnode* temp = Lookup(name);
    if (temp) {
        fprintf(stderr, "Error: variable '%s' is already declared.\n", name);
        exit(1);   
    } 

    Stnode* newNode = create_symbol_table_node(name, type, size, innerSize);
    if(!head){
        head = tail = newNode;
    }else{
        tail->next = newNode;
        tail = tail->next;
    }
}

void create_symbol_table_entry(tnode* id, int Type, int size, int innerSize) {
    Stnode* temp = Lookup(id->varname);
    if(temp){
        yyerror("VARIABLE ALREADY EXISTS\n");
        exit(1);
    }
    Install(id->varname, Type, size, innerSize);
}