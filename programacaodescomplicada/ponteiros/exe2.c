/*
Exercício 2: Escreva um programa que contenha duas variáveis inteiras. 
Compare seus endereços e exiba o maior endereço.
*/

#include <stdio.h>

int main() {
    // Declaração das duas variáveis inteiras
    int numero1, numero2;
    
    // Obtendo os endereços das variáveis
    printf("Endereço da variável numero1: %p\n", &numero1);
    printf("Endereço da variável numero2: %p\n", &numero2);
    
    // Comparando os endereços e exibindo o maior
    if (&numero1 > &numero2) {
        printf("O maior endereço é da variável numero1: %p\n", &numero1);
    } else {
        printf("O maior endereço é da variável numero2: %p\n", &numero2);
    }
    
    return 0;
}