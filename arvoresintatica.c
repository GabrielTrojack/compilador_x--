#include <stdio.h>
#include <stdlib.h>
#include "arvoresintatica.h"

AS* criaAS(char *comando, char *valorString, int valorInt) {
    AS* novo = malloc(sizeof(AS));

    if (novo == NULL) {
        perror("Erro ao alocar memoria para AS");
        exit(EXIT_FAILURE);
    }

    novo->comando = comando;
    novo->valorString = valorString;
    novo->valorInt = valorInt;
    novo->filhos = NULL;
    novo->qntdFilhos = 0;

    return novo;
}

void insereFilhoAS(AS* pai, AS* filho) {
    if (pai == NULL || filho == NULL) return;

    No* noFilho = malloc(sizeof(No));

    if (noFilho == NULL) {
        perror("Erro ao alocar memoria para No");
        exit(EXIT_FAILURE);
    }

    noFilho->filhoAs = filho;
    noFilho->prox = NULL;

    if (pai->filhos == NULL) {
        pai->filhos = noFilho;
    } else {
        No* atual = pai->filhos;

        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        atual->prox = noFilho;
    }

    pai->qntdFilhos++;
}

void insereFilhoNoAnterior(FilhosNoAnterior **anteriores, int atual) {
    if (anteriores == NULL) return;

    FilhosNoAnterior *novo = malloc(sizeof(FilhosNoAnterior));

    if (novo == NULL) {
        perror("Erro ao alocar memoria para FilhosNoAnterior");
        exit(EXIT_FAILURE);
    }

    novo->aindaTem = atual;
    novo->prox = NULL;

    if (*anteriores == NULL) {
        *anteriores = novo;
    } else {
        FilhosNoAnterior *aux = *anteriores;

        while (aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = novo;
    }
}

void removeUltimoNoAnterior(FilhosNoAnterior **anteriores) {
    if (anteriores == NULL || *anteriores == NULL) return;

    FilhosNoAnterior *aux = *anteriores;

    if (aux->prox == NULL) {
        free(aux);
        *anteriores = NULL;
        return;
    }

    while (aux->prox->prox != NULL) {
        aux = aux->prox;
    }

    free(aux->prox);
    aux->prox = NULL;
}

void imprimeAS(AS* atual, FilhosNoAnterior **niveisAnteriores, FILE *out) {
    if (atual == NULL || out == NULL || niveisAnteriores == NULL) {
        return;
    }

    FilhosNoAnterior *aux = *niveisAnteriores;

    while (aux != NULL && aux->prox!=NULL) {
        if (aux->aindaTem > 1) {
            fputs("|  ", out);
        } else {
            fputs("   ", out);
        }

        aux = aux->prox;
    }

    if (atual->comando != NULL) {
        if (niveisAnteriores!=NULL && *niveisAnteriores!=NULL) fputs("|--", out);
        fputs(atual->comando, out);
    } 

    fputc('\n', out);

    No* aux2 = atual->filhos;

    for (int i = 0; i < atual->qntdFilhos && aux2 != NULL;
         i++, aux2 = aux2->prox) {

        insereFilhoNoAnterior(
            niveisAnteriores,
            atual->qntdFilhos - i
        );

        imprimeAS(aux2->filhoAs, niveisAnteriores, out);

        removeUltimoNoAnterior(niveisAnteriores);
    }
}

void freeFilhos(No* atual) {
    if (atual == NULL) return;

    freeArvore(atual->filhoAs);
    freeFilhos(atual->prox);
    free(atual);
}

void freeArvore(AS* atual) {
    if (atual == NULL) return;

    freeFilhos(atual->filhos);
    free(atual);
}

void debugTest() {
    AS *programa = criaAS("programa", NULL, 0);

    AS *exp1 = criaAS("exp", NULL, 0);
    AS *tipo1 = criaAS("tipo", NULL, 0);
    AS *id1 = criaAS("id", NULL, 0);
    AS *attr1 = criaAS("attr", NULL, 0);

    AS *exp3 = criaAS("exp", NULL, 0);
    AS *tipo3 = criaAS("tipo", NULL, 0);
    AS *id3 = criaAS("id", NULL, 0);
    AS *attr3 = criaAS("attr", NULL, 0);
    AS *id4 = criaAS("id", NULL, 0);

    AS *exp2 = criaAS("exp", NULL, 0);
    AS *tipo2 = criaAS("tipo", NULL, 0);
    AS *id5 = criaAS("id", NULL, 0);
    AS *attr2 = criaAS("attr", NULL, 0);
    AS *id6 = criaAS("id", NULL, 0);

    insereFilhoAS(programa, exp1);
    insereFilhoAS(exp1, tipo1);
    insereFilhoAS(exp1, id1);
    insereFilhoAS(exp1, attr1);
    insereFilhoAS(exp1, exp3);

    insereFilhoAS(exp3, tipo3);
    insereFilhoAS(exp3, id3);
    insereFilhoAS(exp3, attr3);
    insereFilhoAS(exp3, id4);

    insereFilhoAS(programa, exp2);
    insereFilhoAS(exp2, tipo2);
    insereFilhoAS(exp2, id5);
    insereFilhoAS(exp2, attr2);
    insereFilhoAS(exp2, id6);

    FILE *out = fopen("arvore.txt", "w");
    FilhosNoAnterior *niveisAnteriores = NULL;
    imprimeAS(programa, &niveisAnteriores, out);
    fclose(out);

    freeArvore(programa);
}