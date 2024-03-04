class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> location_of_appeared_char;

    int start = 0, longest = 0;
    for (int i = 0; i < s.length(); i++) {
      char c = s[i];
      if (location_of_appeared_char.find(c) !=
          location_of_appeared_char.end()) {
        int check_longest = i - start;
        if (longest < check_longest) longest = check_longest;

        int check_location = location_of_appeared_char[c] + 1;
        if (start < check_location) start = check_location;
      }
      location_of_appeared_char[c] = i;
    }

    int check_longest = s.length() - start;
    if (longest < check_longest) longest = check_longest;

    return longest;
  }
};