%{
    #include "./../utils/parseTree.h"
    #include "./../GlobalSymbolTable/GlobalSymbolTable.h"

    FILE* inputFile;  

    void yyerror(const char* error);
    int yylex(void);

    int Type = DATA_TYPE_VOID;
    extern FILE* yyin;
%}

%union{
    tnode* node;
}

%token PBEGIN END
%token READ WRITE
%token LPAREN RPAREN LBRACE RBRACE
%token PUNCTUATION COMMA NEWLINE
%token IF ELSE THEN ENDIF 
%token WHILE DO REPEAT UNTIL BREAK CONTINUE
%token PLUS MINUS MULT DIV EQUAL LT GT LE GE NOT NE EQ
%token <node> NUM ID STRING_LITERAL
%token DECL ENDDECL
%token INT STR

%type  <node> Program Slist Stmt InputStmt OutputStmt AsgStmt E IfStmt whileStmt doWhileStmt repeatStmt breakStmt continueStmt

%right EQUAL
%left LT GT LE GE EQ NE
%left PLUS MINUS
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
            Stnode* temp = Lookup($3->varname);
            if(temp){
                yyerror("VARIABLE ALREADY EXISTS\n");
                exit(1);
            }
            Install($3->varname, Type, 1);
        }
    | ID
        {
            Stnode* temp = Lookup($1->varname);
            if(temp){
                yyerror("VARIABLE ALREADY EXISTS\n");
                exit(1);
            }
            Install($1->varname, Type, 1);
        }
    ;

Program
    : PBEGIN Slist END PUNCTUATION
        {
            // makeExecutableFile( $2, outputFile);
            inorder($2);
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
            Stnode* temp = Lookup($3->varname);
            if(temp == NULL){
                yyerror("VARIABLE IS NOT DECLARED\n");
            }

            $3->entry = temp;
            $3->type = temp->type;

            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_READ, NULL, NULL, $3, NULL);
        }
    ;

OutputStmt
    : WRITE LPAREN E RPAREN PUNCTUATION
        {
            if($3->type == DATA_TYPE_INTEGER || $3->type == DATA_TYPE_STRING) $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_WRITE, NULL, NULL, $3, NULL);
            else yyerror("NODE TYPE MISMATCH IN WRITE\n");
        }
    ;

AsgStmt
    : ID EQUAL E PUNCTUATION
        {
            Stnode* temp = Lookup($1->varname);
            if(temp == NULL){
                yyerror("VARIABLE IS NOT DECLARED\n");
            }

            $1->entry = temp;
            $1->type = temp->type; 

            // printf("%s = \n",$1->varname);

            if( ($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) || ($1->type == DATA_TYPE_STRING && $3->type == DATA_TYPE_STRING) ) $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_ASSIGN, NULL, NULL, $1, $3);
            else {
                printf("%s %s\n",getNodeSymbol($1->type), getNodeSymbol($3->type));
                yyerror("nodeType MisMatch - ASSIGN!\n");
            }
        }

    ;


IfStmt
    : IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF PUNCTUATION
        {
            if($3->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition in IF must be boolean\n");
            }

            tnode* connectorNode = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_CONNECTOR, NULL, NULL, $6, $8);
            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_IF_ELSE, NULL, NULL, $3, connectorNode);
        }
    | IF LPAREN E RPAREN THEN Slist ENDIF PUNCTUATION
        {

            if($3->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition in IF must be boolean\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_IF, NULL, NULL, $3, $6);
        }
    ;

whileStmt 
    : WHILE LPAREN E RPAREN LBRACE Slist RBRACE
        {
            if($3->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition must be boolean!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_WHILE, NULL, NULL, $3, $6);
        }
    ;

doWhileStmt
    : DO LBRACE Slist RBRACE WHILE LPAREN E RPAREN PUNCTUATION
        {
            if($7->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition must be boolean!\n");
            }
            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_DO_WHILE, NULL, NULL, $7, $3);
        }
    ;

repeatStmt
    : REPEAT LBRACE Slist RBRACE UNTIL LPAREN E RPAREN PUNCTUATION
        {
            if($7->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition must be boolean!\n");
            }
            $$ = create_node(-1, NULL, DATA_TYPE_VOID, NODE_TYPE_REPEAT_UNTIL, NULL, NULL, $7, $3);
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
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_INTEGER, NODE_TYPE_PLUS, NULL, NULL, $1, $3); 
        }
    | E MINUS E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_INTEGER, NODE_TYPE_MINUS, NULL, NULL, $1, $3); 
        }
    | E MULT E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_INTEGER, NODE_TYPE_MULT, NULL, NULL, $1, $3); 
        }
    | E DIV E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_INTEGER, NODE_TYPE_DIV, NULL, NULL, $1, $3); 
        }

    | E LT E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_BOOLEAN, NODE_TYPE_LT, NULL, NULL, $1, $3); 
        }
    
    | E GT E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_BOOLEAN, NODE_TYPE_GT, NULL, NULL, $1, $3); 
        }
    
    | E LE E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_BOOLEAN, NODE_TYPE_LE, NULL, NULL, $1, $3); 
        }
    
    | E GE E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_BOOLEAN, NODE_TYPE_GE, NULL, NULL, $1, $3);   
        }

    | E EQ E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_BOOLEAN, NODE_TYPE_EQ, NULL, NULL, $1, $3); 
        }
    
    | E NE E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, NULL, DATA_TYPE_BOOLEAN,  NODE_TYPE_NE, NULL, NULL, $1, $3); 
        }
    
    | NUM
        { $$ = $1; }
    | STRING_LITERAL
        { $$ = $1; }
    | ID
        { 
            Stnode* temp = Lookup($1->varname);
            if(temp == NULL){
                yyerror("VARIABLE IS NOT DECLARED\n");
            }

            $1->entry = temp;
            $1->type = temp->type;
            $$ = $1; 

        }
    | LPAREN E RPAREN
        { 
            $$ = $2; 
        }
    ;


%%

void yyerror(const char* error) {
    fprintf(stderr, "Error: %s\n", error);
    exit(0);
}

int main(int argc, char** argv){
    if(argc <= 1){
        yyerror("NO INPUT FILE\n");
    }

    FILE* inputFile = fopen(argv[1], "r");
    yyin = inputFile;
    yyparse();
    fclose(inputFile);

    return 0;
}