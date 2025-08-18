%{
#include "./../utils/parseTree.h"
void yyerror(const char* error);
int yylex();
%}
%union{
    struct t_node* node;
}

%token <node> NUM PLUS MINUS MULT DIV LBRACE RBRACE NEWLINE
%type <node> expr

%left PLUS MINUS
%left MULT DIV

%%

START : expr NEWLINE {
            printf("\n\n-------PostFix-------\n\n");
            printPostfix($1);
            printf("\n\n-------PreFix-------\n\n");
            printPrefix($1);
            printf("\n\ncompleted.\n");
            exit(0);
        }
    ;
expr  : expr PLUS expr {
            $<node>$ = makeOperatorNode('+', $1, $3);
        } 
    |   expr MINUS expr {
            $<node>$ = makeOperatorNode('-', $1, $3);
        } 
    |   expr MULT expr {
            $<node>$ = makeOperatorNode('*', $1, $3);
        }  
    |   expr DIV expr {
            $<node>$ = makeOperatorNode('/', $1, $3);
        } 
    |   NUM {
            $<node>$ = $1;
        }
    |   '(' expr ')'  {
            $<node>$ = $2;
        }
    ;

%%

void yyerror(const char* error){
    printf("ERROR : %s\n", error);
}

int main(){
    yyparse();
    return 0;
}




