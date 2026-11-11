#ifndef INDICE_H
#define INDICE_H

typedef struct linha_no {
    int linha;
    struct linha_no *prox;
} LinhaNo;

typedef struct entrada {
    char *palavra;
    int ocorrencias;
    LinhaNo *linhas;
} Entrada;

void indice_init(char *tipo);
void indice_insere(char *palavra, int linha);
Entrada *indice_busca(char *palavra);
int indice_total_palavras();
int indice_altura();
int indice_comparacoes_construcao();
int indice_comparacoes_busca();
void indice_reset_comparacoes_busca();

#endif