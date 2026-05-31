%option yylineno
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "listaencadeada.c"
    int linha=1;
%}

RESERVADA ("fi"|"rof"|"elihw"|"esle"|"tuoc"|"tni"|"rahc"|"elboud"|"od"|"niam"|"gnirts")
LETRA [a-zA-Z]
DIGITO [0-9]
ID {LETRA}({LETRA}|{DIGITO})*

INTEIRO ("+"|"-")?{DIGITO}+
REAL {DIGITO}+"."{DIGITO}+
STRING \"[^"\n]*\"


%%

"\n" {linha++;}

{RESERVADA} {insere(strdup(yytext), "RESERVADA");}

{INTEIRO} {insere(strdup(yytext), "INTEIRO");}

{REAL} {insere(strdup(yytext), "REAL");}

{ID} {insere(strdup(yytext), "IDENTIFICADOR");}

{STRING} {insere(strdup(yytext), "STRING");}

 /* Operadores */

"+" {insere(strdup(yytext), "SOMA");}

"-" {insere(strdup(yytext), "SUBTRACAO");}

"/" {insere(strdup(yytext), "DIVISAO");}

"*" {insere(strdup(yytext), "MULTIPLICACAO");}

"%" {insere(strdup(yytext), "RESTO");}

"=" {insere(strdup(yytext), "ATRIBUICAO");}

">"|"<"|"=="|">="|"<="|"!=" {insere(strdup(yytext), "RELACIONAL");}

 /* Separadores */
" " {}

"(" {insere(strdup(yytext), "ABRE_PARENTESES");}

")" {insere(strdup(yytext), "FECHA_PARENTESES");}

"{" {insere(strdup(yytext), "ABRE_CHAVES");}

"}" {insere(strdup(yytext), "FECHA_CHAVES");}

";" {insere(strdup(yytext), "PONTO_VIRGULA");}


 /* Erros Léxicos */
{DIGITO}+"."{DIGITO}+"."{DIGITO}+ {
    printf("ERRO LEXICO: Numero mal formado (%s) linha %d\n",yytext, linha);
}

{DIGITO}+({DIGITO}|{LETRA})+ {
    printf("ERRO LEXICO: ID nao podem comecar com digitos (%s) linha %d\n",yytext, linha);
}

. {
    printf("ERRO LEXICO: Caracter invalido (%s) linha %d\n",yytext, linha);
}

\"[^\"\n]* { 
    printf("ERRO LEXICO: String mal formada (%s) linha %d\n",yytext, linha);
}

%%

int yywrap(){
    return 1;
}

int main(){
    printf("Digite o nome do arquivo para se abrir: ");
    char nome[100];
    scanf("%s", nome);

    yyin = fopen(nome, "r");
    if (yyin == NULL) {
        printf("Nao foi possivel abrir o arquivo\n");
        return 0;
    }

    yylex();

    imprime();
    return 0;
}