%{
#include <stdio.h>
#include <stdlib.h>
int countLine = 0;
int countChar = 0;
int countWord = 0;
%}

%%

[a-zA-Z]+ {
    countWord++; 
    countChar += yyleng;
}

\n {
    countLine++;
    countChar++;
}

[ \t] {
    countChar += yyleng;
}

. {
    countChar++;
}

%%

int yywrap(){
    return 1;
}

int main(int argc, char* argv[]){
    if(argc > 1){
        FILE* ftpr = fopen(argv[1], "r");
        if(ftpr) yyin = ftpr;
    }

    yylex();
    printf("number of characters = %d\n", countChar);
    printf("number of words = %d\n", countWord);
    printf("number of lines = %d\n", countLine);

    return 0;
}