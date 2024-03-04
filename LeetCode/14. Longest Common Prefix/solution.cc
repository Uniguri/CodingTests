class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    int max_length_of_prefix = 200;
    unordered_map<int, char> prefix_map;

    for (const auto& str : strs) {
      const int length_of_str = str.length();
      if (length_of_str < max_length_of_prefix)
        max_length_of_prefix = length_of_str;

      for (int i = 0; i < length_of_str; ++i) {
        if (prefix_map.find(i) == prefix_map.end())
          prefix_map[i] = str[i];
        else {
          if (prefix_map[i] != str[i]) {
            if (i < max_length_of_prefix) max_length_of_prefix = i;
            break;
          }
        }
      }
    }

    string prefix;
    prefix.reserve(max_length_of_prefix);

    for (int i = 0; i < max_length_of_prefix; ++i) {
      prefix.push_back(prefix_map[i]);
    }

    return prefix;
  }
};