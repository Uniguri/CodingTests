class Solution {
 private:
  unordered_map<int, int> table;

 public:
  int climbStairs(int n) {
    if (n <= 0)
      return 0;
    else if (n < 4)
      return n;

    if (table.find(n) != table.end())
      return table[n];
    else
      table[n] = climbStairs(n - 1) + climbStairs(n - 2);

    return table[n];
  }
};