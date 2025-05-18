void sortColors(int* nums, int numsSize) {
    int zero = 0, um = 0, dois = 0;
    for(int i = 0;i < numsSize; i++){
        if(nums[i] == 0){
            zero ++;
        }
        if(nums[i] == 1){
            um++;
        }
        if(nums[i] == 2){
            dois++;
        }
    }
    for(int x = 0; x < numsSize; x++){
        if(zero > 0){
            nums[x] = 0;
            zero--;
        }else if(um > 0){
            nums[x] = 1;
            um--;
        }else{
            nums[x] = 2;
            dois--;
        }
    }
}