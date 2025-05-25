char* shortestCompletingWord(char* licensePlate, char** words, int wordsSize) {
    int tamanho = strlen(licensePlate);
    char temp[tamanho + 1];
    int atual = 0;
    for(int i = 0; i < sizeof(licensePlate) - 1; i++){  
        if(licensePlate[i] != '1' && licensePlate[i] != '2' && licensePlate[i] != '3' && licensePlate[i] != '4' && licensePlate[i] != '5' && licensePlate[i] != '6' && licensePlate[i] != '7' && licensePlate[i] != '8' && licensePlate[i] != '9' && licensePlate[i] != '0' && licensePlate[i] != ' '){
            temp[atual] = tolower(licensePlate[i]);
            atual++;
        }
    }
    temp[atual] = '\0';
    int posmelhor = 0;
    int quant = 0;
    int encontrouValida = 0;  //Flag para saber se já encontrou palavra válida
    for(int j = 0; j < wordsSize; j++){
        int z = 0;    
        if(strcmp(words[j], temp) == 0){
            return words[j];
        };
        // Verificar se palavra contém CADA letra de temp
        int palavraValida = 1;  // Assumindo que é válida até provar o contrário
        for(int b = 0; b < strlen(temp); b++){
            int contaTemp = 0;
            int contaPalavra = 0;
            // Contar quantas vezes esta letra aparece em temp
            for(int x = 0; x < strlen(temp); x++){
                if(temp[x] == temp[b]){
                    contaTemp++;
                }
            }
            for(int i = 0; i < strlen(words[j]); i++){
                if(temp[b] == tolower(words[j][i])){  //Adicionei tolower
                    contaPalavra++;
                }
            }
            // Se não tem letras suficientes, palavra não é válida
            if(contaPalavra < contaTemp){
                palavraValida = 0;
                break;
            }
        }
        //Só considerar palavras válidas e escolher a menor
        if(palavraValida){
            if(!encontrouValida || strlen(words[j]) < strlen(words[posmelhor])){
                posmelhor = j;
                encontrouValida = 1;
            }
            z = 1;  // Marcar como válida para o print
        }
        
        
    }
    return words[posmelhor];
}