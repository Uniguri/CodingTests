/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
 private:
  int _maxDepth(TreeNode* root, int nowDepth) {
    if (!root) return nowDepth - 1;

    return max(_maxDepth(root->left, nowDepth + 1),
               _maxDepth(root->right, nowDepth + 1));
  }

 public:
  int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return _maxDepth(root, 1);
  }
};