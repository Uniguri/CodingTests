class Solution {
 public:
  int countOrders(int n) {
    unsigned long long ret = 1;
    for (int i = 1; i <= n; i++) {
      ret *= i;
      ret *= (2 * i - 1);
      ret %= 1000000007;
    }
    return ret;
  }
};