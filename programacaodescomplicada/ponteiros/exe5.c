/*
Exercício 5: Faça um programa que leia dois valores inteiros e chame uma função que 
receba estes 2 valores de entrada e retorne o maior valor na primeira variável e o 
menor valor na segunda variável. Escreva o conteúdo das 2 variáveis na tela.
*/

#include <stdio.h>

// Protótipo da função
void ordena(int *a, int *b);

int main() {
    // Declaração das variáveis
    int num1, num2;
    
    // Leitura dos valores do teclado
    printf("Digite o primeiro valor: ");
    scanf("%d", &num1);
    
    printf("Digite o segundo valor: ");
    scanf("%d", &num2);
    
    // Exibindo os valores antes da ordenação
    printf("\nAntes da ordenação:\n");
    printf("Primeiro número = %d\n", num1);
    printf("Segundo número = %d\n", num2);
    
    // Chamada da função que ordena os valores
    ordena(&num1, &num2);
    
    // Exibindo os valores após a ordenação
    printf("\nApós a ordenação:\n");
    printf("Primeiro número (maior) = %d\n", num1);
    printf("Segundo número (menor) = %d\n", num2);
    
    return 0;
}

// Implementação da função que ordena os valores
void ordena(int *a, int *b) {
    // Se o valor apontado por b for maior que o valor apontado por a
    if (*b > *a) {
        // Realiza a troca
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    // Se a já for maior ou igual a b, não é necessário fazer nada
}