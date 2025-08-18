#include "./codeGeneration.h"

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
}

void printContent(int data, FILE *fptr)
{

    int reg = getReg();
    fprintf(fptr, "MOV R%d, 5\n", reg); // SET FREE REG WITH SYSTEM_CALL_CODE
    fprintf(fptr, "PUSH R%d\n", reg);       // PUSH SYSTEM_CALL_CODE
    fprintf(fptr, "MOV R%d, -2\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);  // PUSH ARG1 = -2
    fprintf(fptr, "PUSH R%d\n", data); // PUSH ARG2 = DATA
    fprintf(fptr, "PUSH R%d\n", reg);  // PUSH ARG3
    fprintf(fptr, "PUSH R%d\n", reg);  // PUSH SPACE TO STORE RETURN VALUE
    fprintf(fptr, "INT 7\n");       // MAKE INTERRUPT TO SHIFT FROM USER MODE TO KERNAL MODE.

    int returnReg = getReg();
    fprintf(fptr, "POP R%d\n", returnReg); // RETURN VALUE OF THE INTERRUPT WILL BE STORE IN THIS "returnReg".
    fprintf(fptr, "POP R%d\n", reg);       // POP ARG3
    fprintf(fptr, "POP R%d\n", reg);       // POP ARG2
    fprintf(fptr, "POP R%d\n", reg);       // POP ARG1
    fprintf(fptr, "POP R%d\n", reg);     // POP SYSTEM_CALL_CODE

    freeReg(reg);
}

void addDataToStack(int data, FILE *fptr)
{
    fprintf(fptr, "PUSH R%d\n", data);
}

void exitProgram(FILE *fptr)
{
    int reg = getReg();
    fprintf(fptr, "MOV R%d, 10\n", reg); // SET FREE REG WITH SYSTEM_CALL_CODE
    fprintf(fptr, "PUSH R%d\n", reg);        // PUSH SYSTEM_CALL_CODE
    fprintf(fptr, "PUSH R%d\n", reg);        // PUSH ARG1
    fprintf(fptr, "PUSH R%d\n", reg);        // PUSH ARG2
    fprintf(fptr, "PUSH R%d\n", reg);        // PUSH ARG3
    fprintf(fptr, "PUSH R%d\n", reg);        // PUSH SPACE TO STORE RETURN VALUE
    fprintf(fptr, "INT 10\n");            // MAKE INTERRUPT TO SHIFT FROM USER MODE TO KERNAL MODE.

    int returnReg = getReg();
    fprintf(fptr, "POP R%d\n", returnReg); // RETURN VALUE OF THE INTERRUPT WILL BE STORE IN THIS "returnReg".
    fprintf(fptr, "POP R%d\n", reg);       // POP ARG3
    fprintf(fptr, "POP R%d\n", reg);       // POP ARG2
    fprintf(fptr, "POP R%d\n", reg);       // POP ARG1
    fprintf(fptr, "POP R%d\n", reg);     // POP SYSTEM_CALL_CODE

    freeReg(reg);
}

int code_Generation(t_node *root, FILE *fptr)
{
    
    if (!root->op)
    {

        int reg = getReg();
        fprintf(fptr, "MOV R%d, %d\n", reg, root->val);
        return reg;
    }

    int leftReg = code_Generation(root->left, fptr);
    int rightReg = code_Generation(root->right, fptr);

    char operator = *(root->op);

    switch (operator)
    {
    case '+':
        fprintf(fptr, "ADD R%d, R%d\n", leftReg, rightReg);
        break;
    case '-':
        fprintf(fptr, "SUB R%d, R%d\n", leftReg, rightReg);
        break;
    case '*':
        fprintf(fptr, "MUL R%d, R%d\n", leftReg, rightReg);
        break;
    case '/':
        fprintf(fptr, "DIV R%d, R%d\n", leftReg, rightReg);
        break;
    default:
        printf("unknown Operator.\n");
        exit(1);
    }

    freeReg(rightReg);
    return leftReg;
}
