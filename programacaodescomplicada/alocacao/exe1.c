/*
Programa que:
(a) Aloca dinamicamente um array de 5 números inteiros
(b) Pede para o usuário digitar os 5 números no espaço alocado
(c) Mostra na tela os 5 números
(d) Libera a memória alocada
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declaração do ponteiro para o array
    int *numeros;
    int i;
    
    // (a) Alocação dinâmica de memória para um array de 5 inteiros
    numeros = (int *) malloc(5 * sizeof(int));
    
    // Verificação se a alocação foi bem-sucedida
    if (numeros == NULL) {
        printf("Erro: Memória insuficiente!\n");
        return 1; // Saída com código de erro
    }
    
    // (b) Leitura dos números informados pelo usuário
    printf("Digite 5 números inteiros:\n");
    for (i = 0; i < 5; i++) {
        printf("Número %d: ", i+1);
        scanf("%d", &numeros[i]);
    }
    
    // (c) Exibição dos números digitados
    printf("\nOs números digitados foram:\n");
    for (i = 0; i < 5; i++) {
        printf("numeros[%d] = %d\n", i, numeros[i]);
    }
    
    // (d) Liberação da memória alocada
    free(numeros);
    printf("\nMemória liberada com sucesso!\n");
    
    return 0;
}