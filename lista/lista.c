#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===================== ESTRUTURAS =====================
typedef struct {
    int cod;
    char nome[40];
    float preco;
} SDado;

typedef struct SNodo {
    SDado info;
    struct SNodo *pNext;
} SNodo;

typedef struct {
    SNodo *pFirst;
    unsigned int nTamanho;  // Informação extra na sentinela
} SLista;

// ===================== FUNÇÕES BÁSICAS =====================

// Função para criar um novo nodo
SNodo* CriarNodo(SDado dado) {
    SNodo *novoNodo = (SNodo*)malloc(sizeof(SNodo));
    if (!novoNodo) {
        printf("Erro ao alocar memória para novo nodo!\n");
        return NULL;
    }
    novoNodo->info = dado;
    novoNodo->pNext = NULL;
    return novoNodo;
}

// Função Clear - limpa todos os nodos da lista
void Clear(SLista *pLista) {
    if (!pLista) return;
    
    SNodo *pAtual = pLista->pFirst;
    SNodo *pProximo;
    
    while (pAtual != NULL) {
        pProximo = pAtual->pNext;
        free(pAtual);
        pAtual = pProximo;
    }
    
    pLista->pFirst = NULL;
    pLista->nTamanho = 0;
}

// Função Reset - inicializa/reseta a lista
void Reset(SLista *pLista) {
    if (!pLista) return;
    
    Clear(pLista);
    pLista->pFirst = NULL;
    pLista->nTamanho = 0;
}

// Função para verificar se a lista está vazia
bool Empty(SLista *pLista) {
    return (pLista == NULL || pLista->pFirst == NULL);
}

// Função para obter o tamanho da lista
unsigned int Tamanho(SLista *pLista) {
    return pLista ? pLista->nTamanho : 0;
}

// ===================== FUNÇÃO PUSH =====================
int PUSH(SLista *pLista, SDado dado, unsigned int nIndex) {
    if (!pLista) return 0;
    
    // Criar novo nodo
    SNodo *pNodo = CriarNodo(dado);
    if (!pNodo) return 0;
    
    SNodo *pAtual, *pAnterior;
    
    // Lista vazia - só pode inserir no índice 0
    if (pLista->pFirst == NULL && nIndex != 0) {
        free(pNodo);
        return 0; /* erro: nIndex inválido */
    }
    
    // Inserir como primeiro elemento (lista vazia)
    if (pLista->pFirst == NULL && nIndex == 0) {
        pLista->pFirst = pNodo;
        pLista->pFirst->pNext = NULL;
        pLista->nTamanho++;
        return 1;
    }
    
    // Inserir no início da lista (índice 0)
    if (nIndex == 0) {
        pNodo->pNext = pLista->pFirst;
        pLista->pFirst = pNodo;
        pLista->nTamanho++;
        return 1;
    }
    
    // Inserir em posição específica
    pAtual = pLista->pFirst;
    pAnterior = NULL;
    
    // Navegar até a posição desejada
    for (unsigned int nPos = 0; nPos < nIndex && pAtual != NULL; nPos++) {
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
    }
    
    // Se chegou ao final da lista, pode inserir (append)
    // Se não chegou, insere no meio
    pNodo->pNext = pAtual;  // pAtual pode ser NULL (fim da lista)
    if (pAnterior) {
        pAnterior->pNext = pNodo;
    }
    
    pLista->nTamanho++;
    return 1;
}

// Função auxiliar para inserir no final da lista
int PushFinal(SLista *pLista, SDado dado) {
    return PUSH(pLista, dado, pLista->nTamanho);
}

// Função auxiliar para inserir no início da lista
int PushInicio(SLista *pLista, SDado dado) {
    return PUSH(pLista, dado, 0);
}

// ===================== FUNÇÃO POP =====================
int POP(SLista *pLista, SDado *pDado, unsigned int nIndex) {
    if (!pLista || !pDado) return 0;
    
    SNodo *pAnterior, *pAtual;
    
    // Lista vazia
    if (pLista->pFirst == NULL) return 0; /* erro: lista vazia */
    
    // Índice inválido
    if (nIndex >= pLista->nTamanho) return 0;
    
    // Remover primeiro elemento (índice 0)
    if (nIndex == 0) {
        pAtual = pLista->pFirst;
        *pDado = pAtual->info;
        pLista->pFirst = pLista->pFirst->pNext;
        free(pAtual);
        pLista->nTamanho--;
        return 1;
    }
    
    // Remover elemento em posição específica
    pAtual = pLista->pFirst;
    pAnterior = NULL;
    
    // Navegar até a posição desejada
    for (unsigned int nPos = 0; nPos < nIndex && pAtual != NULL; nPos++) {
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
    }
    
    // Se não encontrou o nodo (não deveria acontecer se nIndex < nTamanho)
    if (!pAtual) return 0;
    
    // Copiar dados e remover nodo
    *pDado = pAtual->info;
    pAnterior->pNext = pAtual->pNext;
    free(pAtual);
    pLista->nTamanho--;
    
    return 1;
}

// Função auxiliar para remover do final da lista
int PopFinal(SLista *pLista, SDado *pDado) {
    if (pLista->nTamanho == 0) return 0;
    return POP(pLista, pDado, pLista->nTamanho - 1);
}

// Função auxiliar para remover do início da lista
int PopInicio(SLista *pLista, SDado *pDado) {
    return POP(pLista, pDado, 0);
}

// ===================== FUNÇÕES AUXILIARES =====================

// Função para buscar um elemento por código
int BuscarPorCodigo(SLista *pLista, int cod, SDado *pDado) {
    if (!pLista || !pDado) return -1;
    
    SNodo *pAtual = pLista->pFirst;
    unsigned int pos = 0;
    
    while (pAtual != NULL) {
        if (pAtual->info.cod == cod) {
            *pDado = pAtual->info;
            return pos;
        }
        pAtual = pAtual->pNext;
        pos++;
    }
    
    return -1; // Não encontrado
}

// Função para obter elemento por índice
int ObterPorIndice(SLista *pLista, unsigned int nIndex, SDado *pDado) {
    if (!pLista || !pDado || nIndex >= pLista->nTamanho) return 0;
    
    SNodo *pAtual = pLista->pFirst;
    
    for (unsigned int i = 0; i < nIndex && pAtual != NULL; i++) {
        pAtual = pAtual->pNext;
    }
    
    if (pAtual) {
        *pDado = pAtual->info;
        return 1;
    }
    
    return 0;
}

// Função para listar todos os elementos
void Listar(SLista *pLista) {
    if (!pLista) {
        printf("Lista não inicializada!\n");
        return;
    }
    
    printf("\n=== LISTANDO LISTA ENCADEADA ===\n");
    printf("Tamanho da lista: %u elementos\n", pLista->nTamanho);
    
    if (Empty(pLista)) {
        printf("Lista vazia!\n");
        return;
    }
    
    SNodo *pAtual = pLista->pFirst;
    unsigned int pos = 0;
    
    printf("Posição | Código | Nome                | Preço\n");
    printf("--------|--------|---------------------|----------\n");
    
    while (pAtual != NULL) {
        printf("   %2u   | %6d | %-19s | R$ %6.2f\n", 
               pos, pAtual->info.cod, pAtual->info.nome, pAtual->info.preco);
        pAtual = pAtual->pNext;
        pos++;
    }
}

// Função para remover por código
int RemoverPorCodigo(SLista *pLista, int cod) {
    if (!pLista) return 0;
    
    SNodo *pAtual = pLista->pFirst;
    SNodo *pAnterior = NULL;
    
    while (pAtual != NULL) {
        if (pAtual->info.cod == cod) {
            // Encontrou o elemento
            if (pAnterior == NULL) {
                // É o primeiro elemento
                pLista->pFirst = pAtual->pNext;
            } else {
                // Não é o primeiro elemento
                pAnterior->pNext = pAtual->pNext;
            }
            free(pAtual);
            pLista->nTamanho--;
            return 1;
        }
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
    }
    
    return 0; // Não encontrado
}

// ===================== PROGRAMA PRINCIPAL =====================
int main() {
    SLista lista;
    Reset(&lista);
    
    int opcao;
    SDado dado;
    unsigned int indice;
    int codigo;
    
    do {
        printf("\n=== MENU LISTA ENCADEADA ===\n");
        printf("1: Inserir no início\n");
        printf("2: Inserir no final\n");
        printf("3: Inserir em posição específica\n");
        printf("4: Remover do início\n");
        printf("5: Remover do final\n");
        printf("6: Remover de posição específica\n");
        printf("7: Remover por código\n");
        printf("8: Buscar por código\n");
        printf("9: Obter por índice\n");
        printf("10: Listar todos os elementos\n");
        printf("11: Mostrar tamanho da lista\n");
        printf("12: Limpar lista\n");
        printf("0: Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1: {
                printf("Código: ");
                scanf("%d", &dado.cod);
                printf("Nome: ");
                scanf(" %39[^\n]", dado.nome);
                printf("Preço: ");
                scanf("%f", &dado.preco);
                
                if (PushInicio(&lista, dado)) {
                    printf("Elemento inserido no início com sucesso!\n");
                } else {
                    printf("Erro ao inserir elemento!\n");
                }
                break;
            }
            
            case 2: {
                printf("Código: ");
                scanf("%d", &dado.cod);
                printf("Nome: ");
                scanf(" %39[^\n]", dado.nome);
                printf("Preço: ");
                scanf("%f", &dado.preco);
                
                if (PushFinal(&lista, dado)) {
                    printf("Elemento inserido no final com sucesso!\n");
                } else {
                    printf("Erro ao inserir elemento!\n");
                }
                break;
            }
            
            case 3: {
                printf("Código: ");
                scanf("%d", &dado.cod);
                printf("Nome: ");
                scanf(" %39[^\n]", dado.nome);
                printf("Preço: ");
                scanf("%f", &dado.preco);
                printf("Posição (0 a %u): ", lista.nTamanho);
                scanf("%u", &indice);
                
                if (PUSH(&lista, dado, indice)) {
                    printf("Elemento inserido na posição %u com sucesso!\n", indice);
                } else {
                    printf("Erro ao inserir elemento! Posição inválida.\n");
                }
                break;
            }
            
            case 4: {
                if (PopInicio(&lista, &dado)) {
                    printf("Elemento removido do início: %d - %s - R$ %.2f\n", 
                           dado.cod, dado.nome, dado.preco);
                } else {
                    printf("Lista vazia! Nenhum elemento para remover.\n");
                }
                break;
            }
            
            case 5: {
                if (PopFinal(&lista, &dado)) {
                    printf("Elemento removido do final: %d - %s - R$ %.2f\n", 
                           dado.cod, dado.nome, dado.preco);
                } else {
                    printf("Lista vazia! Nenhum elemento para remover.\n");
                }
                break;
            }
            
            case 6: {
                printf("Posição a remover (0 a %u): ", 
                       lista.nTamanho > 0 ? lista.nTamanho - 1 : 0);
                scanf("%u", &indice);
                
                if (POP(&lista, &dado, indice)) {
                    printf("Elemento removido da posição %u: %d - %s - R$ %.2f\n", 
                           indice, dado.cod, dado.nome, dado.preco);
                } else {
                    printf("Erro ao remover! Posição inválida ou lista vazia.\n");
                }
                break;
            }
            
            case 7: {
                printf("Código do elemento a remover: ");
                scanf("%d", &codigo);
                
                if (RemoverPorCodigo(&lista, codigo)) {
                    printf("Elemento com código %d removido com sucesso!\n", codigo);
                } else {
                    printf("Elemento com código %d não encontrado.\n", codigo);
                }
                break;
            }
            
            case 8: {
                printf("Código a buscar: ");
                scanf("%d", &codigo);
                
                int pos = BuscarPorCodigo(&lista, codigo, &dado);
                if (pos >= 0) {
                    printf("Elemento encontrado na posição %d:\n", pos);
                    printf("Código: %d | Nome: %s | Preço: R$ %.2f\n", 
                           dado.cod, dado.nome, dado.preco);
                } else {
                    printf("Elemento com código %d não encontrado.\n", codigo);
                }
                break;
            }
            
            case 9: {
                printf("Índice a obter (0 a %u): ", 
                       lista.nTamanho > 0 ? lista.nTamanho - 1 : 0);
                scanf("%u", &indice);
                
                if (ObterPorIndice(&lista, indice, &dado)) {
                    printf("Elemento na posição %u:\n", indice);
                    printf("Código: %d | Nome: %s | Preço: R$ %.2f\n", 
                           dado.cod, dado.nome, dado.preco);
                } else {
                    printf("Índice inválido!\n");
                }
                break;
            }
            
            case 10: {
                Listar(&lista);
                break;
            }
            
            case 11: {
                printf("Tamanho atual da lista: %u elementos\n", Tamanho(&lista));
                break;
            }
            
            case 12: {
                Clear(&lista);
                printf("Lista limpa com sucesso!\n");
                break;
            }
            
            case 0: {
                printf("Saindo do programa...\n");
                Clear(&lista); // Limpar memória antes de sair
                break;
            }
            
            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 0);
    
    return 0;
}