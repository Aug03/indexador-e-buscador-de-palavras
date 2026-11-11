#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice2.h"

typedef struct no {
    Entrada *e;
    struct no *esq, *dir;
} No;

static No *raiz = NULL;
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
    raiz = NULL;
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

static No *insere_rec(No *r, char *palavra, int linha) {
    if (!r) {
        No *n = malloc(sizeof(No));
        if (n == NULL) return NULL;
        
        n->e = nova_entrada(palavra, linha);
        if (n->e == NULL) {
            free(n);
            return NULL;
        }
        
        n->esq = n->dir = NULL;
        return n;
    }

    comp_construcao++;
    int c = strcmp(palavra, r->e->palavra);

    if (c == 0) {
        LinhaNo *l = malloc(sizeof(LinhaNo));
        if (l == NULL) return r;
        
        l->linha = linha;
        l->prox = r->e->linhas;
        r->e->linhas = l;
        r->e->ocorrencias++;
    } else if (c < 0)
        r->esq = insere_rec(r->esq, palavra, linha);
    else
        r->dir = insere_rec(r->dir, palavra, linha);

    return r;
}

void indice_insere(char *palavra, int linha) {
    raiz = insere_rec(raiz, palavra, linha);
}

Entrada *indice_busca(char *palavra) {
    No *r = raiz;
    while (r) {
        comp_busca++;
        int c = strcmp(palavra, r->e->palavra);
        if (c == 0) return r->e;
        if (c < 0) r = r->esq;
        else r = r->dir;
    }
    return NULL;
}

static int altura(No *r) {
    if (!r) return -1;
    int e = altura(r->esq);
    int d = altura(r->dir);
    return 1 + (e > d ? e : d);
}

int indice_altura() { return altura(raiz); }
int indice_total_palavras() { return total; }
int indice_comparacoes_construcao() { return comp_construcao; }
int indice_comparacoes_busca() { return comp_busca; }
void indice_reset_comparacoes_busca() { comp_busca = 0; }