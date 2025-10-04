#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "parseTree.h"

// Register management
#define NUM_REGS     20
#define E_REG_FULL   -1
#define SUCCESS      0

bool registers[NUM_REGS];
int  getReg(void);
void freeReg(int regIndex);

// Program structure
void generateHeader(FILE *fptr);
void exitProgram(FILE *fptr);

// Address calculations
int  getAddress(Stnode* entry);
int  getArrayLastAddress(Stnode *entry);

// I/O operations
void generate_Code_ReadSys(int addrReg, FILE *fptr);
void readSystemCall(tnode *node, FILE *fptr);

void printContent(int dataReg, FILE *fptr);
void writeSystemCall(tnode *node, FILE *fptr);

// Code generation for expressions/statements
int  generate_string_code(tnode* node, FILE* fptr);
int  generate_arithmetic_code(tnode *root, FILE *fptr);
void generate_assignment_code(tnode *node, FILE *fptr);
int  generate_boolean_code(tnode* root, FILE* fptr);

void code_Generation(tnode* root, FILE* fptr, int temp);

// Conditionals
void generate_if_code(tnode* root, FILE* fptr, int loopLabel);
void generate_if_else_code(tnode* root, FILE* fptr, int loopLabel);

// Arrays
void check_array_bound(int indexReg, tnode *root, FILE *fptr);
int  generate_code_array_index(tnode *root, FILE *fptr);
void generate_code_array_assign(tnode *root, FILE *fptr);
void generate_code_array_read(tnode *root, FILE *fptr);
void generate_code_2d_array_assign(tnode *root, FILE *fptr);
int  generate_code_2d_array_index(tnode *root, FILE *fptr);
void generate_code_2d_array_read(tnode *root, FILE *fptr);

void generate_address_assign(tnode* root, FILE* fptr);
void generate_deref_assign(tnode* root, FILE* fptr);

#endif