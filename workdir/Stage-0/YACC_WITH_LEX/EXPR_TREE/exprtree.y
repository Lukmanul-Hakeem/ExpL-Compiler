%{
#include <stdio.h>
#include <stdlib.h>
#include "./exprtree.h"

typedef struct tnode tnode;

int yylex(void);
void yyerror(const char *s);
%}

%union {
    tnode* node;
}

%token <node> NUM
%token PLUS MULT MINUS DIV NEWLINE
%left PLUS MINUS
%left MULT DIV

%type <node> expr START

%%

START : expr NEWLINE { 
            printf("answer : %d\n", evaluate($1)); 
            exit(0); 
        }
     ;

expr : NUM 
     { $$ = $1; }
     
     | expr PLUS expr 
     { $$ = makeOperatorNode('+', $1, $3); }

     | expr MULT expr 
     { $$ = makeOperatorNode('*', $1, $3); }

     | expr DIV expr 
     { $$ = makeOperatorNode('/', $1, $3); }

     | expr MINUS expr 
     { $$ = makeOperatorNode('-', $1, $3); }

     | '(' expr ')' 
     { $$ = $2; }
     ;

%%

void yyerror(const char* error) {
    printf("%s\n", error);
}

int main() {
    yyparse();
    return 0;
}
