%{

#include<stdio.h>
#include "./y.tab.h"
#include "./../utils/parseTree.h"

%}

%%

[0-9]+  { yylval.node = makeLeafNode( atoi(yytext) ); return NUM; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULT; }
"/"     { return DIV; }
"("     { return LBRACE; }
")"     { return RBRACE; }
\n      { return NEWLINE; }
.|\t    { }

%%

int yywrap(){
    return 1;
}