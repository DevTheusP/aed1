#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void preordem(struct TreeNode* root){
    printf("%d\n",root->val);
    if(root->left != NULL){
        preordem(root->left);
    }
    if(root->right != NULL){
        preordem(root->right);
    }
}
void ordem(struct TreeNode* root){
    if(root->left != NULL){
        ordem(root->left);
    }
    printf("%d\n",root->val);
    if(root->right != NULL){
        ordem(root->right);
    }
}
void posordem(struct TreeNode* root){
    
    if(root->left != NULL){
        posordem(root->left);
    }
    if(root->right != NULL){
        posordem(root->right);
    }
    printf("%d\n",root->val);
}

int altura(struct TreeNode* root){
    if(root == NULL){ return 0;
    }else{
        int alturadireita = altura(root->right);
        int alturaesquerda = altura(root->left);
        if(alturaesquerda > alturadireita){
            return alturaesquerda + 1;
        }else{
            return alturadireita + 1;
        }

    }
}