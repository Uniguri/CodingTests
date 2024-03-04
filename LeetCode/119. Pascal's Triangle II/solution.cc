class Solution {
 public:
  vector<int> getRow(int rowIndex) {
    if (rowIndex == 0)
      return {1};
    else if (rowIndex == 1)
      return {1, 1};

    vector<int> ret(rowIndex + 1);
    ret[0] = ret[rowIndex] = 1;

    auto&& t = getRow(rowIndex - 1);
    for (int i = 1; i < rowIndex; i++) {
      ret[i] = t[i - 1] + t[i];
    }

    return ret;
  }
};