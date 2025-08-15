// Sua função merge (sem modificações)
void merge(int *v, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim - inicio + 1;
    p1 = inicio;
    p2 = meio + 1;
    temp = (int *)malloc(tamanho * sizeof(int));
    if (temp != NULL) {
        for (i = 0; i < tamanho; i++) {
            if (!fim1 && !fim2) {
                // Compara os elementos enquanto ambas as metades têm itens
                if (v[p1] < v[p2]) {
                    temp[i] = v[p1++];
                } else {
                    temp[i] = v[p2++];
                }
                // Verifica se uma das metades chegou ao fim
                if (p1 > meio) fim1 = 1;
                if (p2 > fim) fim2 = 1;
            } else {
                // Copia o restante da metade que não terminou
                if (!fim1) {
                    temp[i] = v[p1++];
                } else {
                    temp[i] = v[p2++];
                }
            }
        }
        // Copia do array temporário de volta para o original
        for (j = 0, k = inicio; j < tamanho; j++, k++) {
            v[k] = temp[j];
        }
    }
    free(temp);
}

// Sua função mergesort (com um pequeno ajuste para remover a dependência da biblioteca math.h)
void mergesort(int *v, int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        // Usar esta forma para calcular o meio é mais seguro contra overflow de inteiros
        meio = inicio + (fim - inicio) / 2; 
        mergesort(v, inicio, meio);
        mergesort(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArray(int* nums, int numsSize, int* returnSize) {
    // 1. Define o tamanho do array de retorno
    *returnSize = numsSize;

    // Se o array de entrada for vazio, retorna um array vazio alocado
    if (numsSize == 0) {
        return (int*)malloc(0);
    }

    // 2. Aloca memória para o novo array que será retornado
    int* result = (int*)malloc(numsSize * sizeof(int));
    if (result == NULL) { // Verifica se a alocação falhou
        *returnSize = 0;
        return NULL;
    }

    // 3. Copia os elementos do array original (nums) para o novo array (result)
    memcpy(result, nums, numsSize * sizeof(int));

    // 4. Chama o SEU algoritmo mergesort para ordenar o NOVO array
    mergesort(result, 0, numsSize - 1);

    // 5. Retorna o ponteiro para o novo array ordenado
    return result;
}