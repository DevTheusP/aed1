// Função para comparar dois inteiros em ordem decrescente
int compare_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int largestInteger(int num) {
    /**
     * Encontra o maior número possível trocando dígitos de mesma paridade
     * 
     * Estratégia:
     * 1. Converter número para string de dígitos
     * 2. Separar dígitos pares e ímpares
     * 3. Ordenar cada grupo em ordem decrescente
     * 4. Reconstruir o número usando os dígitos ordenados nas posições originais
     */
    
    // Converter número para string
    char str[20];
    sprintf(str, "%d", num);
    int len = strlen(str);
    
    // Arrays para armazenar dígitos pares e ímpares
    int pares[len], impares[len];
    int count_pares = 0, count_impares = 0;
    
    // Separar dígitos por paridade
    for (int i = 0; i < len; i++) {
        int digit = str[i] - '0';
        if (digit % 2 == 0) {
            pares[count_pares++] = digit;
        } else {
            impares[count_impares++] = digit;
        }
    }
    
    // Ordenar em ordem decrescente
    qsort(pares, count_pares, sizeof(int), compare_desc);
    qsort(impares, count_impares, sizeof(int), compare_desc);
    
    // Reconstruir o número
    int resultado = 0;
    int idx_pares = 0, idx_impares = 0;
    
    for (int i = 0; i < len; i++) {
        int digit_original = str[i] - '0';
        
        if (digit_original % 2 == 0) {
            // Posição era par, usar próximo maior par disponível
            resultado = resultado * 10 + pares[idx_pares++];
        } else {
            // Posição era ímpar, usar próximo maior ímpar disponível
            resultado = resultado * 10 + impares[idx_impares++];
        }
    }
    
    return resultado;
}
