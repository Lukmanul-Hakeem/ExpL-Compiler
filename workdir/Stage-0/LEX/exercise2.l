%{
    #include <stdio.h>
    #include <stdlib.h>

    int countInt = 0;
    int countFloat = 0;
    extern FILE *yyin;
%}

INTEGER_PATTERN     (-?[1-9][0-9]*)|0
FLOAT_NUMBER        -?([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)

%%

{INTEGER_PATTERN} {
    countInt++;
    printf("Integer : %s\n", yytext);
}

{FLOAT_NUMBER}  {
    countFloat++;
    printf("Float : %s\n", yytext);
}

.|\n    {  }

%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* ftpr = fopen(argv[1], "r");
        if (ftpr) yyin = ftpr; 
    }

    yylex();
    printf("Number of Integers : %d\n", countInt);
    printf("Number of Floats   : %d\n", countFloat);
    return 0;
}
