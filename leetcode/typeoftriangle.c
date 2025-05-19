#include <stdio.h>

char* triangleType(int* nums, int numsSize) {
    if(nums[0] == nums[1]){
        if(nums[0] == nums[2]){
            return "equilateral";
        }else{
            return "isosceles";
        }
    }else{
        if(nums[0] == nums[2]){
            return "isosceles";
        }else{
            if(((nums[0] + nums[1]) > nums[2]) && ((nums[0] + nums[2]) > nums[1]) && ((nums[2] + nums[1]) > nums[0])){
                return "scalene";
            }else{
                return "none";
            }
        }
    }
        

    return "";
}