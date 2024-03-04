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
  int min = INT_MAX;

 public:
  int getMinimumDifference(TreeNode* root) {
    if (!root) return INT_MAX;

    int now_val = root->val;
    int temp = INT_MAX;

    TreeNode* r = root->left;
    while (r) {
      temp = r->val;
      r = r->right;
    }

    int temp_min = abs(now_val - temp);
    if (temp_min < min) min = temp_min;

    if (min == 1) return 1;

    r = root->right;
    while (r) {
      temp = r->val;
      r = r->left;
    }

    temp_min = abs(now_val - temp);
    if (temp_min < min) min = temp_min;

    if (min == 1) return 1;

    getMinimumDifference(root->left);
    getMinimumDifference(root->right);

    return min;
  }
};