#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice2.h"

typedef struct no {
    Entrada *e;
    struct no *prox;
} No;

static No *inicio = NULL;
static int total = 0;
static int comp_construcao = 0;
static int comp_busca = 0;

static char *duplica(const char *s) {
    if (s == NULL) return NULL;
    char *d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

void indice_init(char *tipo) {
    (void)tipo;
    inicio = NULL;
    total = comp_construcao = comp_busca = 0;
}

static Entrada *nova_entrada(char *palavra, int linha) {
    Entrada *e = malloc(sizeof(Entrada));
    if (e == NULL) return NULL;
    
    e->palavra = duplica(palavra);
    if (e->palavra == NULL) {
        free(e);
        return NULL;
    }
    
    e->ocorrencias = 1;
    e->linhas = malloc(sizeof(LinhaNo));
    if (e->linhas == NULL) {
        free(e->palavra);
        free(e);
        return NULL;
    }
    
    e->linhas->linha = linha;
    e->linhas->prox = NULL;
    total++;
    return e;
}

void indice_insere(char *palavra, int linha) {
    No *p = inicio;
    while (p) {
        comp_construcao++;
        if (strcmp(p->e->palavra, palavra) == 0) {
            LinhaNo *l = malloc(sizeof(LinhaNo));
            if (l == NULL) return;
            
            l->linha = linha;
            l->prox = p->e->linhas;
            p->e->linhas = l;
            p->e->ocorrencias++;
            return;
        }
        p = p->prox;
    }

    No *novo = malloc(sizeof(No));
    if (novo == NULL) return;
    
    novo->e = nova_entrada(palavra, linha);
    if (novo->e == NULL) {
        free(novo);
        return;
    }
    
    novo->prox = inicio;
    inicio = novo;
}

Entrada *indice_busca(char *palavra) {
    No *p = inicio;
    while (p) {
        comp_busca++;
        if (strcmp(p->e->palavra, palavra) == 0)
            return p->e;
        p = p->prox;
    }
    return NULL;
}

int indice_total_palavras() { return total; }
int indice_altura() { return -1; }
int indice_comparacoes_construcao() { return comp_construcao; }
int indice_comparacoes_busca() { return comp_busca; }
void indice_reset_comparacoes_busca() { comp_busca = 0; }