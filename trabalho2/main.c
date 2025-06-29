//Matheus Persch
//Push e POP funcionando corretamente, faltou criar uma lógica para 
typedef struct{
    char letras[100000];
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
    if(pilha->topo >= 100000-1){
        return 1;
    }else{return 0;}
}

void push(Pilha *pilha, char letra){
    if(isFull(pilha) == 1){
        printf("Pilha cheia");
        return;
    }else{
        pilha->topo ++;
        pilha->letras[pilha->topo] = letra;
        printf("Colocou %c", letra);
    }
}

char pop(Pilha *pilha){
    if(isEmpty(pilha) == 1){
        printf("Pilha vazia");
    }else{
        char letra = pilha->letras[pilha->topo];
        pilha->topo --;
        printf("\n tirou %c", letra);
        return letra;
    }
    return ' ';
}

int encontroux(Pilha *pilha){
    for(int j = pilha->topo - 2; j >= 0; j --){
        char temp = pop(pilha);
        if(temp == 'a'){
            if(pop(pilha) == 'b'){
                printf("\nencontrou x");
                return 1;
            }
        }else{
            push(pilha, temp);
        }
    }
    printf("\nencontrou nada");
    for(int l = pilha->topo; l > 0; l --){
            printf("%c", pilha->letras[l]);
        }
        printf("\n");
    return 0;
}
int encontrouy(Pilha *pilha){
    for(int j = pilha->topo - 2; j >= 0; j --){
        if(pop(pilha) == 'b'){
            if(pop(pilha) == 'a'){
                printf("\nencontrou y");
                return 1;
            };
        }
    }
    printf("\nencontrou nada");
    for(int l = pilha->topo; l > 0; l --){
            printf("%c", pilha->letras[l]);
        }
        printf("\n");
    return 0;
}

int maximumGain(char* s, int x, int y) {
    int score = 0;
    Pilha *pilha = (Pilha*)malloc(sizeof(Pilha));
    pilha->topo = 0;
    for(int i = strlen(s) - 1; i >= 0; i--){
        push(pilha, s[i]);
    }
    int bol = 1;
    while(bol == 1){
        if(encontrouy(pilha)){
            score += y;
        }else if(encontroux(pilha)){
            score += x;
        }else{
            bol = 0;
        }
    }
    
    return score;

}