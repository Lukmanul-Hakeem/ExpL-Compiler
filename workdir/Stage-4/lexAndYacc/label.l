%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "./labelTransition/label.h"

    int instructCount = 0;
    int pass = 1;
    int baseAddr = 2056;
    FILE* output;

%}

number      [0-9]+
register    R[0-9]+
label       [A-Za-z][A-Za-z0-9_]*
space       [ \t]+

jz_instr    JZ{space}{register},{space}?{label}
jnz_instr   JNZ{space}{register},{space}?{label}
jmp_instr   JMP{space}{label}

%%

{label}":"\n {
    if(pass == 1){
        int address = baseAddr + 2 * instructCount;
        char labelName[50];
        strncpy(labelName, yytext, yyleng - 2);
        labelName[yyleng - 2] = '\0';
        insertLabel(labelName, address);
    }
}

{jz_instr}\n {
    if(pass == 1){
        instructCount++;
    } else {

        char reg[10], curLabel[50];
        sscanf(yytext, "JZ %s %s", reg, curLabel);
        int address = searchLabel(curLabel);

        if(address == -1){
            exit(1);
        }
        fprintf(output, "JZ %s %d\n", reg, address);
    }
}



{jnz_instr}\n {
    if(pass == 1){
        instructCount++;
    } else {

        char reg[10], curLabel[50];
        sscanf(yytext, "JNZ %s , %s", reg, curLabel);

        int address = searchLabel(curLabel);
        if(address == -1){
            exit(1);
        }

        fprintf(output, "JNZ %s %d\n", reg, address);
    }
}

{jmp_instr}\n {
    if(pass == 1){
        instructCount++;
    } else {

        char curLabel[50];
        sscanf(yytext, "JMP %s\n", curLabel);
        int address = searchLabel(curLabel);

        if(address == -1){
            exit(1);
        }
        fprintf(output, "JMP %d\n",address);
    }
}

{number}\n {
    if(pass == 2){
        fprintf(output, "%s", yytext);
    }
}

.*\n {
    if(pass == 1){
        instructCount++;
    } else {
        fprintf(output, "%s", yytext);
    }
}

%%

int yywrap() {
    if(pass == 1){
        pass++;
        rewind(yyin);   
        instructCount = 0; 
        return 0;       
    }
    return 1;          
}

int main(int argc, char** argv) {
    if(argc < 3){
        exit(1);
    }

    yyin = fopen(argv[1], "r");
    if(!yyin){
        perror("Error opening input file");
        exit(1);
    }

    output = fopen(argv[2], "w");
    if(!output){
        perror("Error opening output file");
        exit(1);
    }

    yylex();

    fclose(output);
    fclose(yyin);
    return 0;
}