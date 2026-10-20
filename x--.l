%option yylineno
%{
    #include "syntax.tab.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "listaencadeada.c"
    #include "tabelareservadas.h"
    #include "tabelasimbolos.h"
    int linha=1;
%}

LETRA [a-zA-Z]
DIGITO [0-9]
ID {LETRA}({LETRA}|{DIGITO})*

INTEIRO {DIGITO}+
REAL {DIGITO}+"."{DIGITO}+
STRING \"[^"\n]*\"


%%

"\n" {linha++;}

{INTEIRO} {insere(strdup(yytext), "INTEIRO"); return INTEIRO;}

{REAL} {insere(strdup(yytext), "REAL");return REAL;}

{ID} {
    int token = buscaReservada(yytext);
    if (token != -1) {
        insere(strdup(yytext), "RESERVADA");
        return token;
    }
    insereSimbolo(yytext, linha);
    insere(strdup(yytext), "IDENTIFICADOR");
    return IDENTIFICADOR;
}

{STRING} {insere(strdup(yytext), "STRING");return STRING;}

 /* Operadores */

"+" {insere(strdup(yytext), "SOMA"); return SOMA;}

"-" {insere(strdup(yytext), "SUBTRACAO"); return SUBTRACAO;}

"/" {insere(strdup(yytext), "DIVISAO"); return DIVISAO;}

"*" {insere(strdup(yytext), "MULTIPLICACAO"); return MULTIPLICACAO;}

"%" {insere(strdup(yytext), "RESTO"); return RESTO;}

"=" {insere(strdup(yytext), "ATRIBUICAO"); return ATRIBUICAO;}

">"|"<"|"=="|">="|"<="|"!=" {insere(strdup(yytext), "RELACIONAL"); return RELACIONAL;}

 /* Separadores */
" " {}

"(" {insere(strdup(yytext), "ABRE_PARENTESES"); return ABRE_PARENTESES;}

")" {insere(strdup(yytext), "FECHA_PARENTESES"); return FECHA_CHAVES;}

"{" {insere(strdup(yytext), "ABRE_CHAVES"); return ABRE_CHAVES;}

"}" {insere(strdup(yytext), "FECHA_CHAVES"); return FECHA_CHAVES;}

";" {insere(strdup(yytext), "PONTO_VIRGULA"); return PONTO_VIRGULA;}


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

// int yywrap(){
//     return 1;
// }

// int main(){
//     printf("Digite o nome do arquivo para se abrir: ");
//     char nome[100];
//     scanf("%s", nome);

//     yyin = fopen(nome, "r");
//     if (yyin == NULL) {
//         printf("Nao foi possivel abrir o arquivo\n");
//         return 0;
//     }

//     yylex();

//     imprime();
//     return 0;
// }