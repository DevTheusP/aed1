/*
Exercício 3: Escreva um programa que contenha duas variáveis inteiras. 
Leia essas variáveis do teclado. Em seguida, compare seus endereços e 
exiba o conteúdo do maior endereço.
*/

#include <stdio.h>

int main() {
    // Declaração das duas variáveis inteiras
    int numero1, numero2;
    
    // Leitura dos valores do teclado
    printf("Digite o valor para a primeira variável: ");
    scanf("%d", &numero1);
    
    printf("Digite o valor para a segunda variável: ");
    scanf("%d", &numero2);
    
    // Exibindo os valores e endereços das variáveis
    printf("\nVariável numero1 = %d, Endereço: %p\n", numero1, &numero1);
    printf("Variável numero2 = %d, Endereço: %p\n", numero2, &numero2);
    
    // Comparando os endereços e exibindo o conteúdo do maior endereço
    if (&numero1 > &numero2) {
        printf("\nO maior endereço é: %p, que contém o valor: %d\n", &numero1, numero1);
    } else {
        printf("\nO maior endereço é: %p, que contém o valor: %d\n", &numero2, numero2);
    }
    
    return 0;
}