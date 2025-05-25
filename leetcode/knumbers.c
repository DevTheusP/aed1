#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int minimumSum(int n, int k) {
    /**
     * Encontra a soma mínima de um array k-avoiding de tamanho n
     * 
     * Estratégia:
     * 1. Usar os menores números positivos possíveis
     * 2. Para cada número x, verificar se k-x já foi usado
     * 3. Se k-x já foi usado, pular x (para evitar soma = k)
     * 4. Continuar até ter n elementos
     */
    
    // Array para marcar números já usados (otimização para k pequeno)
    bool usado[k + 1000]; // Buffer extra para números maiores que k
    for (int i = 0; i <= k + 999; i++) {
        usado[i] = false;
    }
    
    int soma = 0;
    int contador = 0;
    int numero_atual = 1;
    
    while (contador < n) {
        int complemento = k - numero_atual;
        
        // Verificar se podemos usar numero_atual
        bool pode_usar = true;
        
        // Se o complemento é positivo e já foi usado, não podemos usar numero_atual
        if (complemento > 0 && complemento <= k + 999 && usado[complemento]) {
            pode_usar = false;
        }
        
        if (pode_usar) {
            soma += numero_atual;
            if (numero_atual <= k + 999) {
                usado[numero_atual] = true;
            }
            contador++;
        }
        
        numero_atual++;
    }
    
    return soma;
}

// Versão otimizada sem array auxiliar
int minimumSumOptimized(int n, int k) {
    /**
     * Versão otimizada baseada na observação matemática:
     * 
     * Se k é ímpar ou k/2 não está na primeira metade:
     * - Podemos usar números 1, 2, ..., n diretamente
     * 
     * Se k é par e k/2 está na primeira metade:
     * - Usamos 1, 2, ..., k/2-1, k/2+1, ..., até completar n elementos
     */
    
    if (k > 2 * n) {
        // k é muito grande, podemos usar 1, 2, ..., n
        return n * (n + 1) / 2;
    }
    
    // Caso geral: usar estratégia greedy
    int soma = 0;
    int contador = 0;
    int numero = 1;
    
    while (contador < n) {
        // Verificar se numero + seu complemento = k
        // Se sim, e se o complemento ainda pode aparecer, pular numero
        
        bool deve_pular = false;
        int complemento = k - numero;
        
        // Se complemento > numero, significa que ainda não foi considerado
        // Neste caso, devemos escolher entre numero e complemento
        // Escolhemos o menor (numero) e pulamos o maior (complemento)
        if (complemento > numero && complemento <= numero + (n - contador)) {
            // O complemento ainda pode aparecer nos próximos números
            // Então pulamos o número atual para evitar o par
            deve_pular = true;
        }
        
        if (!deve_pular) {
            soma += numero;
            contador++;
        }
        
        numero++;
    }
    
    return soma;
}

// Versão mais simples e direta
int minimumSumCorrect(int n, int k) {
    /**
     * Versão correta:
     * Para minimizar a soma, queremos usar os menores números possíveis.
     * Estratégia: usar números 1, 2, 3, ... mas pular aqueles que formam pares que somam k
     */
    
    int soma = 0;
    int count = 0;
    int num = 1;
    
    // Set para rastrear números já usados (simulado com array)
    bool usado[2001] = {false}; // Assumindo que números não passam de 2000
    
    while (count < n) {
        int complemento = k - num;
        
        // Se o complemento já foi usado, não podemos usar num
        if (complemento > 0 && complemento < 2001 && usado[complemento]) {
            // Pular este número
        } else {
            // Podemos usar este número
            soma += num;
            usado[num] = true;
            count++;
        }
        
        num++;
    }
    
    return soma;
}

// Função para testar e comparar as implementações
void testar_solucao(int n, int k) {
    printf("n=%d, k=%d:\n", n, k);
    printf("  Resultado correto: %d\n", minimumSumCorrect(n, k));
    printf("\n");
}

int main() {
    // Teste 1: n=5, k=4 -> 18
    testar_solucao(5, 4);
    
    // Teste 2: n=2, k=6 -> 3  
    testar_solucao(2, 6);
    
    // Teste 3: n=3, k=5 -> 6
    testar_solucao(3, 5);
    
    // Teste 4: n=4, k=6 -> 10
    testar_solucao(4, 6);
    
    return 0;
}

/**
 * EXPLICAÇÃO DETALHADA:
 * 
 * EXEMPLO 1: n=5, k=4
 * Processo:
 * - num=1: complemento=3, não usado ainda → usar 1, soma=1
 * - num=2: complemento=2, é o próprio número → usar 2, soma=3
 * - num=3: complemento=1, já foi usado → pular
 * - num=4: complemento=0, inválido → usar 4, soma=7
 * - num=5: complemento=-1, inválido → usar 5, soma=12
 * - num=6: complemento=-2, inválido → usar 6, soma=18
 * Array usado: [1, 2, 4, 5, 6], soma = 18 ✓
 * 
 * EXEMPLO 2: n=2, k=6  
 * Processo:
 * - num=1: complemento=5, não usado ainda → usar 1, soma=1
 * - num=2: complemento=4, não usado ainda → usar 2, soma=3
 * Array usado: [1, 2], soma = 3 ✓
 * 
 * LÓGICA PRINCIPAL:
 * - Queremos usar os menores números possíveis: 1, 2, 3, 4, ...
 * - Para cada número x, verificamos se k-x já foi usado
 * - Se k-x já foi usado, não podemos usar x (pois x + (k-x) = k)
 * - Caso contrário, podemos usar x
 * 
 * CASOS ESPECIAIS:
 * - Se k é par e x = k/2, então x + x = k, então só podemos usar um x = k/2
 * - Se k é ímpar, não há problema com x + x = k
 * 
 * COMPLEXIDADE:
 * - Tempo: O(n + k) no pior caso
 * - Espaço: O(k) para o array de controle
 */