%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yyerror(const char* str);
int yylex();
%}

%union {
    char* str;
}

%token <str> NUM
%token <str> PLUS
%token <str> MINUS
%token <str> MULT

%type <str> expr

%left PLUS MINUS
%left MULT

%%

start : expr '\n' {
    printf("%s\n", $1);
    free($1);
};

expr : NUM {
    $$ = strdup($1);
}
| expr PLUS expr {
    $$ = (char*)malloc(strlen($1) + strlen($3) + 4);
    sprintf($$, "+ %s %s", $1, $3);
    free($1); free($3);
}
| expr MINUS expr {
    $$ = (char*)malloc(strlen($1) + strlen($3) + 4);
    sprintf($$, "- %s %s", $1, $3);
    free($1); free($3);
}
| expr MULT expr {
    $$ = (char*)malloc(strlen($1) + strlen($3) + 4);
    sprintf($$, "* %s %s", $1, $3);
    free($1); free($3);
};

%%

int yyerror(const char* str) {
    printf("error\n");
    return 0;
}

int main() {
    yyparse();
    return 0;
}
