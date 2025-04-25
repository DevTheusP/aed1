#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    //não lembro como realocar memória caso precisar
    char nomes[100] = "";
    char nometemp[50]= "";
    int opcao = 0;
    printf("\nDigite 1 para adicionar nome, 2 para excluir, 3 para listar e 4 para sair: ");
    scanf("%d", &opcao);
    getchar();
    while (opcao != 4){
        switch (opcao)
        {
        case 1:
        printf("\nDigite o nome a ser adicionado: ");
        fgets(nometemp, 50, stdin);
        strcat(nomes, nometemp);
            break;
        case 2:
        printf("\nDigite o nome a ser removido");
        fgets(nometemp, 50, stdin);
        strcspn(nomes, nometemp);
            break;
        
        case 3:
            printf("\nListando todos os nomes");
            printf("\n%s", nomes);
            break;
        
        case 4:
            printf("\nPrograma encerrado");
            break;

        default:

            break;
        };
        printf("\nDigite 1 para adicionar nome, 2 para excluir, 3 para listar e 4 para sair: ");
        scanf("%d", &opcao);
        getchar();
    };
    
};