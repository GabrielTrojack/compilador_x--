%{
    #include "arvoresintatica.h"
    #include "tabelasimbolos.h"
    #include "tabelareservadas.h"

    int yylex(void);
    int yyerror(const char *s);
%}

/* Palavras reservadas */
%token TNI RAHC ELBOUD GNIRTS DIOV NIAM
%token FI ESLE ELIHW OD ROF
%token TUOC NIC NRUTER EDULCNI

/* Identificadores e literais */
%token IDENTIFICADOR INTEIRO REAL STRING

/* Operadores */
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO RESTO
%token ATRIBUICAO RELACIONAL

/* Separadores */
%token ABRE_PARENTESES FECHA_PARENTESES ABRE_CHAVES FECHA_CHAVES PONTO_VIRGULA

%%

programa:
    /* vazio */
    | programa token
    ;

token:
      TNI | RAHC | ELBOUD | GNIRTS | DIOV | NIAM
    | FI | ESLE | ELIHW | OD | ROF
    | TUOC | NIC | NRUTER | EDULCNI
    | IDENTIFICADOR | INTEIRO | REAL | STRING
    | SOMA | SUBTRACAO | MULTIPLICACAO | DIVISAO | RESTO
    | ATRIBUICAO | RELACIONAL
    | ABRE_PARENTESES | FECHA_PARENTESES | ABRE_CHAVES | FECHA_CHAVES | PONTO_VIRGULA
    ;
%%

int yywrap(){
    return 1;
}

int main(void) {    
    debugTest();

    yyparse();
    
    imprimeTabelaSimbolos();
    imprimeReservadas();
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
    return 0;
}