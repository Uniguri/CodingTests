class Solution {
 public:
  int maxOperations(vector<int>& nums, int k) {
    int number_of_operations = 0;
    unordered_map<int, int> freq;

    for (const auto& i : nums) {
      int complement = k - i;
      if (freq[i] > 0) {
        ++number_of_operations;
        freq[i]--;
      } else
        freq[complement]++;
    }

    return number_of_operations;
  }
};