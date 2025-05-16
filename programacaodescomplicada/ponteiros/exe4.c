/*
Exercício 4: Faça um programa que leia 2 valores inteiros e chame uma função que 
receba estas 2 variáveis e troque o seu conteúdo, ou seja, esta função é chamada 
passando duas variáveis A e B por exemplo e, após a execução da função, A conterá 
o valor de B e B terá o valor de A.
*/

#include <stdio.h>

// Protótipo da função
void troca(int *a, int *b);

int main() {
    // Declaração das variáveis
    int A, B;
    
    // Leitura dos valores do teclado
    printf("Digite o valor para A: ");
    scanf("%d", &A);
    
    printf("Digite o valor para B: ");
    scanf("%d", &B);
    
    // Exibindo os valores antes da troca
    printf("\nAntes da troca:\n");
    printf("A = %d\n", A);
    printf("B = %d\n", B);
    
    // Chamada da função de troca, passando os endereços de A e B
    troca(&A, &B);
    
    // Exibindo os valores após a troca
    printf("\nApós a troca:\n");
    printf("A = %d\n", A);
    printf("B = %d\n", B);
    
    return 0;
}

// Implementação da função de troca
void troca(int *a, int *b) {
    int temp;
    
    // Armazena temporariamente o valor apontado por a
    temp = *a;
    
    // Substitui o valor apontado por a pelo valor apontado por b
    *a = *b;
    
    // Substitui o valor apontado por b pelo valor temporário
    *b = temp;
}