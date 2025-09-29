#include "GlobalSymbolTable.h"
#include <stdlib.h>

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

Stnode* create_symbol_table_node(char* name, int type, int size){
    
    Stnode* newNode = (Stnode*)malloc(sizeof(Stnode));
    newNode->name = strdup(name);
    newNode->type = type;
    newNode->size = size;
    newNode->binding = 4096 + bindAddr;
    bindAddr += size;
    newNode->next = NULL;

    return newNode;
}

void print_symbol_table(){
    Stnode* temp = head;
    while(temp){
        printf("%s : %s : %d\n", temp->name, temp->type == 0 ? "INTEGER" : "STRING", temp->binding);
        temp = temp->next;
    }
}

void Install(char *name, int type, int size){
   Stnode* temp = Lookup(name);
    if (temp) {
        fprintf(stderr, "Error: variable '%s' is already declared.\n", name);
        exit(1);   
    } 

    Stnode* newNode = create_symbol_table_node(name, type, size);
    if(!head){
        head = tail = newNode;
    }else{
        tail->next = newNode;
        tail = tail->next;
    }
}