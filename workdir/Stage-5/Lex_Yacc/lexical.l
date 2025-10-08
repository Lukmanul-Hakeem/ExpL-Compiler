%{
    #include "./../Symbol_Table/global_symbol_table.h"
    #include "./../Parse_Tree/parse_tree.h"
    #include "./../Constants/constants.h"
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

[+\-*/%]    { return *yytext; }

"="         { return EQUAL; }
"=="        { return EQ; }

"<"         { return LT; }
"<="        { return LE; }

">"         { return GT; }
">="        { return GE; }

"!"         { return NOT; }
"!="        { return NE; }
"&"         { return AND; }

[(){},;\[\]] { return *yytext; }

[a-zA-Z][A-Za-z0-9]* {
    // Identifier node
    union Constant val;  // no constant value for ID
    yylval.AST_node = create_ast_node(NODE_TYPE_ID, yytext, val);
    return ID;
}

\"[^\"]*\" {
    
    int leng = yyleng - 2;
    char* str = (char*)malloc(leng + 1);
    strncpy(str, yytext + 1, leng);
    str[leng] = '\0';

    union Constant val;
    val.sVal = str;  // assuming union has strVal member

    yylval.AST_node = create_ast_node(NODE_TYPE_STRING, str, val);
    return STRING_LITERAL;
}

[0-9]+ {
    union Constant val;
    val.iVal = atoi(yytext);

    yylval.AST_node = create_ast_node(NODE_TYPE_VALUE, NULL, val);
    return NUM;
}

[ \t\r]+    { /* ignore whitespace */ }
\n          { /* ignore newlines */ }

.           { /* ignore any other character */ }

%%

int yywrap(){
    return 1;
}
