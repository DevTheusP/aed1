/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {
    if(root == NULL){
        return NULL;
    };
    invertTree(root->left);
    invertTree(root->right);
    struct TreeNode *temp = root->right;
    root->right = root->left;
    root->left = temp;
    return root;
}