%option yylineno
%{
    #include <stdio.h>
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

{RESERVADA} {printf("Palavra_Reservada\n");}

{INTEIRO} {printf("Numero_Inteiro %s\n",yytext);}

{REAL} {printf("Numero_Real %s\n",yytext);}

{ID} {printf("Identificador\n");}

{STRING} {printf("String %s\n", yytext);}

 /* Operadores */

"+" {printf("Token de soma\n");}

"-" {printf("Token de subtracao\n");}

"/" {printf("Token de divisao\n");}

"*" {printf("Token de multiplicacao\n");}

"%" {printf("Token de resto\n");}

"=" {printf("Token de atribuicao\n");}

">"|"<"|"=="|">="|"<="|"!=" {printf("Token relacional\n");}

 /* Separadores */
" " {}

"(" {printf("Abre_Parentesis\n");}

")" {printf("Fecha_Parentesis\n");}

"{" {printf("Abre_Chaves\n");}

"}" {printf("Fecha_Chaves\n");}

";" {printf("Ponto_Virgula\n");}


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
    yyin = fopen("fonte2.txt", "r");
    yylex();
    return 0;
}