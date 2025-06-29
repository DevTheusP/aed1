#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char letras[100001];
    int topo;
    
}Pilha;

int isEmpty(Pilha * pilha){
    if(pilha->topo == 0){
        return 1;
    }else{
        return 0;
    }
}

int isFull(Pilha *pilha){
    if(pilha->topo >= 100001-1){
        return 1;
    }else{return 0;}
}

void push(Pilha *pilha, char letra){
    if(isFull(pilha) == 1){
        return;
    }else{
        pilha->topo ++;
        pilha->letras[pilha->topo] = letra;
    }
}

char pop(Pilha *pilha){
    if(isEmpty(pilha) == 1){
        return ' ';
    }else{
        char letra = pilha->letras[pilha->topo];
        pilha->topo --;
        return letra;
    }
}

int maximumGain(char* s, int x, int y) {
    int score = 0;
    Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));
    if (pilha == NULL) {
        return 0;
    }
    pilha->topo = 0;
    
    int len = strlen(s);
    
    if (x == y) {
        for(int i = 0; i < len; i++) {
            if(!isEmpty(pilha) && 
               ((pilha->letras[pilha->topo] == 'a' && s[i] == 'b') ||
                (pilha->letras[pilha->topo] == 'b' && s[i] == 'a'))) {
                pop(pilha);
                score += x;
            } else {
                push(pilha, s[i]);
            }
        }
        free(pilha);
        return score;
    }
    
    char first_char, second_char;
    int first_points, second_points;
    
    if (x > y) {
        first_char = 'a'; second_char = 'b'; first_points = x; second_points = y;
    } else {
        first_char = 'b'; second_char = 'a'; first_points = y; second_points = x;
    }
    
    for(int i = 0; i < len; i++) {
        if(!isEmpty(pilha) && pilha->letras[pilha->topo] == first_char && s[i] == second_char) {
            pop(pilha);
            score += first_points;
        } else {
            push(pilha, s[i]);
        }
    }
    
    char *remaining = (char*)malloc(200000 * sizeof(char));
    if (remaining == NULL) {
        free(pilha);
        return score;
    }
    
    int remaining_size = 0;
    while(!isEmpty(pilha)) {
        remaining[remaining_size++] = pop(pilha);
    }
    
    for(int i = remaining_size - 1; i >= 0; i--) {
        if(!isEmpty(pilha) && pilha->letras[pilha->topo] == second_char && remaining[i] == first_char) {
            pop(pilha);
            score += second_points;
        } else {
            push(pilha, remaining[i]);
        }
    }
    
    free(remaining);
    free(pilha);
    return score;
}

int main() {
    char *s = (char*)malloc(100001 * sizeof(char));
    if (s == NULL) {
        printf("Erro: não foi possível alocar memória\n");
        return 1;
    }
    
    int x, y;
    
    printf("Digite a string: ");
    if (scanf("%100000s", s) != 1) {
        printf("Erro na leitura da string\n");
        free(s);
        return 1;
    }
    
    printf("Digite o valor de x (pontos para remover 'ab'): ");
    if (scanf("%d", &x) != 1) {
        printf("Erro na leitura de x\n");
        free(s);
        return 1;
    }
    
    printf("Digite o valor de y (pontos para remover 'ba'): ");
    if (scanf("%d", &y) != 1) {
        printf("Erro na leitura de y\n");
        free(s);
        return 1;
    }
    
    int resultado = maximumGain(s, x, y);
    printf("Pontuação máxima: %d\n", resultado);
    
    free(s);
    return 0;
}