// se o array estiver ordenado, retorna 0
//a raiz é fixa
//nums = [3,4,5,1,2]
// preciso garantir que os numros maior que a raiz estejam em ordem crescente
// e que os menores que a raiz estejam em ordem cr
int dfs(int* nums, int numsSize){
    printf("quantos numeros? %d\n", numsSize);
    printf("raiz = %d\n", nums[0]);
    if(numsSize < 3){
        return 1;
    }
    int maiorqueraiz = 0;
    int maiores[numsSize];
    int menoresqueraiz = 0;
    int menores[1000];
    for(int i = 1; i < numsSize; i++){
        if(nums[i]>nums[0]){
            maiores[maiorqueraiz] = nums[i];
            printf("%d\n", maiores[maiorqueraiz]);
            maiorqueraiz++;
        }else{
            menores[menoresqueraiz] = nums[i];
            printf("%d\n", menores[menoresqueraiz]);
            menoresqueraiz++;
            
        }
    }
    int m1 = numsSize - 1;
    int left = menoresqueraiz;
    int fat3 = m1 - left;
    for(int j = numsSize -2; j > 1; j--){
        m1 = m1 * j;
        printf("%d\n", m1);
        if(menoresqueraiz > j){
            left = left * j;
        }if(((numsSize -1) - menoresqueraiz) > j){
            fat3 = fat3 * j;
        }
    }
    int c = 1;
    if(left * fat3 != 0){
    int c = (m1)/(left * fat3);}
    printf("resultado combinação%d\n", c);
    return dfs(menores,menoresqueraiz) * c;

}
int numOfWays(int* nums, int numsSize) {
    if(nums[0] == 1){
        return 0;
    }
    return dfs(nums, numsSize);
    //maior que raiz = numeros do lado direito
    //menor que raiz = numeros do lado esquerdo
    //4 espaços para permutar
    // 2 menores que raiz
    //Preciso fazer o fatorial direito, a logica eu entendi;
}