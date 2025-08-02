#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
#define MOD 1000000007

// Tabela para armazenar as combinações C(n, k)
long long tabela_pascal[MAX_N][MAX_N];

// Função para pré-calcular combinações usando triangulo de pascal
void montar_tabela(int n) {
    for (int i = 0; i <= n; i++) {
        tabela_pascal[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            tabela_pascal[i][j] = (tabela_pascal[i - 1][j - 1] + tabela_pascal[i - 1][j]) % MOD;
        }
    }
}

long long dfs(int* nums, int numsSize) {
    if (numsSize < 3) {
        return 1;
    }

    int raiz = nums[0];
    int* menores = (int*)malloc(numsSize * sizeof(int));
    int* maiores = (int*)malloc(numsSize * sizeof(int));
    int menores_count = 0;
    int maiores_count = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < raiz) {
            menores[menores_count++] = nums[i];
        } else {
            maiores[maiores_count++] = nums[i];
        }
    }

    long long comb = tabela_pascal[menores_count + maiores_count][menores_count];
    long long left_ways = dfs(menores, menores_count);
    long long right_ways = dfs(maiores, maiores_count);

    free(menores);
    free(maiores);

    // Aplica o módulo em cada multiplicação para evitar overflow
    long long result = (comb * left_ways) % MOD;
    result = (result * right_ways) % MOD;

    return result;
}

int numOfWays(int* nums, int numsSize) {
    montar_tabela(numsSize);
    return (dfs(nums, numsSize) - 1 + MOD) % MOD;
}