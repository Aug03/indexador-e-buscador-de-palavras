#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "texto2.h"
#include "indice2.h"

#define MAX_LINHAS 10000
#define MAX_PALAVRA 256

char *linhas_texto[MAX_LINHAS];
int num_linhas = 0;

char *duplica(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

void carregar_arquivo(const char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "r");
    if (!arq) {
        printf("Erro ao abrir arquivo '%s'\n", nome_arquivo);
        exit(1);
    }
    
    char buffer[TAMANHO];
    num_linhas = 0;
    
    while (fgets(buffer, TAMANHO, arq) && num_linhas < MAX_LINHAS) {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        linhas_texto[num_linhas] = duplica(buffer);
        num_linhas++;
        
        char copia[TAMANHO];
        strcpy(copia, buffer);
        
        char *palavra = copia;
        while (*palavra) {
            while (*palavra && !isalpha((unsigned char)*palavra)) {
                palavra++;
            }
            
            if (!*palavra) break;
            
            char *fim = palavra;
            while (*fim && isalpha((unsigned char)*fim)) {
                fim++;
            }
            
            if (fim > palavra) {
                char temp[MAX_PALAVRA];
                int len = fim - palavra;
                if (len >= MAX_PALAVRA) len = MAX_PALAVRA - 1;
                strncpy(temp, palavra, len);
                temp[len] = '\0';
                
                normaliza_palavra(temp);
                
                if (palavra_valida(temp)) {
                    indice_insere(temp, num_linhas);
                }
                
                palavra = fim;
            }
        }
    }
    
    fclose(arq);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Uso: %s <arquivo> <lista|arvore>\n", argv[0]);
        return 1;
    }
    
    char *nome_arquivo = argv[1];
    char *tipo_indice = argv[2];
    
    if (strcmp(tipo_indice, "lista") != 0 && strcmp(tipo_indice, "arvore") != 0) {
        printf("Tipo de indice invalido. Use 'lista' ou 'arvore'.\n");
        return 1;
    }
    
    indice_init(tipo_indice);
    
    carregar_arquivo(nome_arquivo);
    
    printf("Arquivo: '%s'\n", nome_arquivo);
    printf("Tipo de indice: '%s'\n", tipo_indice);
    printf("Numero de linhas no arquivo: %d\n", num_linhas);
    printf("Total de palavras unicas indexadas: %d\n", indice_total_palavras());
    
    if (strcmp(tipo_indice, "arvore") == 0) {
        printf("Altura da arvore: %d\n", indice_altura());
    }
    
    printf("Numero de comparacoes realizadas para a construcao do indice: %d\n",
           indice_comparacoes_construcao());
    
    char comando[256];
    char palavra[256];
    
    printf("> ");
    while (fgets(comando, sizeof(comando), stdin)) {
        comando[strcspn(comando, "\n")] = '\0';
        
        if (strcmp(comando, "fim") == 0) {
            break;
        }
        
        if (strncmp(comando, "busca ", 6) == 0) {
            strcpy(palavra, comando + 6);
            
            normaliza_palavra(palavra);
            
            if (!palavra_valida(palavra)) {
                printf("Palavra invalida para busca.\n");
                printf("> ");
                continue;
            }
            
            indice_reset_comparacoes_busca();
            
            Entrada *e = indice_busca(palavra);
            
            if (e) {
                printf("Existem %d ocorrencias da palavra '%s' na(s) seguinte(s) linha(s):\n",
                       e->ocorrencias, palavra);
                
                LinhaNo *ln = e->linhas;
                while (ln) {
                    int idx = ln->linha - 1;
                    if (idx >= 0 && idx < num_linhas) {
                        printf("%05d: %s\n", ln->linha, linhas_texto[idx]);
                    }
                    ln = ln->prox;
                }
            } else {
                printf("Palavra '%s' nao encontrada.\n", palavra);
            }
            
            printf("Numero de comparacoes: %d\n", indice_comparacoes_busca());
            
        } else {
            printf("Opcao invalida!\n");
        }
        
        printf("> ");
    }
    
    for (int i = 0; i < num_linhas; i++) {
        free(linhas_texto[i]);
    }
    
    return 0;
}