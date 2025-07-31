#include <stdio.h>
/*



*/
 
int main() {
 
    int dias = 0;
    int gcc = 0;
    int gct = 0;
    scanf("%d %d %d", &dias, &gcc, &gct);
    getchar();
    
    char ida[dias], volta[dias];
    for(int i = 0; i < dias; i++){
        char ct;
        char tc;
        scanf("%c %c", &ida[i], &volta[i]);
        getchar();
    }
    for(int j = 0; j < dias; j++){
        char saida1;
        char saida2;
        if(ida[j] == 'Y'){
            gcc--;
            gct ++;
            saida1 = 'Y';
        }else if(gct == 0){
            gcc --;
            gct ++;
            saida1 = 'Y';
        }else{
            saida1 = 'N';
        }
        if(volta[j] == 'Y'){
            gct --;
            gcc ++;
            saida2 = 'Y';
        }else if(gcc == 0){
            gct --;
            gcc ++;
            saida2 = 'Y';
        }else{
            saida2 = 'N';
        }
        printf("%c %c\n", saida1, saida2);
    }
 
    return 0;
}