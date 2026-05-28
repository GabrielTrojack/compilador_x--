/*Definiçoes*/

%{
    #include <stdio.h>
%}

RESERVADA ("fi"|"rof"|"elihw"|"esle"|"tuoc"|"tni"|"rahc"|"elboud"|"od"|"niam"|"("|")"|"{"|"}"|";"|"%"|"="|">"|"<"|"+"|"-")
INTEIRO ("+"|"-")?{DIGITO}+
ID {LETRA}({LETRA}|{DIGITO})
NUMERO {DIGITO}+
LETRA [a-zA-Z]
DIGITO [0-9]

%%

{DIGITO}  {printf("digito encontrado %s\n",yytext);}
{LETRA}  {printf("letra encontrado %s\n",yytext);}
{NUMERO}  {printf("numero encontrado\n");}
{ID} {printf("Id encontrado\n");}
{RESERVADA} {printf("palavra RESERVADA encontrado\n");}

%%

int yywrap(){
    return 1;
}

int main(){
    yyin = fopen("arquivo.txt", "r");
    yylex();
    return 0;
}