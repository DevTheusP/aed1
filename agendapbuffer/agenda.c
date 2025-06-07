#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Layout do buffer:
// [0 a sizeof(int)-1]: escolha do menu (int)
// [sizeof(int) a 2*sizeof(int)-1]: numero de pessoas (int)
// [2*sizeof(int) a 3*sizeof(int)-1]: variavel auxiliar i (int)
// [3*sizeof(int) a 4*sizeof(int)-1]: variavel auxiliar encontrou (int)
// [4*sizeof(int) a 5*sizeof(int)-1]: variavel auxiliar j (int)
// [5*sizeof(int) a 5*sizeof(int)+NOME_SIZE-1]: buffer para nome de busca
// [5*sizeof(int)+NOME_SIZE+]: dados das pessoas
// Cada pessoa: [nome(20 bytes)] [idade(sizeof(int) bytes)] [email(50 bytes)]

#define NOME_SIZE 20
#define EMAIL_SIZE 50
#define PESSOA_SIZE (NOME_SIZE * sizeof(char) + sizeof(int) + EMAIL_SIZE * sizeof(char))
#define HEADER_SIZE (5 * sizeof(int) + NOME_SIZE)


void removerNovaLinha(char *str) {
    if (strlen(str) > 0 && str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
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
void adicionarPessoa(void **pBuffer);
void listarTodos(void *pBuffer);
void buscarPessoa(void *pBuffer);
void removerPessoa(void **pBuffer);

int main(){
    
    void *pBuffer = malloc(HEADER_SIZE);
    if(!pBuffer){
        printf("Memória insuficiente!\n");
        return 1;
    }

    void *escolha = pBuffer;
    *(int*)escolha = 0;

    void *numPessoas = (int*)pBuffer + 1;
    *(int*)numPessoas = 0;

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
                if (pBuffer) {
                    escolha = pBuffer;
                    numPessoas = (int*)pBuffer + 1;
                }
                break;
            case 2:
                removerPessoa(&pBuffer);
                if (pBuffer) {
                    escolha = pBuffer;
                    numPessoas = (int*)pBuffer + 1;
                }
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
    }
    
    free(pBuffer);
    return 0;
}

void adicionarPessoa(void **pBuffer) {
    
    void *numPessoas = (int*)*pBuffer + 1;
    
    void *novoBuffer = realloc(*pBuffer, HEADER_SIZE + ((*(int*)numPessoas) + 1) * PESSOA_SIZE);
    if (!novoBuffer) {
        printf("Erro: Memoria insuficiente!\n");
        return;
    }
    *pBuffer = novoBuffer; 
    
    
    numPessoas = (int*)*pBuffer + 1;
    (*(int*)numPessoas)++;
    
    void *novaPessoa = (char*)*pBuffer + HEADER_SIZE + ((*(int*)numPessoas) - 1) * PESSOA_SIZE;
    
    printf("Nome: ");
    
    limparBufferEntrada();
    
    if (fgets((char*)novaPessoa, NOME_SIZE, stdin) == NULL) {
        printf("Erro na leitura do nome!\n");
        // Recalcula ponteiro antes de usar
        numPessoas = (int*)*pBuffer + 1;
        (*(int*)numPessoas)--;
        return;
    }

    removerNovaLinha((char*)novaPessoa);
    
    void *idade = (char*)novaPessoa + NOME_SIZE;
    printf("Idade: ");
    scanf("%d", (int*)idade);
    
    void *email = (char*)novaPessoa + NOME_SIZE + sizeof(int);
    printf("Email: ");
    limparBufferEntrada();
    if (fgets((char*)email, EMAIL_SIZE, stdin) == NULL) {
        printf("Erro na leitura do email!\n");
        // Recalcula ponteiro antes de usar
        numPessoas = (int*)*pBuffer + 1;
        (*(int*)numPessoas)--;
        return;
    }
    
    // Remove \n do final do email
    removerNovaLinha((char*)email);
    
    printf("Pessoa adicionada com sucesso!\n");
}

void buscarPessoa(void *pBuffer) {
    void *numPessoas = (int*)pBuffer + 1;

    if (*(int*)numPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }
    void *nomeBusca = (char*)pBuffer + 5 * sizeof(int); 
    printf("Digite o nome para buscar: ");
    limparBufferEntrada();
    
    if (fgets((char*)nomeBusca, NOME_SIZE, stdin) == NULL) {
        printf("Erro na leitura do nome!\n");
        return;
    }
    removerNovaLinha((char*)nomeBusca);

    void *pessoa = (char*)pBuffer + HEADER_SIZE;
    void *i = (int*)pBuffer + 2;
     *(int*)i = 0;
    void *encontrou = (int*)pBuffer + 3; 
    *(int*)encontrou = 0;

    while(*(int*)i < *(int*)numPessoas){
        void *nome = pessoa;

        if(strcmp((char*)nome, (char*)nomeBusca) == 0){
            void *idade = (char*)pessoa + NOME_SIZE;
            void *email = (char*)pessoa + NOME_SIZE + sizeof(int);
            printf("\nPessoa encontrada:\n");
            printf("Nome: %s | Idade: %d | Email: %s\n", 
                   (char*)nome, *(int*)idade, (char*)email);
            *(int*)encontrou = 1;
            break;

        }
        pessoa = (char*)pessoa + PESSOA_SIZE;
        (*(int*)i)++;
    }
    if (*(int*)encontrou == 0) {
        printf("Pessoa nao encontrada.\n");
    }
}

void removerPessoa(void **pBuffer){
    void *numPessoas = (int*)*pBuffer + 1;

    if (*(int*)numPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    void *nomeBusca = (char*)*pBuffer + 5 * sizeof(int); 
    printf("Digite o nome da pessoa a remover: ");
    limparBufferEntrada();
    
    if (fgets((char*)nomeBusca, NOME_SIZE, stdin) == NULL) {
        printf("Erro na leitura do nome!\n");
        return;
    }
    removerNovaLinha((char*)nomeBusca);

    void *pessoa = (char*)*pBuffer + HEADER_SIZE;
    void *i = (int*)*pBuffer + 2; 
    *(int*)i = 0;
    void *encontrou = (int*)*pBuffer + 3; 
    *(int*)encontrou = 0;

    while (*(int*)i < *(int*)numPessoas) {
        void *nome = pessoa;
        if (strcmp((char*)nome, (char*)nomeBusca) == 0) {
            *(int*)encontrou = 1;

            void *j = (int*)*pBuffer + 4; 
            *(int*)j = *(int*)i;
            
            while (*(int*)j < *(int*)numPessoas - 1) {
                void *pessoaAtual = (char*)*pBuffer + HEADER_SIZE + (*(int*)j) * PESSOA_SIZE;
                void *proximaPessoa = (char*)*pBuffer + HEADER_SIZE + ((*(int*)j) + 1) * PESSOA_SIZE;
                
                memcpy(pessoaAtual, proximaPessoa, PESSOA_SIZE);
                (*(int*)j)++;
            }
            
            break;
        }
        pessoa = (char*)pessoa + PESSOA_SIZE;
        (*(int*)i)++;
    }
    
    if (*(int*)encontrou == 1) {
        
        (*(int*)numPessoas)--;
        
        
        void *novoBuffer;
        if (*(int*)numPessoas > 0) {
            novoBuffer = realloc(*pBuffer, HEADER_SIZE + (*(int*)numPessoas) * PESSOA_SIZE);
        } else {
            
            novoBuffer = realloc(*pBuffer, HEADER_SIZE);
        }
        
        if (!novoBuffer) {
            printf("Erro: Memoria insuficiente para realocar!\n");
            
            numPessoas = (int*)*pBuffer + 1;
            (*(int*)numPessoas)++; 
            return;
        }
        *pBuffer = novoBuffer;
        
        printf("Pessoa removida com sucesso!\n");
    } else {
        printf("Pessoa nao encontrada.\n");
    }
}

void listarTodos(void *pBuffer) {
    void *numPessoas = (int*)pBuffer + 1;
    
    if (*(int*)numPessoas == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }
    
    printf("\n=== LISTA DE PESSOAS ===\n");
    
    void *pessoa = (char*)pBuffer + HEADER_SIZE;
    void *i = (int*)pBuffer + 2; // usa posicao do buffer para i
    *(int*)i = 0;
    
    while (*(int*)i < *(int*)numPessoas) {
        void *nome = pessoa;
        void *idade = (char*)pessoa + NOME_SIZE;
        void *email = (char*)pessoa + NOME_SIZE + sizeof(int);
        
        printf("%d. Nome: %s | Idade: %d | Email: %s\n", 
               *(int*)i + 1, (char*)nome, *(int*)idade, (char*)email);
        
        pessoa = (char*)pessoa + PESSOA_SIZE;
        (*(int*)i)++;
    }
}