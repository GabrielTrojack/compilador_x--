#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

typedef struct Simbolo {
    char *nome;
    char *categoria;              /* "-" até o sintático preencher */
    char *tipo;                   /* "-" até o sintático preencher */
    int linhaPrimeiraOcorrencia;
    int ocorrencias;
    struct Simbolo *prox;
} Simbolo;

Simbolo *buscaSimbolo(const char *nome);
void insereSimbolo(const char *nome, int linha);
void atualizaSimbolo(const char *nome, const char *categoria, const char *tipo);
void imprimeTabelaSimbolos(void);

#endif