#ifndef GLOBALSYMBOLTABLE_H
#define GLOBALSYMBOLTABLE_H

#include <string.h>
#include <stdio.h>

typedef struct tnode tnode; 

typedef struct Stnode {
    char* name;
    int type;
    int size;
    int innerSize;
    int binding;
    struct Stnode *next;
} Stnode;

void create_symbol_table_entry(tnode* id, int Type, int size, int innerSize);
Stnode* create_symbol_table_node(char* name, int type, int size, int innerSize);
Stnode* Lookup(char *name);
void Install(char *name, int type, int size, int innerSize);
void print_symbol_table();

#endif