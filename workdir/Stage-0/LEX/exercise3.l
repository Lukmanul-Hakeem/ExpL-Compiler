%{
#include<stdio.h>
#include<stdlib.h>
%}

word [A][a-zA-Z]{2}

%%

{word}  {
    printf("%s\n",yytext);
}

.|\n { }

%%

int yywrap(){
    return 1;
}

int main(int argc, char* argv[]){

    if(argc > 1){
        FILE* fptr = fopen(argv[1],"r");
        if(fptr)yyin = fptr;
    }

    yylex();
    return 0;

}