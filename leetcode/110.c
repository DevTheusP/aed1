#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int tamanho(struct TreeNode* root){
    if(root == NULL){
        return 0;
    }
    int a = tamanho(root->left);
    if(a == -1) return -1;
    int b = tamanho(root->right);
    if(b == -1) return -1;
    if(abs(a-b)>1){
        return -1;
    }
    return(1 + (a>b? a:b));
};
bool isBalanced(struct TreeNode* root) {
   int q = checkheight(root);
   if(q== -1){
    return false;
   }else{
    return true;
   }

}