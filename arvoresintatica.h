#ifndef ARVORE_SINTATICA_H
#define ARVORE_SINTATICA_H

#include "stdio.h"

typedef struct AS{
    char *comando;
    char *valorString;
    int valorInt;
    No* filhos;
} AS;

typedef struct No {
    AS* filhoAs;
    No* prox;
} No;

AS* raiz;

AS* criaAS(char *comando, char *valorString, int valorInt);
void insereFilhoAS(AS* pai, AS* filho);
void freeArvore(AS* atual);
void freeFilhos(No* atual);

#endif