%{
    #include "./../Constants/constants.h"
    #include "./../Parse_Tree/parse_tree.h"
    #include "./../Symbol_Table/global_symbol_table.h"

    FILE* outputFile; 
    FILE* inputFile;   

    void yyerror(const char* error);
    int yylex(void);

    int type_variable = DATA_TYPE_VOID;

    // void makeExecutableFile(struct tnode* node, FILE* fptr);
    extern FILE* yyin;
    extern p_node* param_head;
    extern p_node* param_tail;
%}

%union{
    ast_node* AST_node;
    gst_node* GST_node;
    p_node* param_node;
}

%token PBEGIN END
%token READ WRITE
%token IF ELSE THEN ENDIF 
%token WHILE DO REPEAT UNTIL BREAK CONTINUE
%token EQUAL LT GT LE GE NOT NE EQ AND
%token DECL ENDDECL
%token INT STR

%type <param_node> ParamList
%type <AST_node> Param
%token <AST_node> NUM ID STRING_LITERAL

%right EQUAL
%left LT GT LE GE EQ NE
%left '+' '-' '%'
%left '*' '/'

%%

GDeclBlock  : DECL GDeclList ENDDECL            { print_gstable(); }
            | DECL ENDDECL
            ;

GDeclList   : GDeclList GDecl 
            | GDecl

GDecl       : Type GidList ';'
            ;
    
GidList     : GidList ',' Gid 
            | Gid

Gid         : ID                                { gst_install($1->name, type_variable, 1, 0, NULL); }
            | ID '[' NUM ']'                    { gst_install($1->name, type_variable, 1, $3->value.iVal, NULL); }
            | ID '(' ParamList ')'              { gst_install($1->name, type_variable, 1, 0, $3); param_head = NULL; param_tail = NULL; }
            ;

ParamList   : ParamList ',' Param               { param_install($3->name, type_variable); $$ = param_head; }
            | Param                             { param_install($1->name, type_variable); $$ = param_head; }
            |                                   { $$ = NULL; }
            ;

Param       : Type ID                           { $$ = $2; }

Type        : INT                               { type_variable = DATA_TYPE_INTEGER; }
            | STR                               { type_variable = DATA_TYPE_STRING; }
            ;

%%

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