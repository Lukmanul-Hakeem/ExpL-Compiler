%{
    // #include <stdio.h>
    // #include <stdlib.h>
    #include "y.tab.h"
    #include "./../utils/parseTree.h"

%}

%%

[0-9]+      { yylval.node = create_node(atoi(yytext), NODE_TYPE_VALUE, NULL, NULL, NULL); return NUM; }

"begin"     { return PBEGIN; }
"end"       { return END; }
"write"     { return WRITE; }
"read"      { return READ; }

";"         { return PUNCTUATION; }

[a-z]      { yylval.node = create_node(-1, NODE_TYPE_ID, yytext, NULL, NULL); return ID; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }
"="         { return EQUAL; }
"("         { return LPAREN; }
")"         { return RPAREN; }

[ \t\r]+    {  }
\n          {  }

.           {  }

%%

int yywrap() {
    return 1;
}