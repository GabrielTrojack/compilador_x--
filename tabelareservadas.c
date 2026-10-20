#include <stdio.h>
#include <string.h>
#include "syntax.tab.h"
#include "tabelareservadas.h"

typedef struct {
    const char *lexema;       
    int token;                
    const char *equivalente;  
    int ocorrencias;         
} EntradaReservada;

static EntradaReservada TABELA_RESERVADAS[] = {
    {"tni",     TNI,     "int"},
    {"rahc",    RAHC,    "char"},
    {"elboud",  ELBOUD,  "double"},
    {"gnirts",  GNIRTS,  "string"},
    {"niam",    NIAM,    "main"},
    {"fi",      FI,      "if"},
    {"esle",    ESLE,    "else"},
    {"elihw",   ELIHW,   "while"},
    {"od",      OD,      "do"},
    {"rof",     ROF,     "for"},
    {"tuoc",    TUOC,    "cout"},
    {"nic",     NIC,     "cin"},
    {"nruter",  NRUTER,  "return"},
    {"edulcni", EDULCNI, "include"},
};

static const int QNTD_RESERVADAS = sizeof(TABELA_RESERVADAS) / sizeof(TABELA_RESERVADAS[0]);

int buscaReservada(const char *lexema) {
    for (int i = 0; i < QNTD_RESERVADAS; i++) {
        if (strcmp(TABELA_RESERVADAS[i].lexema, lexema) == 0) {
            TABELA_RESERVADAS[i].ocorrencias++;
            return TABELA_RESERVADAS[i].token;
        }
    }
    return -1;
}

void imprimeReservadas(void) {
    printf("%-10s %-10s %-6s %s\n", "PALAVRA", "EQUIVALE", "TOKEN", "OCORRENCIAS");
    for (int i = 0; i < QNTD_RESERVADAS; i++) {
        printf("%-10s %-10s %-6d %d\n",
               TABELA_RESERVADAS[i].lexema,
               TABELA_RESERVADAS[i].equivalente,
               TABELA_RESERVADAS[i].token,
               TABELA_RESERVADAS[i].ocorrencias);
    }
}
