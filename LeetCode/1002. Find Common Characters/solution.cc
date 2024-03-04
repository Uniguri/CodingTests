class Solution {
 public:
  vector<string> commonChars(vector<string>& words) {
    vector<string> ret;
    ret.reserve(26);

    unsigned int appearance_count[26] = {0};
    fill_n(appearance_count, 26, INT_MAX);

    for (const auto& word : words) {
      unsigned int temp[26] = {0};
      for (const char c : word) {
        ++temp[c - 'a'];
      }

      for (int i = 0; i < 26; ++i)
        appearance_count[i] = min(appearance_count[i], temp[i]);
    }

    for (int i = 0; i < 26; ++i)
      for (int t = 0; t < appearance_count[i]; ++t)
        ret.push_back(string(1, 'a' + i));

    return ret;
  }
};