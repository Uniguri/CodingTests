class Solution {
 private:
  void reverse(vector<char>& s, size_t i, size_t j) {
    if (j <= i) {
      return;
    }
    char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    reverse(s, i + 1, j - 1);
  }

 public:
  void reverseString(vector<char>& s) { reverse(s, 0, s.size() - 1); }
};