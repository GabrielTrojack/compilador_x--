%{
    #include "arvoresintatica.h"
    int yylex(void);
    int yyerror(const char *s);
%}

%token STRING

%%

programa:
    STRING
    |
    ;

%%

int yywrap(){
    return 1;
}

int main(void) {    
    debugTest();

    yyparse();
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
    return 0;
}