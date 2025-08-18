#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include <stdbool.h>
#include "./parseTree.h"

#define NUM_REGS     20
#define E_REG_FULL   -1
#define SUCCESS      0


bool registers[NUM_REGS];
int  getReg(void);

void freeReg(int regIndex);


void generateHeader(FILE *fptr);
void exitProgram(FILE *fptr);


int  getAddress(char var);


void generate_Code_ReadSys(int addrReg, FILE *fptr);
void readSystemCall(tnode *node, FILE *fptr);
void printContent(int dataReg, FILE *fptr);
void writeSystemCall(tnode *node, FILE *fptr);


int  generate_arithmetic_code(tnode *root, FILE *fptr);
void generate_assignment_code(tnode *node, FILE *fptr);
void code_Generation(tnode* root, FILE* fptr);


#endif 