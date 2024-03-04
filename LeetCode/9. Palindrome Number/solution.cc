class Solution {
 public:
  bool isPalindrome(int x) {
    if (x < 0) return false;

    string str = to_string(x);
    int size = str.length();

    int start = 0, end = size - 1;
    while (start <= end) {
      if (str[start++] != str[end--]) return false;
    }

    return true;
  }
};