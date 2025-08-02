#include <stdio.h>
#include <stdlib.h>
int minCameraCover(struct TreeNode* root){
    int res = 0;

    int solve(struct TreeNode* node, bool parent) {
        if (node) {
            int left = solve(node->left, true);
            int right = solve(node->right, true);

            if (!parent) {
                if (left != 1 && right != 1) {
                    res++;
                    return 0;
                }
            }

            if (left == 2 || right == 2) {
                res++;
                return 1;
            }
            else if (left == 1 || right == 1) {
                return 3;
            }
            else {
                return 2;
            }
        }
        return 3;
    }
    solve(root, false);
    return res;
}