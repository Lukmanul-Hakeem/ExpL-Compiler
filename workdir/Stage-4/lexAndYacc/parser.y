%{
    #include "./../utils/parseTree.h"
    #include "./../utils/codeGeneration.h"
    #include "./../GlobalSymbolTable/GlobalSymbolTable.h"

    FILE* outputFile; 
    FILE* inputFile;   

    void yyerror(const char* error);
    int yylex(void);

    int Type = DATA_TYPE_VOID;

    void makeExecutableFile(struct tnode* node, FILE* fptr);
    extern FILE* yyin;
%}

%union{
    tnode* node;
}

%token PBEGIN END
%token READ WRITE
%token LPAREN RPAREN LBRACE RBRACE LSQUARE RSQUARE
%token PUNCTUATION COMMA NEWLINE
%token IF ELSE THEN ENDIF 
%token WHILE DO REPEAT UNTIL BREAK CONTINUE
%token PLUS MINUS MULT DIV MOD EQUAL LT GT LE GE NOT NE EQ
%token <node> NUM ID STRING_LITERAL
%token DECL ENDDECL
%token INT STR

%type  <node> Program Slist Stmt InputStmt OutputStmt AsgStmt E IfStmt whileStmt doWhileStmt repeatStmt breakStmt continueStmt

%right EQUAL
%left LT GT LE GE EQ NE
%left PLUS MINUS MOD
%left MULT DIV


%%

FinalProgram 
    : Declarations Program
        {
            exit(0);
        }

Declarations
    : DECL DeclList ENDDECL
        { print_symbol_table(); }

    | DECL ENDDECL
    ;

DeclList
    : DeclList Decl
    | Decl
    ;

Decl
    : Type VarList PUNCTUATION
    ;

Type
    : INT   { Type = DATA_TYPE_INTEGER; }
    | STR   { Type = DATA_TYPE_STRING; }
    ;

VarList
    : VarList COMMA ID
        {
            create_symbol_table_entry($3, Type, 1, 0);
        }
    | ID
        {
            create_symbol_table_entry($1, Type, 1, 0);
        }
    | VarList COMMA ID LSQUARE NUM RSQUARE
        {
            create_symbol_table_entry($3, Type, 1, $5->val);
        }
    | ID LSQUARE NUM RSQUARE
        {
            create_symbol_table_entry($1, Type, 1, $3->val);
        }
    | ID LSQUARE NUM RSQUARE LSQUARE NUM RSQUARE
        {
            create_symbol_table_entry($1, Type, $3->val, $6->val);
        }
    | VarList COMMA ID LSQUARE NUM RSQUARE LSQUARE NUM RSQUARE
        {
            create_symbol_table_entry($3, Type, $5->val, $8->val);
        }
    ;

Program
    : PBEGIN Slist END PUNCTUATION
        {
            inorder($2);
            makeExecutableFile( $2, outputFile);
            // evaluate($2);
        }
    | PBEGIN END PUNCTUATION
        {
            printf("No statements.\n");
            exit(0);
        }
    ;

Slist
    : Slist Stmt
        {
            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_CONNECTOR, NULL, NULL, $1, $2);
        }
    | Stmt
        {
            $$ = $1;
        }
    ;


Stmt
    : InputStmt   { $$ = $1; }
    | OutputStmt  { $$ = $1; }
    | AsgStmt     { $$ = $1; }
    | IfStmt      { $$ = $1; }
    | whileStmt   { $$ = $1; }
    | doWhileStmt { $$ = $1; }
    | repeatStmt  { $$ = $1; }
    | breakStmt   { $$ = $1; }
    | continueStmt{ $$ = $1; }
    ;

InputStmt
    : READ LPAREN ID RPAREN PUNCTUATION
        {
            $3 = create_id_node($3);
            $$ = create_read_node($3);
        }

    | READ LPAREN ID LSQUARE E RSQUARE RPAREN PUNCTUATION
        {
            tnode* arrayNode = create_array_node($3, $5);
            $$ = create_read_node(arrayNode);
        }
    | READ LPAREN ID LSQUARE E RSQUARE LSQUARE E RSQUARE RPAREN PUNCTUATION
        {
            tnode* arrayNode = create_2D_array_node($3, $5, $8);
            $$ = create_read_node(arrayNode);
        }
    ;

OutputStmt
    : WRITE LPAREN E RPAREN PUNCTUATION
        {
            $$ = create_write_node($3);
        }
    ;

AsgStmt
    : ID EQUAL E PUNCTUATION
        {
            $1 = create_id_node($1);
            $$ = create_assign_node($1, $3);
        }
    | ID LSQUARE E RSQUARE EQUAL E PUNCTUATION
        {
            tnode* arrayNode = create_array_node($1, $3);
            $$ = create_assign_node(arrayNode, $6);
        }
    | ID LSQUARE E RSQUARE LSQUARE E RSQUARE EQUAL E PUNCTUATION
        {
            tnode* arrayNode = create_2D_array_node($1, $3, $6);
            $$ = create_assign_node(arrayNode, $9);
        }

    ;


IfStmt
    : IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF PUNCTUATION
        {
            $$ = create_if_else_node($3, $6, $8);
        }
    | IF LPAREN E RPAREN THEN Slist ENDIF PUNCTUATION
        {
            $$ = create_if_node($3, $6);
        }
    ;

whileStmt 
    : WHILE LPAREN E RPAREN LBRACE Slist RBRACE
        {
            $$ = create_while_node($3, $6);
        }
    ;

doWhileStmt
    : DO LBRACE Slist RBRACE WHILE LPAREN E RPAREN PUNCTUATION
        {
            $$ = create_do_while_node($7, $3);
        }
    ;

repeatStmt
    : REPEAT LBRACE Slist RBRACE UNTIL LPAREN E RPAREN PUNCTUATION
        {
            $$ = create_repeat_until_node($7, $3);
        }
    ;

breakStmt
    : BREAK PUNCTUATION
        {
            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_BREAK, NULL, NULL, NULL, NULL);
        }
    ;

continueStmt
    : CONTINUE PUNCTUATION
        {
            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_CONTINUE, NULL, NULL, NULL, NULL);
        }
    ;



E
    : E PLUS E
        { 
            $$ = create_arithmetic_node($1, $3, NODE_TYPE_PLUS);
        }
    | E MINUS E
        { 
            $$ = create_arithmetic_node($1, $3, NODE_TYPE_MINUS);
        }
    | E MULT E
        { 
            $$ = create_arithmetic_node($1, $3, NODE_TYPE_MULT);
        }
    | E DIV E
        { 
            $$ = create_arithmetic_node($1, $3, NODE_TYPE_DIV);
        }
    | E MOD E
        {
            $$ = create_arithmetic_node($1, $3, NODE_TYPE_MOD);
        }

    | E LT E
        { 
            $$ = create_boolean_node($1, $3, NODE_TYPE_LT);
        }
    
    | E GT E
        { 
            $$ = create_boolean_node($1, $3, NODE_TYPE_GT);
        }
    
    | E LE E
        { 
            $$ = create_boolean_node($1, $3, NODE_TYPE_LE);
        }
    
    | E GE E
        { 
            $$ = create_boolean_node($1, $3, NODE_TYPE_GE); 
        }

    | E EQ E
        { 
            $$ = create_boolean_node($1, $3, NODE_TYPE_EQ);
        }
    
    | E NE E
        { 
            $$ = create_boolean_node($1, $3, NODE_TYPE_NE);
        }
    
    | NUM
        { 
            $$ = $1; 
        }
    | STRING_LITERAL
        { 
            $$ = $1;
        }
    | ID
        { 
            $1 = create_id_node($1);
            $$ = $1; 
        }
    | LPAREN E RPAREN
        { 
            $$ = $2; 
        }
    | ID LSQUARE E RSQUARE
        {
            $$ = create_array_node($1, $3);
        }
    | ID LSQUARE E RSQUARE LSQUARE E RSQUARE
        {
            $$ = create_2D_array_node($1, $3, $6);
        }
    ;


%%


void makeExecutableFile(struct tnode* node, FILE* fptr){

    generateHeader(fptr);
    code_Generation(node, fptr, -1);
    exitProgram(fptr);

}

void yyerror(const char* error) {
    fprintf(stderr, "Error: %s\n", error);
    exit(0);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        return 1;
    }
    inputFile = fopen(argv[1], "r");
    outputFile = fopen(argv[2], "w");
    if (!inputFile || !outputFile) {
        perror("File opening failed");
        return 1;
    }
    yyin = inputFile;
    yyparse();
    fclose(inputFile);
    fclose(outputFile);
    return 0;

}