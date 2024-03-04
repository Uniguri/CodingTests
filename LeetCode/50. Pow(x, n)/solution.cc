class Solution {
 private:
  double _myPow(double x, long long n) {
    if (x == 0.) return 0.;
    if (n == 0 || x == 1.) return 1.;
    if (n == 1) return x;

    double temp = _myPow(x * x, n / 2);

    if (n % 2 == 0) {
      return temp;
    } else {
      return temp * x;
    }
  }

 public:
  double myPow(double x, int n) {
    if (n < 0) {
      return 1 / _myPow(x, -(long long)n);
    }

    return _myPow(x, (long long)n);
  }
};