char* shortestCompletingWord(char* licensePlate, char** words, int wordsSize) {
    int tamanho = strlen(licensePlate);
    char temp[tamanho];
    int atual = 0;
    int posi[wordsSize];
    //função para padronizar a string;
    for(int i = 0; i < sizeof(licensePlate) - 1; i++){
        if(licensePlate[i] != '1' && licensePlate[i] != '2' && licensePlate[i] != '3' && licensePlate[i] != '4' && licensePlate[i] != '5' && licensePlate[i] != '6' && licensePlate[i] != '7' && licensePlate[i] != '8' && licensePlate[i] != '9' && licensePlate[i] != '0' && licensePlate[i] != ' '){
            temp[atual] = tolower(licensePlate[i]);
            
            atual++;
    }
    }
    temp[atual] = '\0';
    //função para retornar a palavra
    int posmelhor = 0;
    int quant = 0;
    for(int j = 0; j < wordsSize; j++){
        int z = 0;
        if(strcmp(words[j], temp) == 0){
                return words[j];
            };
        for(int i = 0; i < strlen(words[j]); i++){
            for(int b = 0; b < strlen(temp); b++){
                if(temp[b] == words[j][i]){
                    z++;
                }
            }
        }
        if(z > quant){
            if(strlen(words[posmelhor]) > strlen(words[j])){
                posmelhor = j;
                quant = z;
            }
        }
        
        printf("\npalavra: %s", words[j]);
        printf("\nletras encontradas: %d", z);
        
    }
    return words[posmelhor];
}