#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char* s) {
    
    if (s == NULL || *s == '\0') {
        return 0;
    }
    int visto[128] = {0};
    
    int max_length = 0;
    int inicio = 0;
    int i = 0;
    
    while (s[i] != '\0') {
        char c = s[i];
        
        
        if (visto[(int)c]) {
            
            while (s[inicio] != c) {
                visto[(int)s[inicio]] = 0;
                inicio++;
            }
            
            inicio++;
        } else {
            
            visto[(int)c] = 1;
            
            
            int comprimento_atual = i - inicio + 1;
            if (comprimento_atual > max_length) {
                max_length = comprimento_atual;
            }
        }
        
        i++;
    }
    
    return max_length;
}

// Função auxiliar para encontrar e imprimir a substring mais longa
void encontrarEImprimirSubstring(char* s) {
    if (s == NULL || *s == '\0') {
        printf("String vazia\n");
        return;
    }
    
    int visto[128] = {0};
    int inicio = 0;
    int melhor_inicio = 0;
    int melhor_comprimento = 0;
    int i = 0;
    
    while (s[i] != '\0') {
        char c = s[i];
        
        if (visto[(int)c]) {
            while (s[inicio] != c) {
                visto[(int)s[inicio]] = 0;
                inicio++;
            }
            inicio++;
        } else {
            visto[(int)c] = 1;
            
            int comprimento_atual = i - inicio + 1;
            if (comprimento_atual > melhor_comprimento) {
                melhor_comprimento = comprimento_atual;
                melhor_inicio = inicio;
            }
        }
        
        i++;
    }
    
    
    printf("Substring mais longa: \"");
    for (i = 0; i < melhor_comprimento; i++) {
        printf("%c", s[melhor_inicio + i]);
    }
    printf("\"\n");
}

int main() {
    char* exemplos[] = {
        "abcabcbb",
        "bbbbb",
        "pwwkew",
        "aab",
        "",
        "au",
        "dvdf",
        "anviaj"
    };
    
    int num_exemplos = sizeof(exemplos) / sizeof(exemplos[0]);
    
    for (int i = 0; i < num_exemplos; i++) {
        int resultado = lengthOfLongestSubstring(exemplos[i]);
        printf("Exemplo %d:\n", i + 1);
        printf("String: \"%s\"\n", exemplos[i]);
        printf("Comprimento da maior substring sem repetição: %d\n", resultado);
        encontrarEImprimirSubstring(exemplos[i]);
        printf("\n");
    }
    
    
    return 0;
}