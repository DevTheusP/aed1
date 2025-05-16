/*
Exercício 1: Escreva um programa que declare um inteiro, um real e um char, e ponteiros para inteiro, 
real, e char. Associe as variáveis aos ponteiros (use &). Modifique os valores de cada variável usando
os ponteiros. Imprima os valores das variáveis antes e após a modificação.
*/


#include <stdio.h>

int main() {
    // Declaração das variáveis
    int inteiro;
    float real;
    char caractere;
    
    // Declaração dos ponteiros
    int *ptr_inteiro;
    float *ptr_real;
    char *ptr_caractere;
    
    // Inicialização das variáveis
    inteiro = 10;
    real = 3.14;
    caractere = 'A';
    
    // Associação dos ponteiros com as variáveis
    ptr_inteiro = &inteiro;
    ptr_real = &real;
    ptr_caractere = &caractere;
    
    // Impressão dos valores originais
    printf("Valores originais:\n");
    printf("Inteiro: %d\n", inteiro);
    printf("Real: %.2f\n", real);
    printf("Caractere: %c\n", caractere);
    
    // Modificação dos valores utilizando os ponteiros
    *ptr_inteiro = 20;
    *ptr_real = 9.99;
    *ptr_caractere = 'Z';
    
    // Impressão dos valores após a modificação
    printf("\nValores após a modificação usando ponteiros:\n");
    printf("Inteiro: %d\n", inteiro);
    printf("Real: %.2f\n", real);
    printf("Caractere: %c\n", caractere);
    
    return 0;
}