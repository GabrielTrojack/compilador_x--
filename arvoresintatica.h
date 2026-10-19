#ifndef ARVORE_SINTATICA_H
#define ARVORE_SINTATICA_H

#include "stdio.h"
#include "stdlib.h"

typedef struct AS{
    char *comando;
    char *valorString;
    int valorInt;
    int qntdFilhos;
    struct No* filhos;
} AS;

typedef struct No {
    AS* filhoAs;
    struct No* prox;
} No;

typedef struct FilhosNoAnterior {
    int aindaTem;
    struct FilhosNoAnterior *prox;
} FilhosNoAnterior;

extern AS* raiz;

AS* criaAS(char *comando, char *valorString, int valorInt);
void imprimeAS(AS* atual, FilhosNoAnterior** niveisAnteriores, FILE *out);
void insereFilhoNoAnterior(FilhosNoAnterior **anteriores, int atual);
void removeUltimoNoAnterior(FilhosNoAnterior **anteriores);
void insereFilhoAS(AS* pai, AS* filho);
void freeArvore(AS* atual);
void freeFilhos(No* atual);
void debugTest();

#endif