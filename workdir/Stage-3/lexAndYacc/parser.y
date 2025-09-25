%{
    #include "./../utils/codeGeneration.h"

    FILE* outputFile; 
    FILE* inputFile;  

    void yyerror(const char* error);
    int yylex(void);
    void makeExecutableFile(struct tnode* node, FILE* fptr);
    extern FILE* yyin;

%}

%union {
    struct tnode* node;
}

%token PBEGIN END
%token READ WRITE
%token LPAREN RPAREN LBRACE RBRACE
%token PUNCTUATION NEWLINE
%token IF ELSE THEN ENDIF 
%token WHILE DO REPEAT UNTIL BREAK CONTINUE
%token PLUS MINUS MULT DIV EQUAL LT GT LE GE NOT NE EQ
%token <node> NUM ID

%type  <node> Program Slist Stmt InputStmt OutputStmt AsgStmt E IfStmt whileStmt doWhileStmt repeatStmt breakStmt continueStmt

%right EQUAL
%left LT GT LE GE EQ NE
%left PLUS MINUS
%left MULT DIV

%%

Program
    : PBEGIN Slist END PUNCTUATION
        {
            makeExecutableFile( $2, outputFile);
            // inorder($2);
            // evaluate($2);
            exit(0); 
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
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_CONNECTOR, NULL, $1, $2);
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
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_READ, NULL, $3, NULL);
        }
    ;

OutputStmt
    : WRITE LPAREN E RPAREN PUNCTUATION
        {
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_WRITE, NULL, $3, NULL);
        }
    ;

IfStmt
    : IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF PUNCTUATION
        {
            if($3->type == DATA_TYPE_INTEGER){
                yyerror("nodeType MisMatch!\n");
            }

            tnode* connectorNode = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_CONNECTOR, NULL, $6, $8);
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_IF_ELSE, NULL, $3, connectorNode);
        }
    | IF LPAREN E RPAREN THEN Slist ENDIF PUNCTUATION
        {

            if($3->type == DATA_TYPE_INTEGER){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_IF, NULL, $3, $6);
        }
    ;

whileStmt 
    : WHILE LPAREN E RPAREN LBRACE Slist RBRACE
        {
            if($3->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition must be boolean!\n");
            }

            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_WHILE, NULL, $3, $6);
        }
    ;

doWhileStmt
    : DO LBRACE Slist RBRACE WHILE LPAREN E RPAREN PUNCTUATION
        {
            if($7->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition must be boolean!\n");
            }
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_DO_WHILE, NULL, $7, $3);
        }
    ;

repeatStmt
    : REPEAT LBRACE Slist RBRACE UNTIL LPAREN E RPAREN PUNCTUATION
        {
            if($7->type != DATA_TYPE_BOOLEAN){
                yyerror("Condition must be boolean!\n");
            }
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_REPEAT_UNTIL, NULL, $7, $3);
        }
    ;

breakStmt
    : BREAK PUNCTUATION
        {
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_BREAK, NULL, NULL, NULL);
        }
    ;

continueStmt
    : CONTINUE PUNCTUATION
        {
            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_CONTINUE, NULL, NULL, NULL);
        }
    ;


AsgStmt
    : ID EQUAL E PUNCTUATION
        {
            if($1->type != DATA_TYPE_INTEGER || $3->type != DATA_TYPE_INTEGER){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_VOID, NODE_TYPE_ASSIGN, NULL, $1, $3);
        }
    ;

E
    : E PLUS E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_INTEGER, NODE_TYPE_PLUS, NULL, $1, $3); 
        }
    | E MINUS E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_INTEGER, NODE_TYPE_MINUS, NULL, $1, $3); 
        }
    | E MULT E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_INTEGER, NODE_TYPE_MULT, NULL, $1, $3); 
        }
    | E DIV E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_INTEGER, NODE_TYPE_DIV, NULL, $1, $3); 
        }

    | E LT E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_BOOLEAN, NODE_TYPE_LT, NULL, $1, $3); 
        }
    
    | E GT E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_BOOLEAN, NODE_TYPE_GT, NULL, $1, $3); 
        }
    
    | E LE E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_BOOLEAN, NODE_TYPE_LE, NULL, $1, $3); 
        }
    
    | E GE E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_BOOLEAN, NODE_TYPE_GE, NULL, $1, $3);   
        }

    | E EQ E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_BOOLEAN, NODE_TYPE_EQ, NULL, $1, $3); 
        }
    
    | E NE E
        { 
            if( !($1->type == DATA_TYPE_INTEGER && $3->type == DATA_TYPE_INTEGER) ){
                yyerror("nodeType MisMatch!\n");
            }

            $$ = create_node(-1, DATA_TYPE_BOOLEAN,  NODE_TYPE_NE, NULL, $1, $3); 
        }
    
    | NUM
        { $$ = $1; }
    | ID
        { $$ = $1; }
    | LPAREN E RPAREN
        { $$ = $2; }
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