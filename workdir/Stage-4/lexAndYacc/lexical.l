%{
    
    #include "./../GlobalSymbolTable/GlobalSymbolTable.h"
    #include "./../utils/parseTree.h"
    #include "y.tab.h"
%}

%%

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

"int"       { return INT; }
"str"       { return STR; }
"decl"      { return DECL; }
"enddecl"   { return ENDDECL; }

";"         { return PUNCTUATION; }
","         { return COMMA; }

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
"["         { return LSQUARE; }
"]"         { return RSQUARE; }

[a-zA-Z][A-Za-z0-9]*   { yylval.node = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_ID, yytext, NULL, NULL, NULL); return ID; } 

\"[^\"]*\"             { 
    int leng = yyleng - 2;

    char* str = (char*)malloc(leng + 1);
    strncpy(str, yytext + 1, leng);
    str[leng] = '\0';

    yylval.node = create_node(-1, str, DATA_TYPE_STRING, NODE_TYPE_STRING, NULL, NULL, NULL, NULL); 

    free(str);

    return STRING_LITERAL;
}

[0-9]+      { yylval.node = create_node(atoi(yytext), NULL, DATA_TYPE_INTEGER, NODE_TYPE_VALUE, NULL, NULL, NULL, NULL); return NUM; }

[ \t\r]+    {  }
\n          {  }

.           {  }

%%


int yywrap(){
    return 1;
}

