%{
#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"
%}

number [0-9]+

%%

{number} {
	yylval.str = strdup(yytext);
	return NUM;
}

"+" {
	return PLUS;
}

"-" {
	return MINUS;
}

"*" {
	return MULT;
}

[ \t]   { /* skip spaces and tabs */ }

\n      { return '\n'; }

. { }

%%

int yywrap(){
	return 0;
}

