%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror(const char* ch);
%}

%token NUM PLUS MINUS MULT

%left PLUS MINUS
%left MULT

%%

start : expr  {printf("\nCOMPLETED\n");}

expr : NUM {printf("%d ",$1);};
     	| expr PLUS expr  { printf("+ "); }
	| expr MINUS expr { printf("- "); }
	| expr MULT expr  { printf("* "); } ;

%%

int yyerror(const char* ch){
	printf("error : %s\n", ch);
	return 0;
}

int main(){
	yyparse();
	return 0;
}
