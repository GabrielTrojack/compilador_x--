#include "arvoresintatica.h"

AS* criaAS(char *comando, char *valorString, int valorInt) {
    AS* novo = malloc(sizeof(AS));
    novo->comando = comando;
    novo->valorString = valorString;
    novo->valorInt = valorInt;
    novo->filhos = NULL;

    return novo;
}

void insereFilhoAS(AS* pai, AS* filho) {
    No* noFilho = malloc(sizeof(No));
    noFilho->filhoAs = filho;
    noFilho->prox = NULL;

    if (pai->filhos == NULL) {
        pai->filhos = filho;
    }
    else {
        No* atual = pai->filhos;
        while(atual->prox != NULL) atual = atual->prox;

        atual->prox = noFilho;
    }
}

void freeFilhos(No* atual) {
    if (atual==NULL) return;

    freeArvore(atual->filhoAs);
    freeFilhos(atual->prox);
    free(atual);
}

void freeArvore(AS* atual) {
    if (atual==NULL) return;

    freeFilhos(atual->filhos);
    free(atual);
}