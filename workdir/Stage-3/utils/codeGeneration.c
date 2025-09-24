#include "codeGeneration.h"

int label = 0;

int getReg()
{
    for (int i = 0; i < NUM_REGS; i++)
    {
        if (!registers[i])
        {
            registers[i] = true;
            return i;
        }
    }

    return E_REG_FULL;
}

void freeReg(int regIndex)
{
    registers[regIndex] = false;
}

void generateHeader(FILE *fptr)
{
    fprintf(fptr, "0\n2056\n0\n0\n0\n0\n0\n0\n");
    fprintf(fptr, "MOV SP, 4122\n");
}

int getAddress(char var)
{

    int staticAddr = 4096 + var - 'a';
    return staticAddr;
}

void generate_Code_ReadSys(int addrReg, FILE *fptr)
{

    int reg = getReg();
    fprintf(fptr, "MOV R%d, 7\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, -1\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, %d\n", reg, addrReg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "INT 6\n");

    int returnReg = getReg();
    fprintf(fptr, "POP R%d\n", returnReg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);

    freeReg(reg);
    freeReg(returnReg);
}

void readSystemCall(tnode *node, FILE *fptr)
{
    int addrReg = getAddress(node->left->varname[0]);
    generate_Code_ReadSys(addrReg, fptr);
}

void printContent(int dataReg, FILE *fptr)
{

    int reg = getReg();
    fprintf(fptr, "MOV R%d, 5\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, -2\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", dataReg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "INT 7\n");

    int returnReg = getReg();
    fprintf(fptr, "POP R%d\n", returnReg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);

    freeReg(reg);
    freeReg(returnReg);
}

void writeSystemCall(tnode *node, FILE *fptr)
{
    int dataReg = generate_arithmetic_code(node->left, fptr);
    printContent(dataReg, fptr);
    freeReg(dataReg);
}

int generate_arithmetic_code(tnode *root, FILE *fptr)
{

    if (root->nodetype == NODE_TYPE_VALUE)
    {
        int reg = getReg();
        fprintf(fptr, "MOV R%d, %d\n", reg, root->val);
        return reg;
    }

    if (root->nodetype == NODE_TYPE_ID)
    {
        int addr = getAddress(root->varname[0]);
        int reg = getReg();
        fprintf(fptr, "MOV R%d, [%d]\n", reg, addr);
        return reg;
    }

    int leftReg = generate_arithmetic_code(root->left, fptr);
    int rightReg = generate_arithmetic_code(root->right, fptr);

    switch (root->nodetype)
    {
    case NODE_TYPE_PLUS:
        fprintf(fptr, "ADD R%d, R%d\n", leftReg, rightReg);
        break;
    case NODE_TYPE_MINUS:
        fprintf(fptr, "SUB R%d, R%d\n", leftReg, rightReg);
        break;
    case NODE_TYPE_MULT:
        fprintf(fptr, "MUL R%d, R%d\n", leftReg, rightReg);
        break;
    case NODE_TYPE_DIV:
        fprintf(fptr, "DIV R%d, R%d\n", leftReg, rightReg);
        break;
    default:
        printf("unknown Operator.\n");
        exit(1);
    }

    freeReg(rightReg);

    return leftReg;
}

void generate_assignment_code(tnode *node, FILE *fptr)
{

    int rightReg = generate_arithmetic_code(node->right, fptr);
    int addr = getAddress(node->left->varname[0]);
    fprintf(fptr, "MOV [%d], R%d\n", addr, rightReg);
    freeReg(rightReg);

}

void exitProgram(FILE *fptr)
{
    int reg = getReg();
    fprintf(fptr, "MOV R%d, 10\n", reg); 
    fprintf(fptr, "PUSH R%d\n", reg);        
    fprintf(fptr, "PUSH R%d\n", reg);        
    fprintf(fptr, "PUSH R%d\n", reg);        
    fprintf(fptr, "PUSH R%d\n", reg);        
    fprintf(fptr, "PUSH R%d\n", reg);       
    fprintf(fptr, "INT 10\n");            

    int returnReg = getReg();
    fprintf(fptr, "POP R%d\n", returnReg);
    fprintf(fptr, "POP R%d\n", reg);       
    fprintf(fptr, "POP R%d\n", reg);       
    fprintf(fptr, "POP R%d\n", reg);       
    fprintf(fptr, "POP R%d\n", reg);     

    freeReg(reg);
    freeReg(returnReg);
}

int generate_boolean_code(tnode* root, FILE* fptr){

    if(root->nodetype == NODE_TYPE_ID){
        int reg = getReg();
        int addr = getAddress(root->varname[0]);
        fprintf(fptr, "MOV R%d, [%d]\n", reg, addr);
        return reg;
    }else if(root->nodetype == NODE_TYPE_VALUE){
        int reg = getReg();
        fprintf(fptr, "MOV R%d, %d\n", reg, root->val);
        return reg;
    }else{
        int left = generate_boolean_code(root->left, fptr);
        int right = generate_boolean_code(root->right, fptr);

        if(root->nodetype == NODE_TYPE_LT){
            fprintf(fptr, "LT R%d, R%d\n", left, right);
        }else if(root->nodetype == NODE_TYPE_LE){
            fprintf(fptr, "LTE R%d, R%d\n", left, right);
        }else if(root->nodetype == NODE_TYPE_GT){
            fprintf(fptr, "GT R%d, R%d\n", left, right);
        }else if(root->nodetype == NODE_TYPE_GE){
            fprintf(fptr, "GTE R%d, R%d\n", left, right);
        }else if(root->nodetype == NODE_TYPE_EQ){
            fprintf(fptr, "EQ R%d, R%d\n", left, right);
        }else if(root->nodetype == NODE_TYPE_NE){
            fprintf(fptr, "NE R%d, R%d\n", left, right);
        }

        freeReg(right);

        return left;
    }
}

void generate_if_else_code(tnode* root, FILE* fptr){

    int reg = generate_boolean_code(root->left, fptr);
    int temp = label++;

    fprintf(fptr, "JZ R%d, CONDITION_FALSE_%d\n", reg, temp);

    code_Generation(root->right->left, fptr);

    fprintf(fptr, "JMP END_IF_ELSE%d\n", temp);

    fprintf(fptr, "CONDITION_FALSE_%d:\n", temp);

    code_Generation(root->right->right, fptr);

    fprintf(fptr, "END_IF_ELSE%d:\n", temp);
    

    freeReg(reg);

}

void generate_if_code(tnode* root, FILE* fptr){

    int reg = generate_boolean_code(root->left, fptr);
    int temp = label++;

    fprintf(fptr, "JZ R%d, CONDITION_FALSE_%d\n", reg, temp);

    code_Generation(root->right, fptr);

    fprintf(fptr, "JMP END_IF%d\n", temp);

    fprintf(fptr, "CONDITION_FALSE_%d:\n", temp);

    fprintf(fptr, "END_IF%d:\n", temp);


    freeReg(reg);
}

void generate_while_code(tnode* root, FILE* fptr){

    int temp = label++;
    fprintf(fptr, "LOOP%d:\n", temp);
    int reg = generate_boolean_code(root->left, fptr);
    fprintf(fptr, "JZ R%d, END_LOOP%d\n", reg, temp);
    code_Generation(root->right,fptr);
    fprintf(fptr, "JMP LOOP%d\n", temp);
    fprintf(fptr, "END_LOOP%d:\n", temp);

    freeReg(reg);
}

void generate_do_while_code(tnode* root, FILE* fptr){

    int temp = label++;

    fprintf(fptr, "DOWHILE%d:\n", temp);
    code_Generation(root->right, fptr);
    int reg = generate_boolean_code(root->left, fptr);
    fprintf(fptr, "JZ R%d, END_DOWHILE%d\n", reg, temp);
    fprintf(fptr, "JMP DOWHILE%d\n", temp);
    fprintf(fptr, "END_DOWHILE%d:\n", temp);

    freeReg(reg);

}

void generate_repeat_until_code(tnode* root, FILE* fptr){

    int temp = label++;

    fprintf(fptr, "REPEAT_UNTIL%d:\n", temp);
    code_Generation(root->right, fptr);
    int reg = generate_boolean_code(root->left, fptr);
    fprintf(fptr, "JNZ R%d, END_REPEAT_UNTIL%d\n", reg, temp);
    fprintf(fptr, "JMP REPEAT_UNTIL%d\n", temp);
    fprintf(fptr, "END_REPEAT_UNTIL%d:\n", temp);

    freeReg(reg);
}

void code_Generation(tnode* root, FILE* fptr){
    if(root == NULL)return;
    // printf("%d ", root->nodetype);

    if(root->nodetype == NODE_TYPE_CONNECTOR){
        code_Generation(root->left, fptr);
        code_Generation(root->right, fptr);
    }else if(root->nodetype == NODE_TYPE_READ){
        readSystemCall(root, fptr);
    }else if(root->nodetype == NODE_TYPE_WRITE){
        writeSystemCall(root, fptr);
    }else if(root->nodetype == NODE_TYPE_ASSIGN){
        generate_assignment_code(root, fptr);
    }else if(root->nodetype == NODE_TYPE_IF_ELSE){
        generate_if_else_code(root, fptr);
    }else if(root->nodetype == NODE_TYPE_IF){
        generate_if_code(root, fptr);
    }else if(root->nodetype == NODE_TYPE_WHILE){
        generate_while_code(root, fptr);
    }else if(root->nodetype == NODE_TYPE_DO_WHILE){
        generate_do_while_code(root, fptr);
    }else if(root->nodetype == NODE_TYPE_REPEAT_UNTIL){
        generate_repeat_until_code(root, fptr);
    }

    return ;
}