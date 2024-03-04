class Solution {
 public:
  string kthDistinct(vector<string>& arr, int k) {
    unordered_map<string, int> map;

    for (int i = 0; i < arr.size(); ++i) {
      auto& str = arr[i];
      if (map.find(str) == map.end()) {
        map.insert({str, i});
      } else {
        arr[map.find(str)->second] = "";
        str = "";
      }
    }

    for (unsigned int i = 0, j = 1; i < arr.size(); ++i) {
      if (arr[i] != "") {
        if (j == k)
          return arr[i];
        else
          ++j;
      }
    }

    return "";
  }
};