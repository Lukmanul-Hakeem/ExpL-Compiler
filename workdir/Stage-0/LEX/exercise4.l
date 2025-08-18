%{
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;
%}

%option noyywrap

%%

"//".* {
    printf("Single-line comment: %s\n", yytext);
}

"/*"([^*]|\*+[^/])*"*/" {
    printf("Multi-line comment: %s\n", yytext);
}

[ \t\n]+   { }

.          { }

%%

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* fptr = fopen(argv[1], "r");
        if (fptr) yyin = fptr;
    }
    yylex();  
    return 0;
}
