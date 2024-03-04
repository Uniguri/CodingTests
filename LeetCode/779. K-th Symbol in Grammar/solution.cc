class Solution {
 private:
  unsigned int pow(unsigned int n, unsigned int k) {
    unsigned int ret = 1;
    for (unsigned int i = 0; i < k; i++) {
      ret *= n;
    }

    return ret;
  }

 public:
  int kthGrammar(int n, int k) {
    if (k == 1)
      return 0;
    else if (k == 2)
      return 1;

    int npower = pow(2, n - 1);
    if (k <= npower)
      return kthGrammar(n - 1, k);
    else
      return kthGrammar(n - 1, k - npower) ^ 1;
  }
};