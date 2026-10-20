#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelasimbolos.h"

static Simbolo *inicio = NULL; 
static Simbolo *fim = NULL;

static char *copiaTexto(const char *texto) {
    char *copia = strdup(texto);
    if (copia == NULL) {
        perror("Erro ao alocar memoria na tabela de simbolos");
        exit(EXIT_FAILURE);
    }
    return copia;
}

Simbolo *buscaSimbolo(const char *nome) {
    for (Simbolo *atual = inicio; atual != NULL; atual = atual->prox) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
    }
    return NULL;
}

void insereSimbolo(const char *nome, int linha) {
    Simbolo *existente = buscaSimbolo(nome);
    if (existente != NULL) {
        existente->ocorrencias++;
        return;
    }

    Simbolo *novo = malloc(sizeof(Simbolo));
    if (novo == NULL) {
        perror("Erro ao alocar memoria na tabela de simbolos");
        exit(EXIT_FAILURE);
    }
    novo->nome = copiaTexto(nome);
    novo->categoria = copiaTexto("-");
    novo->tipo = copiaTexto("-");
    novo->linhaPrimeiraOcorrencia = linha;
    novo->ocorrencias = 1;
    novo->prox = NULL;

    if (inicio == NULL) {
        inicio = novo;
    } else {
        fim->prox = novo;
    }
    fim = novo;
}

void atualizaSimbolo(const char *nome, const char *categoria, const char *tipo) {
    Simbolo *simbolo = buscaSimbolo(nome);
    if (simbolo == NULL) {
        return;
    }
    free(simbolo->categoria);
    free(simbolo->tipo);
    simbolo->categoria = copiaTexto(categoria);
    simbolo->tipo = copiaTexto(tipo);
}

void imprimeTabelaSimbolos(void) {
    if (inicio == NULL) {
        printf("(tabela de simbolos vazia)\n");
        return;
    }

    printf("%-16s %-10s %-8s %-14s %s\n",
           "NOME", "CATEGORIA", "TIPO", "1a OCORRENCIA", "OCORRENCIAS");
    for (Simbolo *atual = inicio; atual != NULL; atual = atual->prox) {
        printf("%-16s %-10s %-8s linha %-8d %d\n",
               atual->nome, atual->categoria, atual->tipo,
               atual->linhaPrimeiraOcorrencia, atual->ocorrencias);
    }
}