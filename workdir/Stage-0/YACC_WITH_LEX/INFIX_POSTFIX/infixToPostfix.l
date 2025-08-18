%{
#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"
%}

number [0-9]+


%%

{number} {

	yylval = atoi(yytext);
	return NUM;
		
}

"+" {	return PLUS;	}

"*" {	return MULT;    }

"-" {	return MINUS;	}

[ \t\n] { }
. { }

%%


int yywrap(){
	return 1;
}



	
