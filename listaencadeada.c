#include "listaencadeada.h"

void insere(char *lex, char *tipo) {
    No* atual = cabeca;

    if (atual==NULL) {
        cabeca = (No*) malloc(sizeof(No));
        cabeca->lexema = lex;
        cabeca->tipo = tipo;
        cabeca->prox = NULL;
    }
    else {
        while(atual->prox != NULL) {
            atual = atual->prox;
        }

        No* novo = (No*) malloc(sizeof(No));
        novo->lexema = lex;
        novo->tipo = tipo;
        novo->prox = NULL;
        atual->prox = novo;
    }
}

void imprime() {
    No* atual = cabeca;
    while(atual != NULL) {
        printf("TOKEN: %s | LEXEMA: %s\n", atual->tipo, atual->lexema);
        atual = atual->prox;
    }
}