#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1000
#define HEADER_SIZE (15 * sizeof(int) + 3 * MAX_INPUT)

// Layout do buffer expandido:
// [cabeçalho de HEADER_SIZE bytes] [área de dados dos contatos]

void removerNovaLinha(void *pBuffer, void *strPtr) {
    void *str = strPtr;
    if (strlen((char*)str) > 0 && ((char*)str)[strlen((char*)str)-1] == '\n') {
        ((char*)str)[strlen((char*)str)-1] = '\0';
    }
}

void limparBufferEntrada() {
    while(getchar() != '\n');
}

void mostrarMenu() {
    printf("\n=== AGENDA PBUFFER ===\n");
    printf("1 - Adicionar Pessoa\n");
    printf("2 - Remover Pessoa\n");
    printf("3 - Buscar Pessoa\n");
    printf("4 - Listar todos\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");
}

// Assinaturas das funções
void adicionarPessoa(void **pBuffer);
void removerPessoa(void **pBuffer);
void buscarPessoa(void *pBuffer);
void listarTodos(void *pBuffer);
void calcularTamanhoUsado(void *pBuffer);


int main(){
    
    void *pBuffer = malloc(HEADER_SIZE);
    if(!pBuffer){
        printf("Memoria insuficiente!\n");
        return 1;
    }

    // Zera os campos do cabeçalho para garantir um estado inicial limpo.
    memset(pBuffer, 0, HEADER_SIZE);

    void *escolha = pBuffer;

    while (*(int*)escolha != 5) {
        mostrarMenu();
        if (scanf("%d", (int*)escolha) != 1) {
            printf("Entrada invalida!\n");
            limparBufferEntrada();
            
            continue;
        }

        switch (*(int*)escolha) {
            case 1:
                adicionarPessoa(&pBuffer);
                break;
            case 2:
                removerPessoa(&pBuffer);
                break;
            case 3:
                buscarPessoa(pBuffer);
                break;
            case 4:
                listarTodos(pBuffer);
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }

        if (pBuffer) {
            escolha = pBuffer;
        } else {
            printf("Erro critico de memoria! Encerrando.\n");
            return 1; // Encerra se o buffer se tornou nulo
        }
    }

    free(pBuffer);
    
}


void calcularTamanhoUsado(void *pBuffer) {
    void *numPessoas = (int*)pBuffer + 1;
    void *i = (int*)pBuffer + 2;
    void *ponteiroAtual = (char*)pBuffer + HEADER_SIZE;
    void *resultadoCalculo = (int*)pBuffer + 5; // Slot para armazenar o resultado
    *(int*)i = 0;

    while (*(int*)i < *(int*)numPessoas) {
        void *tamanhoNome = ponteiroAtual;
        void *idade = (char*)ponteiroAtual + sizeof(int) + *(int*)tamanhoNome;
        void *tamanhoEmail = (char*)idade + sizeof(int);
        ponteiroAtual = (char*)tamanhoEmail + sizeof(int) + *(int*)tamanhoEmail;
        (*(int*)i)++;
    }
    *(int*)resultadoCalculo = (char*)ponteiroAtual - (char*)pBuffer;
}


void adicionarPessoa(void **pBuffer) {
    // Ponteiros para os slots temporários no cabeçalho
    void *tempNome = (char*)*pBuffer + 15 * sizeof(int);
    void *tempEmail = (char*)*pBuffer + 15 * sizeof(int) + MAX_INPUT;
    void *idadeTemp = (int*)*pBuffer + 6;
    void *tamanhoNomeTemp = (int*)*pBuffer + 7;
    void *tamanhoEmailTemp = (int*)*pBuffer + 8;
    void *aux = (int*)*pBuffer + 4; // Slot aux para removerNovaLinha
    void *tamanhoAtual = (int*)*pBuffer + 9;
    void *tamanhoNovoRegistro = (int*)*pBuffer + 10;
    void *novoTamanhoTotal = (int*)*pBuffer + 11;

    printf("Nome: ");
    limparBufferEntrada();
    fgets((char*)tempNome, MAX_INPUT, stdin);
    removerNovaLinha(*pBuffer, tempNome);
    *(int*)tamanhoNomeTemp = strlen((char*)tempNome) + 1;

    printf("Email: ");
    fgets((char*)tempEmail, MAX_INPUT, stdin);
    removerNovaLinha(*pBuffer, tempEmail);
    *(int*)tamanhoEmailTemp = strlen((char*)tempEmail) + 1;

    printf("Idade: ");
    scanf("%d", (int*)idadeTemp);

    // Armazena valores calculados nos slots do buffer
    void *resultadoCalculo = (int*)*pBuffer + 5;
    calcularTamanhoUsado(*pBuffer);
    *(int*)tamanhoAtual = *(int*)resultadoCalculo;
    *(int*)tamanhoNovoRegistro = sizeof(int) + *(int*)tamanhoNomeTemp + sizeof(int) + sizeof(int) + *(int*)tamanhoEmailTemp;
    *(int*)novoTamanhoTotal = *(int*)tamanhoAtual + *(int*)tamanhoNovoRegistro;

    void *novoBuffer = realloc(*pBuffer, *(int*)novoTamanhoTotal);
    if (!novoBuffer) {
        printf("Erro: Memoria insuficiente!\n");
        return;
    }
    *pBuffer = novoBuffer; 

    // Recalcula ponteiros para os dados temporários após realloc
    tempNome = (char*)*pBuffer + 15 * sizeof(int);
    tempEmail = (char*)*pBuffer + 15 * sizeof(int) + MAX_INPUT;
    idadeTemp = (int*)*pBuffer + 6;
    tamanhoNomeTemp = (int*)*pBuffer + 7;
    tamanhoEmailTemp = (int*)*pBuffer + 8;
    tamanhoAtual = (int*)*pBuffer + 9;

    // Adiciona a nova pessoa no final do buffer
    void *posicaoNovaPessoa = (char*)*pBuffer + *(int*)tamanhoAtual;

    *(int*)posicaoNovaPessoa = *(int*)tamanhoNomeTemp;
    void *nomeDestino = (char*)posicaoNovaPessoa + sizeof(int);
    strcpy((char*)nomeDestino, (char*)tempNome);

    void *idadeDestino = (char*)nomeDestino + *(int*)tamanhoNomeTemp;
    *(int*)idadeDestino = *(int*)idadeTemp;

    void *tamanhoEmailDestino = (char*)idadeDestino + sizeof(int);
    *(int*)tamanhoEmailDestino = *(int*)tamanhoEmailTemp;

    void *emailDestino = (char*)tamanhoEmailDestino + sizeof(int);
    strcpy((char*)emailDestino, (char*)tempEmail);

    void *numPessoas = (int*)*pBuffer + 1;
    (*(int*)numPessoas)++;

    printf("Pessoa adicionada com sucesso!\n");
}


void removerPessoa(void **pBuffer){
    void *numPessoas = (int*)*pBuffer + 1;
    if (*(int*)numPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n"); return;
    }

    void *nomeBusca = (char*)*pBuffer + 15 * sizeof(int) + 2 * MAX_INPUT;
    void *aux = (int*)*pBuffer + 4;
    
    void *tamanhoTotalBuffer = (int*)*pBuffer + 12;
    void *bytesParaMover = (int*)*pBuffer + 13;
    void *novoTamanho = (int*)*pBuffer + 14;

    printf("Digite o nome da pessoa a remover: ");
    limparBufferEntrada();
    fgets((char*)nomeBusca, MAX_INPUT, stdin);
    removerNovaLinha(*pBuffer, nomeBusca);

    void *ponteiroAtual = (char*)*pBuffer + HEADER_SIZE;
    void *i = (int*)*pBuffer + 2;
    *(int*)i = 0;
    void *encontrou = (int*)*pBuffer + 3;
    *(int*)encontrou = 0;

    while (*(int*)i < *(int*)numPessoas) {
        void *tamanhoNomePessoa = ponteiroAtual;
        void *nome = (char*)ponteiroAtual + sizeof(int);
        void *idade = (char*)nome + *(int*)tamanhoNomePessoa;
        void *tamanhoEmailPessoa = (char*)idade + sizeof(int);
        void *email = (char*)tamanhoEmailPessoa + sizeof(int);
        void *proximaPessoa = (char*)email + *(int*)tamanhoEmailPessoa;

        if (strcmp((char*)nome, (char*)nomeBusca) == 0) {
            *(int*)encontrou = 1;
            void *resultadoCalculo = (int*)*pBuffer + 5;
            calcularTamanhoUsado(*pBuffer);
            *(int*)tamanhoTotalBuffer = *(int*)resultadoCalculo;
            *(int*)bytesParaMover = (char*)*pBuffer + *(int*)tamanhoTotalBuffer - (char*)proximaPessoa;

            if (*(int*)bytesParaMover > 0) {
                memmove(ponteiroAtual, proximaPessoa, *(int*)bytesParaMover);
            }
            break;
        }
        ponteiroAtual = proximaPessoa;
        (*(int*)i)++;
    }

    if (*(int*)encontrou == 1) {
        (*(int*)numPessoas)--;
        void *resultadoCalculo = (int*)*pBuffer + 5;
        calcularTamanhoUsado(*pBuffer);
        *(int*)novoTamanho = *(int*)resultadoCalculo;

        
        if (*(int*)numPessoas == 0) {
            *(int*)novoTamanho = HEADER_SIZE;
        }

        void *novoBuffer = realloc(*pBuffer, *(int*)novoTamanho);
        if (novoBuffer) {
            *pBuffer = novoBuffer;
        } else if (*(int*)numPessoas > 0) {
            printf("Aviso: falha ao encolher o buffer de memoria.\n");
        }
        printf("Pessoa removida com sucesso!\n");
    } else {
        printf("Pessoa nao encontrada.\n");
    }
}


void buscarPessoa(void *pBuffer) {
    void *numPessoas = (int*)pBuffer + 1;
    if (*(int*)numPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n"); return;
    }

    void *nomeBusca = (char*)pBuffer + 15 * sizeof(int) + 2 * MAX_INPUT;
    void *aux = (int*)pBuffer + 4; 

    printf("Digite o nome para buscar: ");
    limparBufferEntrada();
    fgets((char*)nomeBusca, MAX_INPUT, stdin);
    removerNovaLinha(pBuffer, nomeBusca);

    void *ponteiroAtual = (char*)pBuffer + HEADER_SIZE;
    void *i = (int*)pBuffer + 2;
    *(int*)i = 0;
    void *encontrou = (int*)pBuffer + 3;
    *(int*)encontrou = 0;

    while(*(int*)i < *(int*)numPessoas){
        void *tamanhoNomePessoa = ponteiroAtual;
        void *nome = (char*)ponteiroAtual + sizeof(int);

        if(strcmp((char*)nome, (char*)nomeBusca) == 0){
            void *idade = (char*)nome + *(int*)tamanhoNomePessoa;
            void *tamanhoEmailPessoa = (char*)idade + sizeof(int);
            void *email = (char*)tamanhoEmailPessoa + sizeof(int);

            printf("\nPessoa encontrada:\n");
            printf("Nome: %s | Idade: %d | Email: %s\n", (char*)nome, *(int*)idade, (char*)email);
            *(int*)encontrou = 1;
            break;
        }

        void *idade = (char*)nome + *(int*)tamanhoNomePessoa;
        void *tamanhoEmailPessoa = (char*)idade + sizeof(int);
        void *email = (char*)tamanhoEmailPessoa + sizeof(int);
        ponteiroAtual = (char*)email + *(int*)tamanhoEmailPessoa;
        (*(int*)i)++;
    }

    if (*(int*)encontrou == 0) {
        printf("Pessoa nao encontrada.\n");
    }
}


void listarTodos(void *pBuffer) {
    void *numPessoas = (int*)pBuffer + 1;
    if (*(int*)numPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n"); return;
    }

    printf("\n=== LISTA DE PESSOAS ===\n");

    void *ponteiroAtual = (char*)pBuffer + HEADER_SIZE;
    void *i = (int*)pBuffer + 2;
    *(int*)i = 0;

    while (*(int*)i < *(int*)numPessoas) {
        void *tamanhoNomePessoa = ponteiroAtual;
        void *nome = (char*)ponteiroAtual + sizeof(int);
        void *idade = (char*)nome + *(int*)tamanhoNomePessoa;
        void *tamanhoEmailPessoa = (char*)idade + sizeof(int);
        void *email = (char*)tamanhoEmailPessoa + sizeof(int);

        printf("%d. Nome: %s | Idade: %d | Email: %s\n",
               *(int*)i + 1, (char*)nome, *(int*)idade, (char*)email);

        ponteiroAtual = (char*)email + *(int*)tamanhoEmailPessoa;
        (*(int*)i)++;
    }
}