/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

 

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 

Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106
https://leetcode.com/problems/median-of-two-sorted-arrays/description/
*/
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    int temp[nums1Size+nums2Size];
    int x =0;
        for (int i = 0 ; i<nums1Size+nums2Size ; i++){
            if (i < nums1Size)
               temp[i] = nums1[i];
            else
                temp[i] = nums2[x++];

        }
        for(int i=0;i<nums1Size+nums2Size;i++){
            for(int j=i+1;j<nums1Size+nums2Size;j++){
                if(temp[i]>temp[j]){
                    int t= temp[i];
                    temp[i]=temp[j];
                    temp[j]=t;
                }
            }
        }
        if ((nums1Size+nums2Size) %2 ==0){
            int l = (nums1Size+nums2Size) /2;
            return (temp[l]+temp[l-1])/2.00;
        }
        else {
            return temp[(nums1Size+nums2Size)/2];
        }

}