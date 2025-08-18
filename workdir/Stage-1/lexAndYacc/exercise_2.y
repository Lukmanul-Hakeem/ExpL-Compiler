%{

    #include "./../utils/parseTree.h"
    #include "./../utils/codeGeneration.h"

    void yyerror(const char* error);
    int yylex();
    void makeExecutableFile(struct t_node* node, FILE* fptr);

    int data = -1;
    FILE* fptr = NULL;


%}


%union{
    struct t_node* node;
}

%token <node> NUM PLUS MINUS MULT DIV LBRACE RBRACE NEWLINE
%type <node> expr

%left PLUS MINUS
%left MULT DIV

%%

START : expr NEWLINE {
            makeExecutableFile($1, fptr);
            exit(0);
        }
    ;
expr  : expr PLUS expr {
            $<node>$ = makeOperatorNode('+', $1, $3);
        } 
    |   expr MINUS expr {
            $<node>$ = makeOperatorNode('-', $1, $3);
        } 
    |   expr MULT expr {
            $<node>$ = makeOperatorNode('*', $1, $3);
        }  
    |   expr DIV expr {
            $<node>$ = makeOperatorNode('/', $1, $3);
        } 
    |   NUM {
            $<node>$ = $1;
        }
    |   '(' expr ')'  {
            $<node>$ = $2;
        }
    ;

%%

void makeExecutableFile(struct t_node* node, FILE* fptr){

    generateHeader(fptr);
    int data = code_Generation(node, fptr);
    addDataToStack(data, fptr);
    printContent(data, fptr);
    exitProgram(fptr);
    freeReg(data);

}

void yyerror(const char* error){
    printf("ERROR : %s\n", error);
}

int main(int argc, char* argv[]){
    if(argc > 1){
        fptr = fopen(argv[1], "w");
    }
    yyparse();
    return 0;
}




