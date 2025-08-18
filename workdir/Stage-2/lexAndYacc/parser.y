%{
    #include "./../utils/parseTree.h"
    #include "./../utils/codeGeneration.h"

    FILE* outputFile; // EXECUTABLE FILE FOR SOURCE CODE
    FILE* inputFile;  // INPUT TO THE LEXICAL ANALYZER

    void yyerror(const char* error);
    int yylex(void);
    void makeExecutableFile(struct tnode* node, FILE* fptr);
    extern FILE* yyin;
%}

%union {
    struct tnode* node;
}

%token PBEGIN END READ WRITE EQUAL PLUS MINUS MULT DIV LPAREN RPAREN PUNCTUATION NEWLINE
%token <node> NUM ID

%type  <node> Program Slist Stmt InputStmt OutputStmt AsgStmt E

%left PLUS MINUS
%left MULT DIV

%%

Program
    : PBEGIN Slist END PUNCTUATION
        {
            makeExecutableFile( $2, outputFile);
            inorder($2);
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
            $$ = create_node(-1, NODE_TYPE_CONNECTOR, NULL, $1, $2);
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
    ;

InputStmt
    : READ LPAREN ID RPAREN PUNCTUATION
        {
            $$ = create_node(-1, NODE_TYPE_READ, NULL, $3, NULL);
        }
    ;

OutputStmt
    : WRITE LPAREN E RPAREN PUNCTUATION
        {
            $$ = create_node(-1, NODE_TYPE_WRITE, NULL, $3, NULL);
        }
    ;

AsgStmt
    : ID EQUAL E PUNCTUATION
        {
            $$ = create_node(-1, NODE_TYPE_ASSIGN, NULL, $1, $3);
        }
    ;

E
    : E PLUS E
        { $$ = create_node(-1, NODE_TYPE_PLUS, NULL, $1, $3); }
    | E MINUS E
        { $$ = create_node(-1, NODE_TYPE_MINUS, NULL, $1, $3); }
    | E MULT E
        { $$ = create_node(-1, NODE_TYPE_MULT, NULL, $1, $3); }
    | E DIV E
        { $$ = create_node(-1, NODE_TYPE_DIV, NULL, $1, $3); }
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
    code_Generation(node, fptr);
    exitProgram(fptr);

}

void yyerror(const char* error) {
        fprintf(stderr, "Error: %s\n", error);
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