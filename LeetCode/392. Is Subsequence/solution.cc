class Solution {
 public:
  bool isSubsequence(string s, string t) {
    size_t sequence = 0;
    for (int i = 0; sequence < s.length() && i < t.length(); i++) {
      if (s.at(sequence) == t.at(i)) {
        sequence++;
      }
    }
    return sequence == s.length();
  }
};