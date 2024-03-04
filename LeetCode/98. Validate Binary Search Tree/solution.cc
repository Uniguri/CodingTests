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
  bool valid(TreeNode* root, long high, long low) {
    if (!root) return true;

    long root_val = root->val;
    if (!(low < root_val && root_val < high)) return false;

    return (valid(root->left, root_val, low) &&
            valid(root->right, high, root_val));
  }

 public:
  bool isValidBST(TreeNode* root) { return valid(root, LONG_MAX, LONG_MIN); }
};