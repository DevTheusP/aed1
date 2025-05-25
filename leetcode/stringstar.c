#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeStars(char* s) {
    /**
     * Remove todas as estrelas de uma string, onde cada estrela remove
     * o caractere não-estrela mais próximo à sua esquerda.
     * 
     * Estratégia: Usar a própria string como pilha, mantendo um índice
     * para a próxima posição livre.
     */
    
    int len = strlen(s);
    int top = 0; // Índice para simular o topo da pilha
    
    for (int i = 0; i < len; i++) {
        if (s[i] == '*') {
            // Remove o último caractere (decrementa o topo da pilha)
            if (top > 0) {
                top--;
            }
        } else {
            // Adiciona o caractere na posição do topo da pilha
            s[top] = s[i];
            top++;
        }
    }
    
    // Adiciona terminador nulo na posição final
    s[top] = '\0';
    
    return s;
}

// Função para testar a solução
int main() {
    // Teste 1: "leet**cod*e" -> "lecoe"
    char test1[] = "leet**cod*e";
    printf("Entrada: %s\n", test1);
    printf("Saída: %s\n\n", removeStars(test1));
    
    // Teste 2: "erase*****" -> ""
    char test2[] = "erase*****";
    printf("Entrada: %s\n", "erase*****");
    printf("Saída: '%s'\n\n", removeStars(test2));
    
    // Teste 3: "abc*def*" -> "abe"
    char test3[] = "abc*def*";
    printf("Entrada: %s\n", "abc*def*");
    printf("Saída: %s\n\n", removeStars(test3));
    
    return 0;
}
