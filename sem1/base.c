//Matheus Persch
//Trabalho extra PC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Filme {
    int id;
    char nome[100];
    int ano;
    struct Filme* proximo;
} Filme;


Filme* inicializarLista();
Filme* criarFilme(int id, char* nome, int ano);
int idExiste(Filme* cabeca, int id);
void adicionarFilme(Filme* cabeca, int id, char* nome, int ano);
void removerFilme(Filme* cabeca, int id);
void imprimirLista(Filme* cabeca);
void liberarLista(Filme* cabeca);

int main() {
    
    Filme* cabecaLista = inicializarLista();
    int opcao, id, ano;
    char nome[100];
    
    do {
        printf("\n===== GERENCIADOR DE FILMES =====\n");
        printf("1. Adicionar filme\n");
        printf("2. Remover filme\n");
        printf("3. Imprimir lista\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 
        
        switch (opcao) {
            case 1:
                printf("\n--- ADICIONAR FILME ---\n");
                printf("Digite o ID do filme: ");
                scanf("%d", &id);
                getchar(); 
                
                printf("Digite o nome do filme: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0; 
                
                printf("Digite o ano de lancamento: ");
                scanf("%d", &ano);
                getchar();
                
                adicionarFilme(cabecaLista, id, nome, ano);
                break;
                
            case 2:
                printf("\n--- REMOVER FILME ---\n");
                printf("Digite o ID do filme a ser removido: ");
                scanf("%d", &id);
                getchar();
                
                removerFilme(cabecaLista, id);
                break;
                
            case 3:
                imprimirLista(cabecaLista);
                break;
                
            case 4:
                printf("\nLiberando memoria e encerrando o programa...\n");
                liberarLista(cabecaLista);
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
    } while (opcao != 4);
    
    printf("Programa encerrado!\n");
    return 0;
}

Filme* inicializarLista() {
    
    Filme *start;

	start = (Filme *) malloc(sizeof(Filme));
	start->proximo = NULL;
	return start;
}

Filme* criarFilme(int id, char* nome, int ano) {
    Filme* novoFilme = (Filme*)malloc(sizeof(Filme));
    if (novoFilme == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    
    novoFilme->id = id;
    strcpy(novoFilme->nome, nome);
    novoFilme->ano = ano;
    novoFilme->proximo = NULL;
    
    return novoFilme;
}

int idExiste(Filme* cabeca, int id) {
    Filme* temp = cabeca->proximo;  // Começa do primeiro elemento real (depois da cabeça)
    while (temp != NULL) {
        if (temp->id == id) {
            return 1; // ID existe
        }
        temp = temp->proximo;
    }
    return 0; // ID não existe
}

void adicionarFilme(Filme* cabeca, int id, char* nome, int ano) {
    
    if (idExiste(cabeca, id)) {
        printf("Erro: Um filme com ID %d ja existe!\n", id);
        return;
    }
    
    Filme* novoFilme = criarFilme(id, nome, ano);
    
    
    Filme* atual = cabeca->proximo;
    Filme* anterior = cabeca;
    
    // Percorre a lista até encontrar a posição correta
    while (atual != NULL && (ano > atual->ano || (ano == atual->ano && strcmp(nome, atual->nome) >= 0))) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    // Inserir o filme na posição correta
    anterior->proximo = novoFilme;
    novoFilme->proximo = atual;
    
    printf("Filme '%s' adicionado com sucesso!\n", nome);
}

void removerFilme(Filme* cabeca, int id) {
    if (cabeca->proximo == NULL) {
        printf("Lista vazia! Nao ha filmes para remover.\n");
        return;
    }
    

    Filme* atual = cabeca->proximo;
    Filme* anterior = cabeca;
    
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    // Se o filme não foi encontrado
    if (atual == NULL) {
        printf("Filme com ID %d nao encontrado!\n", id);
        return;
    }
    
    anterior->proximo = atual->proximo;
    free(atual);
    printf("Filme com ID %d removido com sucesso!\n", id);
}

void imprimirLista(Filme* cabeca) {
    if (cabeca->proximo == NULL) {
        printf("Lista vazia! Nao ha filmes para exibir.\n");
        return;
    }
    
    printf("\n===== LISTA DE FILMES =====\n");
    printf("ID\tANO\tNOME\n");
    printf("---------------------------\n");
    
    Filme* atual = cabeca->proximo;  
    while (atual != NULL) {
        printf("%d\t%d\t%s\n", atual->id, atual->ano, atual->nome);
        atual = atual->proximo;
    }
    printf("===========================\n\n");
}

void liberarLista(Filme* cabeca) {
    Filme* atual = cabeca->proximo;  
    Filme* proximo;
    
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    cabeca->proximo = NULL;
    free(cabeca);
}