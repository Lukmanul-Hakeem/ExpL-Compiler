#ifndef CODEGENERATION_H
#define CODEGENERATION_H

#include<stdio.h>
#include<stdbool.h>
#include "./parseTree.h"

#define NUM_REGS 20
#define E_REG_FULL -1
#define SUCCESS 0

bool registers[NUM_REGS];
int getReg();
void freeReg();
void generateHeader(FILE* fptr);
void printContent(int data, FILE* fptr);
void addDataToStack(int data, FILE *fptr);
void exitProgram(FILE* fptr);
int code_Generation(t_node* root, FILE* fptr);

#endif
