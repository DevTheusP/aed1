/*
Programa que:
1. Lê do usuário o tamanho de um vetor
2. Faz a alocação dinâmica de memória para o vetor
3. Lê os valores do vetor fornecidos pelo usuário
4. Imprime o vetor lido
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int *vetor;  // Ponteiro para o vetor
    int tamanho; // Tamanho do vetor
    int i;       // Variável de controle para loops
    
    // Lendo o tamanho do vetor
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    
    // Verificando se o tamanho é válido
    if (tamanho <= 0) {
        printf("Erro: Tamanho inválido! O tamanho deve ser maior que zero.\n");
        return 1;
    }
    
    // Alocação dinâmica de memória para o vetor
    vetor = (int *) malloc(tamanho * sizeof(int));
    
    // Verificando se a alocação foi bem-sucedida
    if (vetor == NULL) {
        printf("Erro: Memória insuficiente para alocação!\n");
        return 1;
    }
    
    // Lendo os valores do vetor
    printf("\nDigite os %d valores do vetor:\n", tamanho);
    for (i = 0; i < tamanho; i++) {
        printf("vetor[%d]: ", i);
        scanf("%d", &vetor[i]);
    }
    
    // Imprimindo o vetor lido
    printf("\nVetor lido:\n");
    for (i = 0; i < tamanho; i++) {
        printf("vetor[%d] = %d\n", i, vetor[i]);
    }
    
    // Liberando a memória alocada
    free(vetor);
    printf("\nMemória liberada com sucesso!\n");
    
    return 0;
}