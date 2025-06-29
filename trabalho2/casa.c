#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Matheus Persch
//Push e POP funcionando corretamente, faltou criar uma lógica para 
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
    
    // Se x == y, pode remover qualquer um primeiro
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
    
    // Determina qual operação priorizar baseado no maior valor
    char first_char, second_char;
    int first_points, second_points;
    
    if (x > y) {
        first_char = 'a'; second_char = 'b'; first_points = x; second_points = y;
    } else {
        first_char = 'b'; second_char = 'a'; first_points = y; second_points = x;
    }
    
    // Primeira passada: remove a substring de maior valor
    for(int i = 0; i < len; i++) {
        if(!isEmpty(pilha) && pilha->letras[pilha->topo] == first_char && s[i] == second_char) {
            pop(pilha);
            score += first_points;
        } else {
            push(pilha, s[i]);
        }
    }
    
    // Cria uma nova string com o que sobrou na pilha
    char *remaining = (char*)malloc(100001 * sizeof(char));
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