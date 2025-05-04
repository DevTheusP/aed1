#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *nomes = NULL;  
    int opcao;
    char nome[50];
    
    do {
        
        printf("\n=== MENU ===\n");
        printf("1. Adicionar nome\n");
        printf("2. Remover nome\n");
        printf("3. Listar nomes\n");
        printf("4. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpar o buffer
        
        switch(opcao) {
            case 1:  
                printf("Digite o nome: ");
                fgets(nome, 50, stdin);
                nome[strlen(nome)-1] = '\0';  // Remover o \n
                
                if(nomes == NULL) {
                    nomes = (char*) malloc(strlen(nome) + 1);
                    strcpy(nomes, nome);
                } else {
                    nomes = (char*) realloc(nomes, strlen(nomes) + strlen(nome) + 2);
                    strcat(nomes, ",");
                    strcat(nomes, nome);
                }
                printf("Nome adicionado!\n");
                break;
                
            case 2:  
                if(nomes == NULL) {
                    printf("Lista vazia!\n");
                    break;
                }
                
                printf("Digite o nome para remover: ");
                fgets(nome, 50, stdin);
                nome[strlen(nome)-1] = '\0';  
                
                char *novaLista = NULL;
                char *temp = strdup(nomes);
                char *token = strtok(temp, ",");
                int primeiro = 1;
                
                while(token != NULL) {
                    if(strcmp(token, nome) != 0) {
                        if(primeiro) {
                            novaLista = (char*) malloc(strlen(token) + 1);
                            strcpy(novaLista, token);
                            primeiro = 0;
                        } else {
                            novaLista = (char*) realloc(novaLista, strlen(novaLista) + strlen(token) + 2);
                            strcat(novaLista, ",");
                            strcat(novaLista, token);
                        }
                    }
                    token = strtok(NULL, ",");
                }
                
                free(temp);
                free(nomes);
                nomes = novaLista;
                printf("Nome removido!\n");
                break;
                
            case 3:  
                if(nomes == NULL) {
                    printf("Lista vazia!\n");
                } else {
                    printf("Nomes na lista:\n");
                    char *temp = strdup(nomes);
                    char *token = strtok(temp, ",");
                    int i = 1;
                    
                    while(token != NULL) {
                        printf("%d. %s\n", i++, token);
                        token = strtok(NULL, ",");
                    }
                    
                    free(temp);
                }
                break;
                
            case 4:  
                printf("Saindo...\n");
                if(nomes != NULL) {
                    free(nomes);
                }
                break;
                
            default:
                printf("Opcao invalida!\n");
        }
        
    } while(opcao != 4);
    
    return 0;
}