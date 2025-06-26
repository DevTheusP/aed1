#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ===================== VERSÃO ESTÁTICA =====================
const int MAX = 10;

typedef struct {
    char nome[30];
    int idade;
} Pessoa;

typedef struct {
    Pessoa pessoas[MAX];
    int topo;
    int base;
    int limite;
} PilhaEstatica;

// Funções da Pilha Estática
void ResetEstatica(PilhaEstatica *pilha) {
    pilha->topo = 0;
    pilha->base = 0;
    pilha->limite = MAX;
}

bool EmptyEstatica(PilhaEstatica *pilha) {
    return pilha->topo == 0;
}

bool FullEstatica(PilhaEstatica *pilha) {
    return pilha->topo == MAX;
}

bool PushEstatica(PilhaEstatica *pilha, Pessoa *item) {
    if (!FullEstatica(pilha)) {
        pilha->pessoas[pilha->topo] = *item;
        pilha->topo++;
        return true;
    } else {
        return false;
    }
}

bool PopEstatica(PilhaEstatica *pilha, Pessoa *pessoa) {
    if (EmptyEstatica(pilha)) {
        return false;
    }
    pilha->topo--;
    *pessoa = pilha->pessoas[pilha->topo];
    return true;
}

void ClearEstatica(PilhaEstatica *pilha) {
    pilha->topo = 0;
}

void ListarEstatica(PilhaEstatica *pilha) {
    printf("\n=== LISTANDO PILHA ESTÁTICA ===\n");
    if (EmptyEstatica(pilha)) {
        printf("Pilha vazia!\n");
        return;
    }
    
    // Criar uma pilha auxiliar para não destruir a original
    PilhaEstatica aux;
    ResetEstatica(&aux);
    
    // Transferir elementos para pilha auxiliar (invertendo ordem)
    while (!EmptyEstatica(pilha)) {
        Pessoa p;
        PopEstatica(pilha, &p);
        PushEstatica(&aux, &p);
    }
    
    // Listar e restaurar pilha original
    int pos = 1;
    while (!EmptyEstatica(&aux)) {
        Pessoa p;
        PopEstatica(&aux, &p);
        printf("%d. %s - %d anos\n", pos++, p.nome, p.idade);
        PushEstatica(pilha, &p);
    }
}

// ===================== VERSÃO DINÂMICA =====================
typedef struct {
    Pessoa *pessoas;
    int topo;
    int limite;
} PilhaDinamica;

void ResetDinamica(PilhaDinamica *pilha) {
    if (pilha->pessoas) {
        free(pilha->pessoas);
    }
    pilha->pessoas = NULL;
    pilha->topo = 0;
    pilha->limite = 0;
}

bool EmptyDinamica(PilhaDinamica *pilha) {
    return pilha->limite == 0;
}

bool PushDinamica(PilhaDinamica *pilha, Pessoa *item) {
    pilha->limite++;
    
    Pessoa *novaArea = (Pessoa *)realloc(pilha->pessoas, sizeof(Pessoa) * pilha->limite);
    if (!novaArea) {
        printf("Erro alocando memória!\n");
        pilha->limite--;
        return false;
    }
    
    pilha->pessoas = novaArea;
    pilha->pessoas[pilha->limite - 1] = *item;
    pilha->topo = pilha->limite - 1;
    return true;
}

bool PopDinamica(PilhaDinamica *pilha, Pessoa *pessoa) {
    if (EmptyDinamica(pilha)) {
        return false;
    }
    
    *pessoa = pilha->pessoas[pilha->topo];
    pilha->limite--;
    
    if (pilha->limite == 0) {
        free(pilha->pessoas);
        pilha->pessoas = NULL;
        pilha->topo = 0;
    } else {
        Pessoa *novaArea = (Pessoa *)realloc(pilha->pessoas, sizeof(Pessoa) * pilha->limite);
        if (novaArea) {
            pilha->pessoas = novaArea;
            pilha->topo = pilha->limite - 1;
        }
    }
    return true;
}

void ClearDinamica(PilhaDinamica *pilha) {
    ResetDinamica(pilha);
}

void ListarDinamica(PilhaDinamica *pilha) {
    printf("\n=== LISTANDO PILHA DINÂMICA ===\n");
    if (EmptyDinamica(pilha)) {
        printf("Pilha vazia!\n");
        return;
    }
    
    // Criar uma pilha auxiliar para não destruir a original
    PilhaDinamica aux;
    aux.pessoas = NULL;
    aux.topo = 0;
    aux.limite = 0;
    
    // Transferir elementos para pilha auxiliar (invertendo ordem)
    while (!EmptyDinamica(pilha)) {
        Pessoa p;
        PopDinamica(pilha, &p);
        PushDinamica(&aux, &p);
    }
    
    // Listar e restaurar pilha original
    int pos = 1;
    while (!EmptyDinamica(&aux)) {
        Pessoa p;
        PopDinamica(&aux, &p);
        printf("%d. %s - %d anos\n", pos++, p.nome, p.idade);
        PushDinamica(pilha, &p);
    }
    
    ResetDinamica(&aux);
}

// Função para deletar pessoa por nome (usando apenas POP e PUSH)
bool DeletarPorNomeEstatica(PilhaEstatica *pilha, char *nome) {
    PilhaEstatica aux;
    ResetEstatica(&aux);
    bool encontrou = false;
    
    // Transferir elementos para pilha auxiliar, exceto o que será removido
    while (!EmptyEstatica(pilha)) {
        Pessoa p;
        PopEstatica(pilha, &p);
        if (strcmp(p.nome, nome) == 0 && !encontrou) {
            encontrou = true; // Não adiciona na pilha auxiliar (remove)
        } else {
            PushEstatica(&aux, &p);
        }
    }
    
    // Restaurar pilha original sem o elemento removido
    while (!EmptyEstatica(&aux)) {
        Pessoa p;
        PopEstatica(&aux, &p);
        PushEstatica(pilha, &p);
    }
    
    return encontrou;
}

bool DeletarPorNomeDinamica(PilhaDinamica *pilha, char *nome) {
    PilhaDinamica aux;
    aux.pessoas = NULL;
    aux.topo = 0;
    aux.limite = 0;
    bool encontrou = false;
    
    // Transferir elementos para pilha auxiliar, exceto o que será removido
    while (!EmptyDinamica(pilha)) {
        Pessoa p;
        PopDinamica(pilha, &p);
        if (strcmp(p.nome, nome) == 0 && !encontrou) {
            encontrou = true; // Não adiciona na pilha auxiliar (remove)
        } else {
            PushDinamica(&aux, &p);
        }
    }
    
    // Restaurar pilha original sem o elemento removido
    while (!EmptyDinamica(&aux)) {
        Pessoa p;
        PopDinamica(&aux, &p);
        PushDinamica(pilha, &p);
    }
    
    ResetDinamica(&aux);
    return encontrou;
}

// ===================== PROGRAMA PRINCIPAL =====================
int main() {
    PilhaEstatica pilhaEst;
    PilhaDinamica pilhaDin;
    int opcao, tipo;
    
    ResetEstatica(&pilhaEst);
    pilhaDin.pessoas = NULL;
    pilhaDin.topo = 0;
    pilhaDin.limite = 0;
    
    printf("Escolha o tipo de pilha:\n");
    printf("1 - Pilha Estática (máx. %d elementos)\n", MAX);
    printf("2 - Pilha Dinâmica (sem limite)\n");
    printf("Opção: ");
    scanf("%d", &tipo);
    
    do {
        printf("\n=== MENU PILHA ===\n");
        printf("0: Inserir pessoa\n");
        printf("1: Deletar pessoa do topo\n");
        printf("2: Deletar pessoa por nome\n");
        printf("3: Limpar a pilha\n");
        printf("4: Listar pessoas\n");
        printf("5: Sair do programa\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 0: {
                Pessoa p;
                printf("Nome: ");
                scanf(" %29[^\n]", p.nome);
                printf("Idade: ");
                scanf("%d", &p.idade);
                
                bool sucesso;
                if (tipo == 1) {
                    sucesso = PushEstatica(&pilhaEst, &p);
                } else {
                    sucesso = PushDinamica(&pilhaDin, &p);
                }
                
                if (sucesso) {
                    printf("Pessoa inserida com sucesso!\n");
                } else {
                    printf("Erro ao inserir pessoa!\n");
                }
                break;
            }
            
            case 1: {
                Pessoa p;
                bool sucesso;
                
                if (tipo == 1) {
                    sucesso = PopEstatica(&pilhaEst, &p);
                } else {
                    sucesso = PopDinamica(&pilhaDin, &p);
                }
                
                if (sucesso) {
                    printf("Pessoa removida: %s - %d anos\n", p.nome, p.idade);
                } else {
                    printf("Pilha vazia! Nenhuma pessoa para remover.\n");
                }
                break;
            }
            
            case 2: {
                char nome[30];
                printf("Nome da pessoa a ser removida: ");
                scanf(" %29[^\n]", nome);
                
                bool encontrou;
                if (tipo == 1) {
                    encontrou = DeletarPorNomeEstatica(&pilhaEst, nome);
                } else {
                    encontrou = DeletarPorNomeDinamica(&pilhaDin, nome);
                }
                
                if (encontrou) {
                    printf("Pessoa '%s' removida com sucesso!\n", nome);
                } else {
                    printf("Pessoa '%s' não encontrada na pilha.\n", nome);
                }
                break;
            }
            
            case 3: {
                if (tipo == 1) {
                    ClearEstatica(&pilhaEst);
                } else {
                    ClearDinamica(&pilhaDin);
                }
                printf("Pilha limpa com sucesso!\n");
                break;
            }
            
            case 4: {
                if (tipo == 1) {
                    ListarEstatica(&pilhaEst);
                } else {
                    ListarDinamica(&pilhaDin);
                }
                break;
            }
            
            case 5: {
                printf("Saindo do programa...\n");
                if (tipo == 2) {
                    ResetDinamica(&pilhaDin);
                }
                break;
            }
            
            default: {
                printf("Opção inválida! Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 5);
    
    return 0;
}