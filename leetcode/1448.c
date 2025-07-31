#include <stdio.h>

struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
};
 



int preordem(struct TreeNode* root, int maxValue){
    if(root == NULL){
        return 0;
    };
    if(root->val >= maxValue){
        maxValue = root->val;
        return 1 + preordem(root->left, maxValue) + preordem(root->right,maxValue);
    }else{
        return preordem(root->left, maxValue) + preordem(root->right,maxValue);
        
};
}

int goodNodes(struct TreeNode* root){
    return preordem(root,root->val);
}