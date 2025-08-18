
%{
#include <stdio.h>
#include <stdlib.h>    // for atoi()
#include "./exprtree.h"
#include "./y.tab.h"
%}

%%

[0-9]+ { yylval.node = makeLeafNode(atoi(yytext)); return NUM; }
"+"    { return PLUS; }
"-"    { return MINUS; }
"*"    { return MULT; }
"/"    { return DIV; }
[ \t]  { }  // ignore spaces and tabs
\n     { return NEWLINE; }
[()]   { return *yytext; }
.      { }

%%

int yywrap() {
    return 1;
}
