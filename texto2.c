#include <ctype.h>
#include <string.h>
#include "texto2.h"

void normaliza_palavra(char *p) {
    int i, j = 0;
    char tmp[TAMANHO];
    
    for (i = 0; p[i]; i++) {
        unsigned char c = p[i];
        if (c >= 'A' && c <= 'Z') {
            tmp[i] = c + ('a' - 'A');
        } else {
            tmp[i] = c;
        }
    }
    tmp[i] = '\0';
    
    int ini = 0, fim = strlen(tmp) - 1;
    
    #define IS_ASCII_ALPHA(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
    
    while (ini <= fim && !IS_ASCII_ALPHA(tmp[ini])) ini++;
    while (fim >= ini && !IS_ASCII_ALPHA(tmp[fim])) fim--;
    
    for (i = ini; i <= fim; i++) {
        p[j++] = tmp[i];
    }
    p[j] = '\0';
}

int palavra_valida(char *p) {
    if (p[0] == '\0') return 0;
    
    for (int i = 0; p[i]; i++) {
        unsigned char c = p[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            return 1;
        }
    }
    return 0;
}