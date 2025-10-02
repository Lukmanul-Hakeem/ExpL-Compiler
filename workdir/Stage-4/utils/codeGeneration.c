#include "codeGeneration.h"
#include "parseTree.h"
#include "./../GlobalSymbolTable/GlobalSymbolTable.h"

int label = 0;
int conditionLabel = 0;

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
    fprintf(fptr, "MOV SP, 4222\n");
}

int getAddress(Stnode *entry)
{
    return entry->binding;
}

void generate_Code_ReadSys(int addrReg, FILE *fptr)
{

    int reg = getReg();
    fprintf(fptr, "MOV R%d, 7\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, -1\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, R%d\n", reg, addrReg);
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
    if (node->left->nodetype == NODE_TYPE_ARRAY)
    {
        generate_code_array_read(node->left, fptr);
    }else if(node->left->nodetype == NODE_TYPE_2D_ARRAY) {
        generate_code_2d_array_read(node->left, fptr);
    }
    else
    {

        int addr = getAddress(node->left->entry);
        int addrReg = getReg();
        fprintf(fptr, "MOV R%d, %d\n", addrReg, addr);
        generate_Code_ReadSys(addrReg, fptr);
        freeReg(addrReg);
    }
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
    int dataReg = -1;

    if (node->left->type == DATA_TYPE_INTEGER)
        dataReg = generate_arithmetic_code(node->left, fptr);
    else
        dataReg = generate_string_code(node->left, fptr);

    printContent(dataReg, fptr);
    freeReg(dataReg);
}

int generate_string_code(tnode *node, FILE *fptr)
{
    int reg = getReg();
    if (node->nodetype == NODE_TYPE_ID)
    {
        int addr = getAddress(node->entry);
        fprintf(fptr, "MOV R%d, [%d]\n", reg, addr);
    }
    else
    {
        fprintf(fptr, "MOV R%d, \"%s\"\n", reg, node->sval);
    }
    return reg;
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
        int addr = getAddress(root->entry);
        int reg = getReg();
        fprintf(fptr, "MOV R%d, [%d]\n", reg, addr);
        return reg;
    }

    if (root->nodetype == NODE_TYPE_ARRAY)
    {

        int indexReg = generate_code_array_index(root, fptr);

        int reg = getReg();
        fprintf(fptr, "MOV R%d, [R%d]\n", reg, indexReg);

        freeReg(indexReg);
        return reg;
    }

    if(root->nodetype == NODE_TYPE_2D_ARRAY) {
        int indexReg = generate_code_2d_array_index(root, fptr);
        int reg = getReg();
        fprintf(fptr, "MOV R%d, [R%d]\n", reg, indexReg);
        freeReg(indexReg);
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
    case NODE_TYPE_MOD:
        fprintf(fptr, "MOD R%d, R%d\n", leftReg, rightReg);
        break;
    default:
        printf("unknown Operator.\n");
        exit(1);
    }

    freeReg(rightReg);

    return leftReg;
}

void generate_code_array_assign(tnode *root, FILE *fptr)
{
    int regIndex = generate_code_array_index(root->left, fptr);

    int regVal = generate_arithmetic_code(root->right, fptr);
    fprintf(fptr, "MOV [R%d], R%d\n", regIndex, regVal);

    freeReg(regIndex);
    freeReg(regVal);
}

int generate_code_2d_array_index(tnode *root, FILE *fptr)
{
    int rowIndexReg = generate_arithmetic_code(root->right->left, fptr);
    int colIndexReg = generate_arithmetic_code(root->right->right, fptr);

    Stnode* arrayNode = root->left->entry;

    int innerSize = arrayNode->innerSize;

    int innerSizeReg = getReg();

    fprintf(fptr, "MOV R%d, %d\n", innerSizeReg, innerSize);
    fprintf(fptr, "MUL R%d, R%d\n", rowIndexReg, innerSizeReg);
    fprintf(fptr, "ADD R%d, R%d\n", rowIndexReg, colIndexReg);

    check_array_bound(rowIndexReg, root->left, fptr);

    freeReg(colIndexReg);
    freeReg(innerSizeReg);

    return rowIndexReg;
}

void generate_code_2d_array_assign(tnode *root, FILE *fptr)
{
    int indexReg = generate_code_2d_array_index(root->left, fptr);

    int regVal = generate_arithmetic_code(root->right, fptr);
    fprintf(fptr, "MOV [R%d], R%d\n", indexReg, regVal);

    freeReg(indexReg);
    freeReg(regVal);
}

void generate_code_2d_array_read(tnode *root, FILE *fptr)
{
    int indexReg = generate_code_2d_array_index(root, fptr);
    generate_Code_ReadSys(indexReg, fptr);
    freeReg(indexReg);
}

void generate_assignment_code(tnode *node, FILE *fptr)
{

    int rightReg = -1;

    if (node->left->nodetype == NODE_TYPE_ARRAY)
    {
        generate_code_array_assign(node, fptr);
        return;
    }
    else if(node->left->nodetype == NODE_TYPE_2D_ARRAY) {
        generate_code_2d_array_assign(node, fptr);
        return;
    }
    else if (node->right->type == DATA_TYPE_INTEGER)
        rightReg = generate_arithmetic_code(node->right, fptr);
    else if (node->right->type == DATA_TYPE_STRING)
        rightReg = generate_string_code(node->right, fptr);

    int addr = getAddress(node->left->entry);
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

int generate_boolean_code(tnode *root, FILE *fptr)
{
    int left = generate_arithmetic_code(root->left, fptr);
    int right = generate_arithmetic_code(root->right, fptr);

    switch (root->nodetype)
    {
    case NODE_TYPE_LT:
        fprintf(fptr, "LT R%d, R%d\n", left, right);
        break;
    case NODE_TYPE_LE:          
        fprintf(fptr, "LE R%d, R%d\n", left, right);
        break;      
    case NODE_TYPE_GT:          
        fprintf(fptr, "GT R%d, R%d\n", left, right);
        break;
    case NODE_TYPE_GE:          
        fprintf(fptr, "GE R%d, R%d\n", left, right);
        break;
    case NODE_TYPE_EQ:        
        fprintf(fptr, "EQ R%d, R%d\n", left, right);
        break;          
    case NODE_TYPE_NE:          
        fprintf(fptr, "NE R%d, R%d\n", left, right);
        break;  
    default:
        printf("unknown Operator.\n");
        exit(1);
    }

    freeReg(right);
    return left;
}

void generate_if_else_code(tnode *root, FILE *fptr, int loopLabel)
{

    int reg = generate_boolean_code(root->left, fptr);
    int temp = conditionLabel++;

    fprintf(fptr, "JZ R%d, CONDITION_FALSE_%d\n", reg, temp);

    code_Generation(root->right->left, fptr, loopLabel);

    fprintf(fptr, "JMP END_IF_ELSE%d\n", temp);

    fprintf(fptr, "CONDITION_FALSE_%d:\n", temp);

    code_Generation(root->right->right, fptr, loopLabel);

    fprintf(fptr, "END_IF_ELSE%d:\n", temp);

    freeReg(reg);
}

void generate_if_code(tnode *root, FILE *fptr, int loopLabel)
{

    int reg = generate_boolean_code(root->left, fptr);
    int temp = conditionLabel++;

    fprintf(fptr, "JZ R%d, CONDITION_FALSE_%d\n", reg, temp);

    code_Generation(root->right, fptr, loopLabel);

    fprintf(fptr, "JMP END_IF%d\n", temp);

    fprintf(fptr, "CONDITION_FALSE_%d:\n", temp);

    fprintf(fptr, "END_IF%d:\n", temp);

    freeReg(reg);
}

void generate_while_code(tnode *root, FILE *fptr)
{

    int temp = label++;
    fprintf(fptr, "LOOP%d:\n", temp);
    int reg = generate_boolean_code(root->left, fptr);
    fprintf(fptr, "JZ R%d, END%d\n", reg, temp);
    code_Generation(root->right, fptr, temp);
    fprintf(fptr, "JMP LOOP%d\n", temp);
    fprintf(fptr, "END%d:\n", temp);

    freeReg(reg);
}

void generate_do_while_code(tnode *root, FILE *fptr)
{

    int temp = label++;

    fprintf(fptr, "LOOP%d:\n", temp);
    code_Generation(root->right, fptr, temp);
    int reg = generate_boolean_code(root->left, fptr);
    fprintf(fptr, "JZ R%d, END%d\n", reg, temp);
    fprintf(fptr, "JMP LOOP%d\n", temp);
    fprintf(fptr, "END%d:\n", temp);

    freeReg(reg);
}

void generate_repeat_until_code(tnode *root, FILE *fptr)
{

    int temp = label++;

    fprintf(fptr, "LOOP%d:\n", temp);
    code_Generation(root->right, fptr, temp);
    int reg = generate_boolean_code(root->left, fptr);
    fprintf(fptr, "JNZ R%d, END%d\n", reg, temp);
    fprintf(fptr, "JMP LOOP%d\n", temp);
    fprintf(fptr, "END%d:\n", temp);

    freeReg(reg);
}

int getArrayLastAddress(Stnode *node)
{
    int startAddress = node->binding;
    int size = node->size;
    int innerSize = node->innerSize;
    int totalElements = size * innerSize;
    return startAddress + totalElements;
}

void check_array_bound(int indexReg, tnode *root, FILE *fptr)
{
    int FirstAddr = getAddress(root->entry);
    int LastAddr = getArrayLastAddress(root->entry);

    int firstAddrReg = getReg();
    int lastAddrReg = getReg();

    fprintf(fptr, "MOV R%d, %d\n", firstAddrReg, FirstAddr);
    fprintf(fptr, "MOV R%d, %d\n", lastAddrReg, LastAddr);
    fprintf(fptr, "ADD R%d, R%d\n", indexReg, firstAddrReg);

    int temp = conditionLabel++;

    fprintf(fptr, "LE R%d, R%d\n", lastAddrReg, indexReg);
    fprintf(fptr, "JZ R%d, ARRAY_BOUND%d\n", lastAddrReg, temp);

    fprintf(fptr, "MOV R%d, \"ARRAY OUT OFF BOUND\"\n", lastAddrReg);
    printContent(lastAddrReg, fptr);
    exitProgram(fptr);
    fprintf(fptr, "ARRAY_BOUND%d:\n", temp);

    freeReg(firstAddrReg);
    freeReg(lastAddrReg);
}

int generate_code_array_index(tnode *root, FILE *fptr)
{
    int regIndex = generate_arithmetic_code(root->right, fptr);
    check_array_bound(regIndex, root->left, fptr);
    return regIndex;
}

void generate_code_array_read(tnode *root, FILE *fptr)
{
    int indexReg = generate_code_array_index(root, fptr);
    generate_Code_ReadSys(indexReg, fptr);
    freeReg(indexReg);
}

void code_Generation(tnode *root, FILE *fptr, int temp)
{
    if (root == NULL)
        return;

    if (root->nodetype == NODE_TYPE_CONNECTOR)
    {
        code_Generation(root->left, fptr, temp);
        code_Generation(root->right, fptr, temp);
    }
    else if (root->nodetype == NODE_TYPE_READ)
    {
        readSystemCall(root, fptr);
    }
    else if (root->nodetype == NODE_TYPE_WRITE)
    {
        writeSystemCall(root, fptr);
    }
    else if (root->nodetype == NODE_TYPE_ASSIGN)
    {
        generate_assignment_code(root, fptr);
    }
    else if (root->nodetype == NODE_TYPE_IF_ELSE)
    {
        generate_if_else_code(root, fptr, temp);
    }
    else if (root->nodetype == NODE_TYPE_IF)
    {
        generate_if_code(root, fptr, temp);
    }
    else if (root->nodetype == NODE_TYPE_WHILE)
    {
        generate_while_code(root, fptr);
    }
    else if (root->nodetype == NODE_TYPE_DO_WHILE)
    {
        generate_do_while_code(root, fptr);
    }
    else if (root->nodetype == NODE_TYPE_REPEAT_UNTIL)
    {
        generate_repeat_until_code(root, fptr);
    }
    else if (root->nodetype == NODE_TYPE_BREAK)
    {
        fprintf(fptr, "JMP END%d\n", temp);
    }
    else if (root->nodetype == NODE_TYPE_CONTINUE)
    {
        fprintf(fptr, "JMP LOOP%d\n", temp);
    }

    return;
}