#include <stdio.h>
typedef struct{
    int num[10];
    int topo;
    
}Pilha;

int isEmpty(Pilha * pilha){
    if(pilha->topo == 0){
        return 1;
    }else{
        return 0;
    }
}
int top(Pilha *pilha){
    if(!isEmpty(pilha)){
    return pilha->num[pilha->topo];
    }else{
        return 0;
    }
}
int isFull(Pilha *pilha){
    if(pilha->topo >= 9){
        return 1;
    }else{return 0;}
}

void push(Pilha *pilha, int num){
    if(isFull(pilha) == 1){
        
    }else{
        pilha->topo ++;
        pilha->num[pilha->topo] = num;
    }
}

int pop(Pilha *pilha){
    if(isEmpty(pilha) == 1){
        return 0;
    }else{
        int num = pilha->num[pilha->topo];
        pilha->topo --;
        return num;
    }
}

int maxChunksToSorted(int* arr, int arrSize) {
    Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));
    if (pilha == NULL) {
        return 0;
    }
    pilha->topo = 0;
    for(int i = 0;i < arrSize;i++){
        if(isEmpty(pilha) || arr[i] > top(pilha)){
            push(pilha,arr[i]);
        } else{
            int maxelement = top(pilha);
            while(!isEmpty(pilha) && arr[i] < top(pilha)){
                pop(pilha);
            }
            push(pilha, maxelement);
        }
    }
    return pilha->topo;
}