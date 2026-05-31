#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
        struct No* prox;
        char *lexema;
        char *tipo;
    } No;

No* cabeca;

void insere(char *lex, char *tipo);
void imprime();

#endif