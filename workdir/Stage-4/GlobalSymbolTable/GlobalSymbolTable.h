#ifndef GLOBALSYMBOLTABLE_H
#define GLOBALSYMBOLTABLE_H

#include <string.h>
#include<stdio.h>

typedef struct Gsymbol {
    char* name;
    int type;
    int size;
    int binding;
    struct Gsymbol *next;
}Stnode;

Stnode* create_symbol_table_node(char* name, int type, int size);
struct Gsymbol *Lookup(char * name);
void Install(char *name, int type, int size);
void print_symbol_table();

#endif