%{
    #include "y.tab.h"
    #include "./../utils/parseTree.h"

%}

%%

[0-9]+      { yylval.node = create_node(atoi(yytext), DATA_TYPE_INTEGER, NODE_TYPE_VALUE, NULL, NULL, NULL); return NUM; }

"begin"     { return PBEGIN; }
"end"       { return END; }
"write"     { return WRITE; }
"read"      { return READ; }
"if"        { return IF; }
"then"      { return THEN; }
"else"      { return ELSE; }
"endif"     { return ENDIF; }
"while"     { return WHILE; }
"do"        { return DO; }
"repeat"    { return REPEAT; }
"until"     { return UNTIL; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }



";"         { return PUNCTUATION; }

[a-z]      { yylval.node = create_node(-1, DATA_TYPE_INTEGER, NODE_TYPE_ID, yytext, NULL, NULL); return ID; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULT; }
"/"         { return DIV; }

"="         { return EQUAL; }
"=="        { return EQ; }

"<"         { return LT; }
"<="        { return LE; }

">"         { return GT; }
">="        { return GE; }

"!"         { return NOT; }
"!="        { return NE; }

"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }

[ \t\r]+    {  }
\n          {  }

.           {  }

%%

int yywrap() {
    return 1;
}