#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== ESTRUTURA PRODUTO =====
typedef struct {
    int cod;
    char nome[40];
    float preco;
} SProduto;

// ===== FILA (FIFO) =====
typedef struct STipoFila {
    SProduto info;
    struct STipoFila *pNext;
} STipoFila;

typedef struct {
    STipoFila *pFirst;
    STipoFila *pLast;
} SFila;

// Funções da Fila
SFila* RESET_FILA(SFila *pOldFila);
void CLEAR_FILA(SFila *pFila);
void PUSH_FILA(SFila *pFila, SProduto *pProd);
int POP_FILA(SFila *pFila, SProduto *pProd);
void IMPRIME_FILA(SFila *pFila);

// ===== LISTA LIGADA =====
typedef struct {
    int info;
} SInfo;

typedef struct SNodo {
    SInfo dado;
    struct SNodo *pNext;
} SNodo;

typedef struct {
    SNodo *pFirst;
} SLista;

// Funções da Lista
SLista* RESET_LISTA(SLista *pOldLista);
void CLEAR_LISTA(SLista *pLista);
void INSERT_LISTA(SLista *pLista, SInfo info);
int REMOVE_LISTA(SLista *pLista, int info);
void IMPRIME_LISTA(SLista *pLista);

// ===== LISTA DUPLAMENTE LIGADA =====
typedef struct SNodoDuplo {
    SInfo dado;
    struct SNodoDuplo *pNext;
    struct SNodoDuplo *pPrevious;
} SNodoDuplo;

typedef struct {
    unsigned int nCount;
    SNodoDuplo *pFirst;
    SNodoDuplo *pLast;
} SListaDupla;

// Funções da Lista Dupla
SListaDupla* RESET_LISTA_DUPLA(SListaDupla *pOldLista);
void CLEAR_LISTA_DUPLA(SListaDupla *pLista);
void INSERT_LISTA_DUPLA(SListaDupla *pLista, SInfo info);
int REMOVE_LISTA_DUPLA(SListaDupla *pLista, int info);
void IMPRIME_LISTA_DUPLA(SListaDupla *pLista);

// ===== FILA DE PRIORIDADE (HEAP) =====
#define MAX_HEAP 100

typedef struct {
    SProduto elementos[MAX_HEAP];
    int tamanho;
} SHeap;

// Funções do Heap
SHeap* RESET_HEAP(SHeap *pOldHeap);
void PUSH_HEAP(SHeap *pHeap, SProduto produto);
int POP_HEAP(SHeap *pHeap, SProduto *pProd);
void HEAPIFY_UP(SHeap *pHeap, int indice);
void HEAPIFY_DOWN(SHeap *pHeap, int indice);
void IMPRIME_HEAP(SHeap *pHeap);

// ===== IMPLEMENTAÇÃO DAS FUNÇÕES =====

// --- FILA (FIFO) ---
SFila* RESET_FILA(SFila *pOldFila) {
    if (pOldFila)
        CLEAR_FILA(pOldFila);
    
    SFila *pFila = (SFila*)malloc(sizeof(SFila));
    pFila->pFirst = NULL;
    pFila->pLast = NULL;
    
    return pFila;
}

void CLEAR_FILA(SFila *pFila) {
    SProduto temp;
    while (pFila->pFirst != NULL) {
        POP_FILA(pFila, &temp);
    }
}

void PUSH_FILA(SFila *pFila, SProduto *pProd) {
    STipoFila *pNovo = (STipoFila*)malloc(sizeof(STipoFila));
    pNovo->info = *pProd;
    pNovo->pNext = NULL;
    
    if (pFila->pLast != NULL)
        pFila->pLast->pNext = pNovo;
    else
        pFila->pFirst = pNovo;
    
    pFila->pLast = pNovo;
}

int POP_FILA(SFila *pFila, SProduto *pProd) {
    if (pFila->pFirst == NULL) {
        puts("Fila Vazia!");
        return 0;
    }
    
    STipoFila *pNodo = pFila->pFirst;
    *pProd = pFila->pFirst->info;
    pFila->pFirst = pFila->pFirst->pNext;
    
    if (pFila->pFirst == NULL)
        pFila->pLast = NULL;
    
    free(pNodo);
    return 1;
}

void IMPRIME_FILA(SFila *pFila) {
    if (pFila->pFirst == NULL) {
        puts("Fila Vazia!");
        return;
    }
    
    STipoFila *pNodo;
    printf("FILA: ");
    for (pNodo = pFila->pFirst; pNodo != NULL; pNodo = pNodo->pNext) {
        printf("[%s(%d)] ", pNodo->info.nome, pNodo->info.cod);
    }
    printf("\n");
}

// --- LISTA LIGADA ---
SLista* RESET_LISTA(SLista *pOldLista) {
    if (pOldLista)
        CLEAR_LISTA(pOldLista);
    
    SLista *pLista = (SLista*)malloc(sizeof(SLista));
    pLista->pFirst = NULL;
    
    return pLista;
}

void CLEAR_LISTA(SLista *pLista) {
    SNodo *pAtual = pLista->pFirst;
    while (pAtual != NULL) {
        SNodo *pTemp = pAtual;
        pAtual = pAtual->pNext;
        free(pTemp);
    }
    pLista->pFirst = NULL;
}

void INSERT_LISTA(SLista *pLista, SInfo info) {
    SNodo *pNovo = (SNodo*)malloc(sizeof(SNodo));
    pNovo->dado = info;
    pNovo->pNext = pLista->pFirst;
    pLista->pFirst = pNovo;
}

int REMOVE_LISTA(SLista *pLista, int info) {
    SNodo *pAtual = pLista->pFirst;
    SNodo *pAnterior = NULL;
    
    while (pAtual != NULL && pAtual->dado.info != info) {
        pAnterior = pAtual;
        pAtual = pAtual->pNext;
    }
    
    if (pAtual == NULL)
        return 0; // Não encontrado
    
    if (pAnterior == NULL)
        pLista->pFirst = pAtual->pNext;
    else
        pAnterior->pNext = pAtual->pNext;
    
    free(pAtual);
    return 1;
}

void IMPRIME_LISTA(SLista *pLista) {
    if (pLista->pFirst == NULL) {
        puts("Lista Vazia!");
        return;
    }
    
    SNodo *pNodo;
    printf("LISTA: ");
    for (pNodo = pLista->pFirst; pNodo != NULL; pNodo = pNodo->pNext) {
        printf("[%d] ", pNodo->dado.info);
    }
    printf("\n");
}

// --- LISTA DUPLAMENTE LIGADA ---
SListaDupla* RESET_LISTA_DUPLA(SListaDupla *pOldLista) {
    if (pOldLista)
        CLEAR_LISTA_DUPLA(pOldLista);
    
    SListaDupla *pLista = (SListaDupla*)malloc(sizeof(SListaDupla));
    pLista->pFirst = NULL;
    pLista->pLast = NULL;
    pLista->nCount = 0;
    
    return pLista;
}

void CLEAR_LISTA_DUPLA(SListaDupla *pLista) {
    SNodoDuplo *pAtual = pLista->pFirst;
    while (pAtual != NULL) {
        SNodoDuplo *pTemp = pAtual;
        pAtual = pAtual->pNext;
        free(pTemp);
    }
    pLista->pFirst = NULL;
    pLista->pLast = NULL;
    pLista->nCount = 0;
}

void INSERT_LISTA_DUPLA(SListaDupla *pLista, SInfo info) {
    SNodoDuplo *pNovo = (SNodoDuplo*)malloc(sizeof(SNodoDuplo));
    pNovo->dado = info;
    pNovo->pNext = NULL;
    pNovo->pPrevious = pLista->pLast;
    
    if (pLista->pLast != NULL)
        pLista->pLast->pNext = pNovo;
    else
        pLista->pFirst = pNovo;
    
    pLista->pLast = pNovo;
    pLista->nCount++;
}

int REMOVE_LISTA_DUPLA(SListaDupla *pLista, int info) {
    SNodoDuplo *pAtual = pLista->pFirst;
    
    while (pAtual != NULL && pAtual->dado.info != info) {
        pAtual = pAtual->pNext;
    }
    
    if (pAtual == NULL)
        return 0; // Não encontrado
    
    if (pAtual->pPrevious != NULL)
        pAtual->pPrevious->pNext = pAtual->pNext;
    else
        pLista->pFirst = pAtual->pNext;
    
    if (pAtual->pNext != NULL)
        pAtual->pNext->pPrevious = pAtual->pPrevious;
    else
        pLista->pLast = pAtual->pPrevious;
    
    free(pAtual);
    pLista->nCount--;
    return 1;
}

void IMPRIME_LISTA_DUPLA(SListaDupla *pLista) {
    if (pLista->pFirst == NULL) {
        puts("Lista Dupla Vazia!");
        return;
    }
    
    SNodoDuplo *pNodo;
    printf("LISTA DUPLA (Count: %d): ", pLista->nCount);
    for (pNodo = pLista->pFirst; pNodo != NULL; pNodo = pNodo->pNext) {
        printf("[%d] ", pNodo->dado.info);
    }
    printf("\n");
}

// --- HEAP (FILA DE PRIORIDADE) ---
SHeap* RESET_HEAP(SHeap *pOldHeap) {
    SHeap *pHeap = (SHeap*)malloc(sizeof(SHeap));
    pHeap->tamanho = 0;
    return pHeap;
}

void HEAPIFY_UP(SHeap *pHeap, int indice) {
    int pai = (indice - 1) / 2;
    
    if (indice > 0 && pHeap->elementos[indice].preco > pHeap->elementos[pai].preco) {
        SProduto temp = pHeap->elementos[indice];
        pHeap->elementos[indice] = pHeap->elementos[pai];
        pHeap->elementos[pai] = temp;
        
        HEAPIFY_UP(pHeap, pai);
    }
}

void HEAPIFY_DOWN(SHeap *pHeap, int indice) {
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;
    int maior = indice;
    
    if (esquerda < pHeap->tamanho && 
        pHeap->elementos[esquerda].preco > pHeap->elementos[maior].preco)
        maior = esquerda;
    
    if (direita < pHeap->tamanho && 
        pHeap->elementos[direita].preco > pHeap->elementos[maior].preco)
        maior = direita;
    
    if (maior != indice) {
        SProduto temp = pHeap->elementos[indice];
        pHeap->elementos[indice] = pHeap->elementos[maior];
        pHeap->elementos[maior] = temp;
        
        HEAPIFY_DOWN(pHeap, maior);
    }
}

void PUSH_HEAP(SHeap *pHeap, SProduto produto) {
    if (pHeap->tamanho >= MAX_HEAP) {
        puts("Heap cheio!");
        return;
    }
    
    pHeap->elementos[pHeap->tamanho] = produto;
    HEAPIFY_UP(pHeap, pHeap->tamanho);
    pHeap->tamanho++;
}

int POP_HEAP(SHeap *pHeap, SProduto *pProd) {
    if (pHeap->tamanho == 0) {
        puts("Heap vazio!");
        return 0;
    }
    
    *pProd = pHeap->elementos[0];
    pHeap->elementos[0] = pHeap->elementos[pHeap->tamanho - 1];
    pHeap->tamanho--;
    
    if (pHeap->tamanho > 0)
        HEAPIFY_DOWN(pHeap, 0);
    
    return 1;
}

void IMPRIME_HEAP(SHeap *pHeap) {
    if (pHeap->tamanho == 0) {
        puts("Heap Vazio!");
        return;
    }
    
    printf("HEAP (por prioridade): ");
    for (int i = 0; i < pHeap->tamanho; i++) {
        printf("[%s(%.2f)] ", pHeap->elementos[i].nome, pHeap->elementos[i].preco);
    }
    printf("\n");
}

// ===== FUNÇÃO PRINCIPAL DE TESTE =====
int main() {
    printf("=== TESTE DAS ESTRUTURAS DE DADOS ===\n\n");
    
    // --- TESTE DA FILA ---
    printf("--- TESTE DA FILA (FIFO) ---\n");
    SFila *fila = RESET_FILA(NULL);
    
    SProduto p1 = {1, "Produto A", 10.50};
    SProduto p2 = {2, "Produto B", 25.30};
    SProduto p3 = {3, "Produto C", 15.80};
    
    PUSH_FILA(fila, &p1);
    PUSH_FILA(fila, &p2);
    PUSH_FILA(fila, &p3);
    IMPRIME_FILA(fila);
    
    SProduto removido;
    POP_FILA(fila, &removido);
    printf("Removido: %s\n", removido.nome);
    IMPRIME_FILA(fila);
    
    // --- TESTE DA LISTA ---
    printf("\n--- TESTE DA LISTA LIGADA ---\n");
    SLista *lista = RESET_LISTA(NULL);
    
    SInfo info1 = {10};
    SInfo info2 = {20};
    SInfo info3 = {30};
    
    INSERT_LISTA(lista, info1);
    INSERT_LISTA(lista, info2);
    INSERT_LISTA(lista, info3);
    IMPRIME_LISTA(lista);
    
    REMOVE_LISTA(lista, 20);
    printf("Após remover 20:\n");
    IMPRIME_LISTA(lista);
    
    // --- TESTE DA LISTA DUPLA ---
    printf("\n--- TESTE DA LISTA DUPLAMENTE LIGADA ---\n");
    SListaDupla *listaDupla = RESET_LISTA_DUPLA(NULL);
    
    INSERT_LISTA_DUPLA(listaDupla, info1);
    INSERT_LISTA_DUPLA(listaDupla, info2);
    INSERT_LISTA_DUPLA(listaDupla, info3);
    IMPRIME_LISTA_DUPLA(listaDupla);
    
    REMOVE_LISTA_DUPLA(listaDupla, 20);
    printf("Após remover 20:\n");
    IMPRIME_LISTA_DUPLA(listaDupla);
    
    // --- TESTE DO HEAP ---
    printf("\n--- TESTE DO HEAP (FILA DE PRIORIDADE) ---\n");
    SHeap *heap = RESET_HEAP(NULL);
    
    SProduto h1 = {1, "Baixa", 5.00};
    SProduto h2 = {2, "Alta", 50.00};
    SProduto h3 = {3, "Media", 25.00};
    SProduto h4 = {4, "Muito Alta", 100.00};
    
    PUSH_HEAP(heap, h1);
    PUSH_HEAP(heap, h2);
    PUSH_HEAP(heap, h3);
    PUSH_HEAP(heap, h4);
    IMPRIME_HEAP(heap);
    
    SProduto removidoHeap;
    POP_HEAP(heap, &removidoHeap);
    printf("Removido (maior prioridade): %s (%.2f)\n", removidoHeap.nome, removidoHeap.preco);
    IMPRIME_HEAP(heap);
    
    // Limpeza
    CLEAR_FILA(fila);
    free(fila);
    CLEAR_LISTA(lista);
    free(lista);
    CLEAR_LISTA_DUPLA(listaDupla);
    free(listaDupla);
    free(heap);
    
    return 0;
}